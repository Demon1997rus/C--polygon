#pragma once

#include <memory>

#include <boost/noncopyable.hpp>
#include <boost/property_tree/ptree.hpp>

namespace rdi {
class ConfigPrivate;
class Config : public boost::noncopyable {
public:
    typedef boost::property_tree::ptree Node;

    // constructors
public:
    Config();
    explicit Config(const std::string &configPath);
    ~Config();

    // interface
public:
    void load(const std::string &configPath);
    Node root() const noexcept;
    Node findNode(const std::string &path) const;

    // pimpl
private:
    std::unique_ptr<ConfigPrivate> d;
};
}
