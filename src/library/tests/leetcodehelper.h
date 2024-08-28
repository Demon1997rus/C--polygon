#pragma once

#include <memory>
#include <vector>

#include <boost/noncopyable.hpp>

namespace rdi {
class LeetCodeHelperPrivate;
class LeetCodeHelper : public boost::noncopyable {

    // constructors
public:
    LeetCodeHelper();
    explicit LeetCodeHelper(const std::string &configPath);
    ~LeetCodeHelper();

    // interface
public:
    void load(const std::string &configPath);
    std::vector<std::string> problem(const std::string &problem);

    // pimpl
private:
    std::unique_ptr<LeetCodeHelperPrivate> d;
};
}
