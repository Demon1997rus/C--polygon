#pragma once

#include <string>

#include <boost/property_tree/xml_parser.hpp>

using namespace std;
using namespace boost::property_tree;

namespace rdi {
class ConfigPrivate {

public:
    ptree root;

public:
    void load(const string &configPath);
};
}
