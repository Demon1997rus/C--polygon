#include "config.h"

#include <iostream>

#include "configprivate.h"

#define INIT(...) d(new ConfigPrivate(__VA_ARGS__))

namespace rdi {
Config::Config() : INIT() {}

Config::Config(const string &configPath) : Config()
{
    load(configPath);
}

Config::~Config() {}

void Config::load(const string &configPath)
{
    try {
        d->load(configPath);
    } catch (const exception &e) {
        cout << __PRETTY_FUNCTION__ << endl;
        cout << e.what() << endl;
    }
}

Config::Node Config::root() const noexcept
{
    return d->root;
}

Config::Node Config::findNode(const string &path) const
{
    try {
        return d->root.get_child(path);
    } catch (const exception &e) {
        cout << __PRETTY_FUNCTION__ << endl;
        cout << e.what() << endl;
    }
    return Node();
}

void ConfigPrivate::load(const string &configPath)
{
    read_xml(configPath, root);
}
}
#undef INIT
