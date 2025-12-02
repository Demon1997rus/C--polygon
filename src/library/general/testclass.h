#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace rdi {
template <class T>
class TestClass {
    typedef T type_test;
    typedef type_test &reference;
    typedef type_test *pointer;

public:
    void test() {}
    void test() const {}

    TestClass() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

    TestClass(const type_test &test) : __test(test)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    TestClass(type_test &&test) : __test(std::move(test))
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    TestClass(const TestClass<type_test> &other) : __test(other.__test)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    TestClass(TestClass<type_test> &&other) noexcept : __test(std::move(other.__test))
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    ~TestClass() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

    TestClass<type_test> &operator=(const TestClass<type_test> &other)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        __test = other.__test;
        return *this;
    }

    TestClass<type_test> &operator=(TestClass<type_test> &&other) noexcept
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        __test = std::move(other.__test);
        return *this;
    }

    reference operator*()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return __test;
    }

    pointer operator->()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return &__test;
    }

    bool operator==(const TestClass<type_test> &other) const
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return __test == other.__test;
    }

    bool operator!=(const TestClass<type_test> &other) const
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return !(*this == other);
    }

    bool operator<(const TestClass<type_test> &other) const
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return __test < other.__test;
    }

    bool operator<=(const TestClass<type_test> &other) const
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return __test <= other.__test;
    }

    bool operator>(const TestClass<type_test> &other) const
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return __test > other.__test;
    }

    bool operator>=(const TestClass<type_test> &other) const
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return __test >= other.__test;
    }

    rdi::TestClass<type_test> operator+(const TestClass<type_test> &other) const
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return TestClass<type_test>(__test + other.__test);
    }

    rdi::TestClass<type_test> &operator+=(const TestClass<type_test> &other)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        __test += other.__test;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const TestClass<type_test> &other)
    {
        os << other.__test;
        return os;
    }

    friend std::istream &operator>>(std::istream &is, TestClass<type_test> &other)
    {
        is >> other.__test;
        return is;
    }

    template <class... Args>
    static std::shared_ptr<TestClass<type_test>> make_shared(Args &&...args)
    {
        return std::make_shared<TestClass<type_test>>(std::forward<Args>(args)...);
    }

    template <class... Args>
    static std::unique_ptr<TestClass<type_test>> make_unique(Args &&...args)
    {
        return std::make_unique<TestClass<type_test>>(std::forward<Args>(args)...);
    }

private:
    type_test __test;
};
}
