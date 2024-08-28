#pragma once

#include <iosfwd>

#include <bits/allocator.h>

namespace rdi {
template <class T, class Alloc = std::allocator<T>>
class Vector {
    typedef T value_type;
    typedef std::size_t size_type;

    typedef value_type &reference;
    typedef const value_type &const_reference;

    typedef value_type *pointer;
    typedef const value_type *const_pointer;

    typedef value_type *iterator;
    typedef const value_type *const_iterator;

    void create_storage(size_type __n)
    {
        this->m_start = this->m_alloc.allocate(__n);
        this->m_finish = this->m_start;
        this->m_storage = this->m_start + __n;
    }

    void default_initialize(size_type __n)
    {
        this->m_finish = std::__uninitialized_default_n_a(m_start, __n, m_alloc);
    }

public:
    Vector() : m_start(), m_finish(), m_storage() {}

    explicit Vector(size_type size)
    {
        this->create_storage(size);
        this->default_initialize(size);
    }

    iterator begin() noexcept { return iterator(m_start); }
    iterator end() noexcept { return iterator(m_finish); }
    const_iterator begin() const noexcept { return const_iterator(m_start); }
    const_iterator end() const noexcept { return const_iterator(m_finish); }

    friend std::ostream &operator<<(std::ostream &os, const Vector<T> &other)
    {
        for (auto it = other.begin(); it != other.end(); ++it) {
            os << *it << " ";
        }
        return os;
    }

public:
    Alloc m_alloc;
    pointer m_start;
    pointer m_finish;
    pointer m_storage;
};
}
