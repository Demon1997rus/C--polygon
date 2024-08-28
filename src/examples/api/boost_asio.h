#pragma once

#define BOOST_ASIO_DISABLE_HANDLER_TYPE_REQUIREMENTS

#include <memory>

#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/function.hpp>
#include <boost/thread/thread.hpp>

namespace detail {
template <class T>
struct task_wrapped {
public:
    explicit task_wrapped(const T &f) : m_task_unwrapped(f) {}

    void operator()() const
    {
        // Сброс прерывания
        try {
            boost::this_thread::interruption_point();
        } catch (const boost::thread_interrupted &) {
        }

        try {
            // Выполнения  задачи
            m_task_unwrapped();
        } catch (const std::exception &e) {
            std::cerr << "Exception: " << e.what() << '\n';
        } catch (const boost::thread_interrupted &) {
            std::cerr << "Thread interrupted\n";
        } catch (...) {
            std::cerr << "Unknown exception\n";
        }
    }

private:
    T m_task_unwrapped;
};

template <class T>
task_wrapped<T> make_task_wrapped(const T &task_unwrapped)
{
    return task_wrapped<T>(task_unwrapped);
}

template <class Functor>
struct timer_task {
public:
    explicit timer_task(std::unique_ptr<boost::asio::deadline_timer> timer,
                        const Functor &task) :
        m_timer(std::move(timer)),
        m_task(task)
    {
    }

    void operator()(const boost::system::error_code &error) const
    {
        if (!error) {
            m_task();
        } else {
            std::cerr << error << '\n';
        }
    }

private:
    std::unique_ptr<boost::asio::deadline_timer> m_timer;
    task_wrapped<Functor> m_task;
};

struct connection_with_data : boost::noncopyable {
public:
    explicit connection_with_data(boost::asio::io_service &ios) : m_socket(ios) {}

    void shutdown()
    {
        if (!m_socket.is_open()) {
            return;
        }

        boost::system::error_code ignore;
        m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignore);
        m_socket.close(ignore);
    }

    void connect(const char *addr, unsigned short port_num)
    {
        m_socket.connect(boost::asio::ip::tcp::endpoint(
            boost::asio::ip::address_v4::from_string(addr), port_num));
    }

    std::string &data() { return m_data; }

    std::string data() const { return m_data; }

    boost::asio::ip::tcp::socket &socket() { return m_socket; }

    ~connection_with_data() { shutdown(); }

private:
    boost::asio::ip::tcp::socket m_socket;
    std::string m_data;
};
typedef std::unique_ptr<connection_with_data> connection_ptr;

template <class T>
struct task_wrapped_with_connection {
public:
    explicit task_wrapped_with_connection(connection_ptr &&c, const T &f) :
        m_connect(std::move(c)), m_task_unwrapped(f)
    {
    }

    void operator()(const boost::system::error_code &error, std::size_t bytes_count)
    {
        const auto lambda = [this, &error, bytes_count]() {
            m_connect->data().resize(bytes_count);
            m_task_unwrapped(std::move(m_connect), error);
        };

        const auto task = detail::make_task_wrapped(lambda);
        task();
    }

private:
    connection_ptr m_connect;
    T m_task_unwrapped;
};

} // namespace detail

typedef detail::connection_ptr connection_ptr;

class tasks_processor : private boost::noncopyable {
    typedef boost::asio::ip::tcp::acceptor acceptor_type;
    typedef boost::function<void(connection_ptr, const boost::system::error_code &)>
        on_accept_func_type;

public:
    static void start() { get_ios().run(); }

    static void stop() { get_ios().stop(); }

    template <class T>
    static void push_task(const T &task_unwrapped)
    {
        get_ios().post(detail::make_task_wrapped(task_unwrapped));
    }

    template <class Time, class Func>
    static void run_delayed(Time duration_or_time, const Func &f)
    {
        std::unique_ptr<boost::asio::deadline_timer> timer(
            new boost::asio::deadline_timer(get_ios(), duration_or_time));

        boost::asio::deadline_timer &timer_ref = *timer;

        timer_ref.async_wait(detail::timer_task<Func>(std::move(timer), f));
    }

