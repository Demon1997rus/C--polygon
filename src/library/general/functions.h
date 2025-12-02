#pragma once

#include <algorithm>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include <bits/allocator.h>

#define DISABLE_COPY(Class)                                                                    \
    Class(const Class &) = delete;                                                             \
    Class &operator=(const Class &) = delete;

namespace rdi {

//Проверяет контейнер ли это
template <class T>
struct has_begin_end {
    typedef char yes;
    typedef struct {
        yes dummy[2];
    } no;

    template <class U>
    static auto test(U *u) -> decltype((*u).begin(), (*u).end(), yes());
    static no test(...);

public:
    enum { value = (sizeof(yes) == sizeof test((T *) 0)) };
};

template <class T>
T *new_copy(const T *src, size_t src_size, size_t dst_size)
{
    T *dst = new T[dst_size];
    try {
        std::copy(src, src + src_size, dst);
    } catch (...) {
        delete[] dst;
        throw;
    }
    return dst;
}

template <class T1, class T2>
auto sum(T1 first, T2 second) -> decltype(first + second)
{
    return first + second;
}

template <class T, class... Args>
inline std::unique_ptr<T> make_unique(Args &&...args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <class T>
std::unique_ptr<T> copy_singleton(const T &singleton)
{
    std::unique_ptr<char[]> data(new char[sizeof(T)]);
    std::memcpy(data.get(), &singleton, sizeof(T));
    return std::unique_ptr<T>(reinterpret_cast<T *>(data.release()));
}

template <class T>
std::enable_if_t<!has_begin_end<T>::value && !std::is_array<T>::value> print(const T &element)
{
    std::cout << element << " ";
}

template <class T>
std::enable_if_t<std::is_array<T>::value && !has_begin_end<T>::value> print(const T &pointer)
{
    auto beg = std::cbegin(pointer);
    auto end = std::cend(pointer);
    while (beg != end) {
        print(*(beg++));
    }
}

template <class T>
std::enable_if_t<has_begin_end<T>::value && !std::is_array<T>::value> print(const T &container)
{
    for (const auto &e : container) {
        print(e);
    }
    std::cout << '\n';
}

template <class T>
std::enable_if_t<!has_begin_end<T>::value> input(const T &element)
{
    std::cin >> element;
}

template <class T>
std::enable_if_t<has_begin_end<T>::value> input(const T &container)
{
    for (auto &e : container) {
        input(e);
    }
}

std::string searchConfig(const std::string &name, bool *ok = nullptr);

} // namespace rdi
