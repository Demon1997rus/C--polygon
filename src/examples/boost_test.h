#ifndef BOOST_TEST_H
#define BOOST_TEST_H

#include <stdexcept>

namespace rdi {
struct foo {
    int m_val;

    operator int() const { return m_val; }

    bool is_not_null() const { return m_val != 0; }

    void throws() const
    {
        if (is_not_null())
            throw std::logic_error("Logic error: check boost test.");
    }
};
}
#endif // BOOST_TEST_H
