#ifndef QUEUE_PROCESS_H
#define QUEUE_PROCESS_H

#include <boost/atomic.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/deque.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/optional.hpp>

#if (BOOST_ATOMIC_INT_LOCK_FREE != 2)
#error "This code requires lock-free boost::atomic<int>"
#endif

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                Межпроцессорная очередь                               //
//                                                                                      //
//--------------------------------------------------------------------------------------//

/*!
 *  Пример использования
 *
 * Процесс №1
 * int main()
 * {
 *      // 1 - название общей памяти, 2 - сколько нужно выдели места в общей памяти.
 *      process_queue<int> pq("shared_memory", (1024 * 1024 * 32))
 *      pq.push(1);
 *      std::cin.get(); // ждемс пока 2 процесс заберет переменную это чисто для примера
 * }
 *
 * Процесс №2
 * int main()
 * {
 *      process_queue<int> pq("shared_memory", (1024 * 1024 * 32))
 *      int res = pq.pop(); // Если очередь пуста то этот процесс будет ждать элемента
 *      std::cout << res << std::endl; // выведет 1 в консоль.
 * }
 */

/*!
 *  !!! ВАЖНО !!!
 *  Не помещайте классы, которые могут иметь указатели или ссылки,
 *  в общую память! Используйте #include <boost/interprocess/offset_ptr.hpp>/
 */

namespace rdi {
template <class T>
class process_queue {
    BOOST_STATIC_ASSERT_MSG(!boost::is_pointer<T>::value, "Type cannot be a pointer");

public:
    using managed_shared_memory_type = boost::interprocess::managed_shared_memory;
    using value_type = T;
    using allocator_type = boost::interprocess::allocator<
        value_type, boost::interprocess::managed_shared_memory::segment_manager>;

private:
    const std::string m_name;
    managed_shared_memory_type m_segment;
    const allocator_type m_allocator;

    using container_type = boost::interprocess::deque<value_type, allocator_type>;
    container_type &m_container;

    using mutex_type = boost::interprocess::interprocess_mutex;
    mutex_type &m_mutex;

    using condition_type = boost::interprocess::interprocess_condition;
    condition_type &m_cond;

    using lock_type = boost::interprocess::scoped_lock<mutex_type>;

    using atomic_type = boost::atomic<int>;
    atomic_type &m_atomic;

    // constructor and destructor
public:
    process_queue(const std::string &name, const std::size_t size) :
        m_name(name),
        m_segment(boost::interprocess::open_or_create, get_segment_name().c_str(), size),
        m_allocator(m_segment.get_segment_manager()),
        m_container(*m_segment.find_or_construct<container_type>(get_container_name().c_str())(
            m_allocator)),
        m_mutex(*m_segment.find_or_construct<mutex_type>(get_mutex_name().c_str())()),
        m_cond(*m_segment.find_or_construct<condition_type>(get_condition_name().c_str())()),
        m_atomic(*m_segment.find_or_construct<atomic_type>(get_atomic_name().c_str())(0))
    {
        ++m_atomic;
    }

    ~process_queue()
    {
        if ((--m_atomic) == 0) {
            this->cleanup();
        }
    }

    // public interface
public:
    void push(const value_type &val) { emplace(val); }

    void push(value_type &&val) { emplace(boost::move(val)); }

    template <class... Args>
    void emplace(Args &&... args)
    {
        lock_type lock(m_mutex);
        m_container.emplace_back(boost::forward<Args>(args)...);
        lock.unlock();
        m_cond.notify_one();
    }

    boost::optional<value_type> try_pop_task()
    {
        boost::optional<value_type> res;
        lock_type lock(m_mutex, boost::interprocess::defer_lock);
        if (lock.try_lock() && !m_container.empty()) {
            res = boost::move(m_container.front());
            m_container.pop_front();
        }
        return res;
    }

    value_type pop()
    {
        lock_type lock(m_mutex);
        while (m_container.empty()) {
            m_cond.wait(lock);
        }
        value_type res = boost::move(m_container.front());
        m_container.pop_front();
        return res;
    }

    // private interface
private:
    std::string get_segment_name() const { return m_name; }
    std::string get_container_name() const { return m_name + ":container"; }
    std::string get_mutex_name() const { return m_name + ":mutex"; }
    std::string get_condition_name() const { return m_name + ":condition"; }
    std::string get_atomic_name() const { return m_name + ":atomic"; }

    void cleanup()
    {
        m_segment.destroy<condition_type>(get_condition_name().c_str());
        m_segment.destroy<mutex_type>(get_mutex_name().c_str());
        m_segment.destroy<container_type>(get_container_name().c_str());
        m_segment.destroy<atomic_type>(get_atomic_name().c_str());
        boost::interprocess::shared_memory_object::remove(get_segment_name().c_str());
    }
};
}
#endif // QUEUE_PROCESS_H
