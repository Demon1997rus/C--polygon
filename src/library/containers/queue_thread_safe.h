#pragma once

#include <queue>

#include <boost/optional.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_lock_guard.hpp>
#include <boost/thread/thread.hpp>

template <class T>
class queue_thread_safe {
public:
    typedef T value_type;
    typedef std::queue<value_type> container_type;
    typedef boost::mutex mutex_type;
    typedef boost::condition_variable condition_type;
    typedef typename container_type::size_type size_type;

public:
    void push(const value_type &val) { emplace(val); }

    void push(value_type &&val) { emplace(boost::move(val)); }

    template <class... Args>
    void emplace(Args &&... args)
    {
        boost::unique_lock<mutex_type> lock(m_mtx);
        m_container.emplace(boost::forward<Args>(args)...);
        lock.unlock();
        m_cond.notify_one();
    }

    value_type pop()
    {
        boost::unique_lock<mutex_type> lock(m_mtx);
        while (m_container.empty()) {
            m_cond.wait(lock);
        }

        value_type res = boost::move(m_container.front());
        m_container.pop();
        return res;
    }

    boost::optional<value_type> try_pop()
    {
        boost::optional<value_type> res;
        boost::unique_lock<mutex_type> lock(m_mtx, boost::defer_lock);
        if (lock.try_lock() && !m_container.empty()) {
            res = boost::move(m_container.front());
            m_container.pop();
        }
        return res;
    }

private:
    container_type m_container;
    mutex_type m_mtx;
    condition_type m_cond;
};
