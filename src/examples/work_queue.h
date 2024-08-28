#ifndef WORK_QUEUE_H
#define WORK_QUEUE_H

#include <deque>

#include <boost/function.hpp>
#include <boost/optional.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>

class work_queue {
public:
    using task_type = boost::function<void()>;
    using container_type = std::deque<task_type>;
    using mutex_type = boost::mutex;
    using cond_type = boost::condition_variable;

public:
    void push_task(const task_type &task) { emplace_task(task); }

    void push_task(task_type &&task) { emplace_task(std::move(task)); }

    template <class... Args>
    void emplace_task(Args &&... args)
    {
        boost::unique_lock<mutex_type> lock(m_mutex);
        m_tasks.emplace_back(std::forward<Args>(args)...);
        lock.unlock();
        m_cond.notify_one();
    }

    boost::optional<task_type> try_pop_task()
    {
        boost::optional<task_type> res;
        boost::unique_lock<mutex_type> lock(m_mutex, boost::defer_lock);
        if (lock.try_lock() && !m_tasks.empty()) {
            res = std::move(m_tasks.front());
            m_tasks.pop_front();
        }
        return res;
    }

    task_type pop_task()
    {
        boost::unique_lock<mutex_type> lock(m_mutex);
        while (m_tasks.empty()) {
            m_cond.wait(lock);
        }

        task_type res = std::move(m_tasks.front());
        m_tasks.pop_front();
        return res;
    }

    void stop()
    {
        boost::lock_guard<mutex_type> lock(m_mutex);
        m_is_stopped = true;
        m_cond.notify_all();
    }

    void run()
    {
        while (true) {
            boost::unique_lock<mutex_type> lock(m_mutex);
            while (m_tasks.empty()) {
                if (m_is_stopped) {
                    return;
                }
                m_cond.wait(lock);
            }

            task_type task = std::move(m_tasks.front());
            m_tasks.pop_front();
            lock.unlock();
            task();
        }
    }

private:
    container_type m_tasks;
    mutex_type m_mutex;
    cond_type m_cond;
    bool m_is_stopped;
};

#endif // WORK_QUEUE_H