    static connection_ptr create_connection(const char *addr, unsigned short port_num)
    {
        connection_ptr res(new detail::connection_with_data(get_ios()));
        res->connect(addr, port_num);
        return res;
    }

    template <class Functor>
    static void add_listener(unsigned short port_num, const Functor &f)
    {
        std::unique_ptr<tcp_listener> listener(new tcp_listener(get_ios(), port_num, f));
        start_accepting_connection(std::move(listener));
    }

    static void start_multiple(std::size_t threads_count = 0)
    {
        if (threads_count == 0) {
            threads_count =
                (std::max)(static_cast<int>(boost::thread::hardware_concurrency()), 1);
        }

        // Первый поток является текущим
        --threads_count;

        boost::asio::io_service &ios = get_ios();

        boost::thread_group tg;
        for (std::size_t i = 0; i < threads_count; ++i) {
            tg.create_thread([&ios]() { ios.run(); });
        }
        tg.join_all();
    }

protected:
    static boost::asio::io_service &get_ios()
    {
        static boost::asio::io_service ios;
        static boost::asio::io_service::work work(ios);
        return ios;
    }

private:
    struct tcp_listener {
        acceptor_type m_acceptor;
        const on_accept_func_type m_func;
        connection_ptr m_new_connection;

        template <class Functor>
        tcp_listener(boost::asio::io_service &io_service, unsigned short port,
                     const Functor &task_unwrapped) :
            m_acceptor(io_service,
                       boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
            m_func(task_unwrapped)
        {
        }
    };

    typedef std::unique_ptr<tcp_listener> listener_ptr;

    struct handle_accept {
        listener_ptr m_listener;

        explicit handle_accept(listener_ptr &&listener) : m_listener(std::move(listener)) {}

        void operator()(const boost::system::error_code &error)
        {
            detail::task_wrapped_with_connection<on_accept_func_type> task(
                std::move(m_listener->m_new_connection), m_listener->m_func);

            start_accepting_connection(std::move(m_listener));
            task(error, 0);
        }
    };

    static void start_accepting_connection(listener_ptr &&listener)
    {
        if (!listener->m_acceptor.is_open()) {
            return;
        }
        listener->m_new_connection.reset(
            new detail::connection_with_data(listener->m_acceptor.get_io_service()));

        boost::asio::ip::tcp::socket &s = listener->m_new_connection->socket();
        acceptor_type &a = listener->m_acceptor;
        a.async_accept(s, tasks_processor::handle_accept(std::move(listener)));
    }
};

namespace api {

template <class Functor>
BOOST_ASIO_DECL void async_write_data(connection_ptr &&c, const Functor &f)
{
    boost::asio::ip::tcp::socket &s = c->socket();
    std::string &d = c->data();

    boost::asio::async_write(s, boost::asio::buffer(d),
                             detail::task_wrapped_with_connection<Functor>(std::move(c), f));
}

template <class Functor>
BOOST_ASIO_DECL void async_read_data(connection_ptr &&c, const Functor &f,
                                     std::size_t at_least_bytes)
{
    std::string &d = c->data();
    boost::asio::ip::tcp::socket &s = c->socket();

    d.resize(at_least_bytes);
    char *p = (d.empty() ? 0 : &d[0]);

    boost::asio::async_read(s, boost::asio::buffer(p, d.size()),
                            detail::task_wrapped_with_connection<Functor>(std::move(c), f));
}

template <class Functor>
BOOST_ASIO_DECL void async_read_data_at_least(connection_ptr &&c, const Functor &f,
                                              std::size_t at_least_bytes, std::size_t at_most)
{
    boost::asio::ip::tcp::socket &s = c->socket();
    std::string &d = c->data();

    d.resize(at_most);
    char *p = (at_most == 0 ? 0 : &d[0]);

    boost::asio::async_read(s, boost::asio::buffer(p, at_most),
                            boost::asio::transfer_at_least(at_least_bytes),
                            detail::task_wrapped_with_connection<Functor>(std::move(c), f));
}
}
