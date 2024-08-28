#pragma once

#include <stdexcept>

#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/throw_exception.hpp>

#include <bits/c++config.h>

namespace rdi {

template <class T, std::size_t N>
class Array {
    BOOST_STATIC_ASSERT_MSG(N != 0, "Array size is zero");

public:
    using size_type = std::size_t;
    using value_type = T;
    using reference = value_type &;
    using pointer = value_type *;
    using iterator = value_type *;
    using const_iterator = const value_type *;
    using const_reference = const value_type &;

public:
    T elems[N];

    // functions
public:
    size_type size() const noexcept { return N; }

    iterator begin() noexcept { return iterator(elems); }
    const_iterator begin() const noexcept { return const_iterator(elems); }

    iterator end() noexcept { return iterator(elems + N); }
    const_iterator end() const noexcept { return const_iterator(elems + N); }

    reference operator[](size_type index) noexcept
    {
        BOOST_ASSERT(index < N && "Index out of range");
        return elems[index];
    }

    const_reference operator[](size_type index) const noexcept
    {
        BOOST_ASSERT(index < N && "Index out of range");
        return elems[index];
    }

    reference front() noexcept { return elems[0]; }
    const_reference front() const noexcept { return elems[0]; }

    reference back() noexcept { return elems[N - 1]; }
    const_reference back() const noexcept { return elems[N - 1]; }

    reference at(size_type index)
    {
        range_check(index);
        return elems[index];
    }

    const_reference at(size_type index) const
    {
        range_check(index);
        return elems[index];
    }

private:
    // check range (may be private because it is static)
    static void range_check(size_type index)
    {
        if (index >= N) {
            std::out_of_range e("array<>: index out of range");
            boost::throw_exception(e);
        }
    }
};
} // namespace rdi
