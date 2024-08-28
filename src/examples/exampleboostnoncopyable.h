#pragma once

#include <boost/noncopyable.hpp>

namespace rdi { namespace examples {
class ExampleBoostNonCopyable : private boost::noncopyable {
public:
    ExampleBoostNonCopyable() = default;
};
}}
