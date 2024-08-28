#pragma once

#include <boost/noncopyable.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

namespace rdi {

template <class T>
struct UniquePointerArrayDeleter {
    static inline void cleanup(T *pointer)
    {
        BOOST_STATIC_ASSERT_MSG(sizeof(T) > 0, "can't delete pointer to incomplete type");
        delete[] pointer;
    }
};

template <class T>
struct UniquePointerDeleter {
    static inline void cleanup(T *pointer)
    {
        BOOST_STATIC_ASSERT_MSG(!boost::is_void<T>::value,
                                "can't delete pointer to incomplete type");
        BOOST_STATIC_ASSERT_MSG(sizeof(T) > 0, "can't delete pointer to incomplete type");
        if (pointer) {
            delete pointer;
        }
    }
};

template <class T, class Cleanup = UniquePointerDeleter<T>>
class UniquePointer : private boost::noncopyable {
    BOOST_STATIC_ASSERT_MSG(!boost::is_pointer<T>::value, "Type cannot be a pointer");

public:
    explicit UniquePointer(T *ptr = nullptr) BOOST_NOEXCEPT : m_ptr(ptr) {}

    UniquePointer(UniquePointer<T> &&other) BOOST_NOEXCEPT : m_ptr(other.take()) {}

    UniquePointer &operator=(UniquePointer &&other) BOOST_NOEXCEPT { reset(other.take()); }

    inline ~UniquePointer() BOOST_NOEXCEPT { Cleanup::cleanup(m_ptr); }

    T *data() const BOOST_NOEXCEPT { return m_ptr; }

    T *get() const BOOST_NOEXCEPT { return m_ptr; }

    bool isNull() const { return m_ptr == nullptr; }

    void reset(T *other = nullptr) BOOST_NOEXCEPT
    {
        if (m_ptr == other)
            return;
        T *temp = m_ptr;
        m_ptr = other;
        Cleanup::cleanup(temp);
    }

    void swap(UniquePointer<T, Cleanup> &other) BOOST_NOEXCEPT
    {
        std::swap(m_ptr, other.m_ptr);
    }

    T *take() BOOST_NOEXCEPT
    {
        T *temp = m_ptr;
        m_ptr = nullptr;
        return temp;
    }

    T &operator*() BOOST_NOEXCEPT { return *m_ptr; }

    T *operator->() BOOST_NOEXCEPT { return m_ptr; }

    bool operator!() const BOOST_NOEXCEPT { return !m_ptr; }

    operator bool() const BOOST_NOEXCEPT { return !isNull(); }

private:
    T *m_ptr;
};

template <class T, class... Args>
UniquePointer<T> make_unique(Args &&... args)
{
    return UniquePointer<T>(new T(std::forward<Args>(args)...));
}
}
