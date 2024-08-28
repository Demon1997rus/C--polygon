#pragma once

#include <iostream>

#include <boost/move/move.hpp>

#include <string.h>

namespace rdi { namespace examples {

/*!
 * \brief The ExampleBoostNonCopyOnMove class - класс мувается но не копируется
 */
class ExampleBoostNonCopyOnMove {
private:
    void *m_descriptor;

private:
    BOOST_MOVABLE_BUT_NOT_COPYABLE(ExampleBoostNonCopyOnMove)

public:
    ExampleBoostNonCopyOnMove() : m_descriptor(nullptr) {}

    explicit ExampleBoostNonCopyOnMove(const char *param) : m_descriptor(strdup(param)) {}

    ExampleBoostNonCopyOnMove(BOOST_RV_REF(ExampleBoostNonCopyOnMove) other) BOOST_NOEXCEPT
        : m_descriptor(other.m_descriptor)
    {
        other.m_descriptor = nullptr;
    }

    ExampleBoostNonCopyOnMove &operator=(BOOST_RV_REF(ExampleBoostNonCopyOnMove)
                                             other) BOOST_NOEXCEPT
    {
        ExampleBoostNonCopyOnMove temp(boost::move(other));
        std::swap(m_descriptor, temp.m_descriptor);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const ExampleBoostNonCopyOnMove &other)
    {
        return os << reinterpret_cast<const char *>(other.m_descriptor);
    }
};
}}
