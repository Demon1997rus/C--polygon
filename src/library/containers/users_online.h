#ifndef USERS_ONLINE_H
#define USERS_ONLINE_H

#include <string>
#include <unordered_map>

#include <boost/thread/shared_lock_guard.hpp>
#include <boost/thread/shared_mutex.hpp>

namespace detail {
struct user_info {
    unsigned short age;
    std::string address;
};
}

class users_online {
public:
    using user_info = detail::user_info;

    // public interface
public:
    bool is_online(const std::string &username) const
    {
        boost::shared_lock<boost::shared_mutex> lock(m_mutex);
        return m_users.find(username) != m_users.end();
    }

    std::string get_address(const std::string &username) const
    {
        boost::shared_lock_guard<boost::shared_mutex> lock(m_mutex);
        return m_users.at(username).address;
    }

    void set_online(const std::string &username, const user_info &data)
    {
        boost::lock_guard<boost::shared_mutex> lock(m_mutex);
        m_users.emplace(username, data);
    }

    // private members
private:
    mutable boost::shared_mutex m_mutex;
    std::unordered_map<std::string, user_info> m_users;
};

#endif // USERS_ONLINE_H
