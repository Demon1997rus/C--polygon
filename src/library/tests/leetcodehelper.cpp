#include "leetcodehelper.h"

#include "leetcodehelperprivate.h"

#define INIT(...) d(new LeetCodeHelperPrivate(__VA_ARGS__))

namespace rdi {
LeetCodeHelper::LeetCodeHelper() : INIT() {}

LeetCodeHelper::LeetCodeHelper(const string &configPath) : LeetCodeHelper()
{
    load(configPath);
}

LeetCodeHelper::~LeetCodeHelper() {}

void LeetCodeHelper::load(const string &configPath)
{
    d->config.load(configPath);
}

std::vector<std::string> LeetCodeHelper::problem(const string &problem)
{
    Config::Node node = d->config.findNode("leetcode.problem" + problem);
    std::vector<std::string> tests;
    tests.reserve(node.size());
    for (const auto &child : node) {
        tests.push_back(child.second.data());
    }
    return tests;
}
}
#undef INIT
