#include "solution.h"

#include <QDebug>
#include <QFile>

#include "../time/timemeter.h"
#include "solves.h"

namespace rdi { namespace unit_test {
void Solution::productExceptSelf()
{
    using Test = pair<vector<int>, vector<int>>;

    Test test1 = {{1, 2, 3, 4}, {24, 12, 8, 6}};
    Test test2 = {{-1, 1, 0, -3, 3}, {0, 0, 9, 0, 0}};
    Test test3 = {{2, -4, 3, -5, 2}, {120, -60, 80, -48, 120}};

    QCOMPARE(rdi::productExceptSelf(test1.first), test1.second);
    QCOMPARE(rdi::productExceptSelf(test2.first), test2.second);
    QCOMPARE(rdi::productExceptSelf(test3.first), test3.second);
}

void Solution::lengthOfLongestSubstring()
{
    QCOMPARE(rdi::lengthOfLongestSubstring("abcabcbb"), 3);
    QCOMPARE(rdi::lengthOfLongestSubstring("bbbbb"), 1);
    QCOMPARE(rdi::lengthOfLongestSubstring("pwwkew"), 3);
    QCOMPARE(rdi::lengthOfLongestSubstring(""), 0);
    QCOMPARE(rdi::lengthOfLongestSubstring("abcweqprrqasfd"), 8);
}

void Solution::findMinArrowShots()
{
    using Test = pair<vector<vector<int>>, int>;

    Test test1 = {{{10, 16}, {2, 8}, {1, 6}, {7, 12}}, 2};
    Test test2 = {{{1, 2}, {3, 4}, {5, 6}, {7, 8}}, 4};
    Test test3 = {{{1, 2}, {2, 3}, {3, 4}, {4, 5}}, 2};
    Test test4 = {{{1, 5}, {2, 6}, {3, 7}, {4, 8}}, 1};

    QCOMPARE(rdi::findMinArrowShots(test1.first), test1.second);
    QCOMPARE(rdi::findMinArrowShots(test2.first), test2.second);
    QCOMPARE(rdi::findMinArrowShots(test3.first), test3.second);
    QCOMPARE(rdi::findMinArrowShots(test4.first), test4.second);
}

void Solution::leastInterval()
{
    using Params = pair<vector<char>, int>;
    using Result = int;
    using Test = pair<Params, Result>;

    Test test1 = {{{'A', 'A', 'A', 'B', 'B', 'B'}, 2}, 8};
    Test test2 = {{{'A', 'C', 'A', 'B', 'D', 'B'}, 1}, 6};
    Test test3 = {{{'A', 'A', 'A', 'B', 'B', 'B'}, 3}, 10};
    Test test4 = {{{'A', 'A', 'A', 'A', 'A', 'B'}, 2}, 13};
    Test test5 = {{{'A', 'A', 'A', 'A', 'A', 'A', 'B', 'C', 'D', 'E', 'F', 'G'}, 1}, 12};

    QCOMPARE(rdi::leastInterval(test1.first.first, test1.first.second), test1.second);
    QCOMPARE(rdi::leastInterval(test2.first.first, test2.first.second), test2.second);
    QCOMPARE(rdi::leastInterval(test3.first.first, test3.first.second), test3.second);
    QCOMPARE(rdi::leastInterval(test4.first.first, test4.first.second), test4.second);
    QCOMPARE(rdi::leastInterval(test5.first.first, test5.first.second), test5.second);
}

void Solution::mergeInBeetween()
{
    using Params = std::tuple<ListNode *, int, int, ListNode *>;
    using Result = ListNode *;
    using Test = pair<Params, Result>;

    Test test1{{ListNode::toListNode({10, 1, 13, 6, 9, 5}), 3, 4,
                ListNode::toListNode({1000000, 1000001, 1000002})},
               ListNode::toListNode({10, 1, 13, 1000000, 1000001, 1000002, 5})};

    ListNode *test1_result =
        rdi::mergeInBeetween(std::get<0>(test1.first), std::get<1>(test1.first),
                             std::get<2>(test1.first), std::get<3>(test1.first));

    Test test2{{ListNode::toListNode({0, 1, 2, 3, 4, 5, 6}), 2, 5,
                ListNode::toListNode({1000000, 1000001, 1000002, 1000003, 1000004})},
               ListNode::toListNode({0, 1, 1000000, 1000001, 1000002, 1000003, 1000004, 6})};

    ListNode *test2_result =
        rdi::mergeInBeetween(std::get<0>(test2.first), std::get<1>(test2.first),
                             std::get<2>(test2.first), std::get<3>(test2.first));

    QCOMPARE(ListNode::toVector(test1_result), ListNode::toVector(test1.second));
    QCOMPARE(ListNode::toVector(test2_result), ListNode::toVector(test2.second));
}

void Solution::isPalindrome()
{
    using Params = ListNode *;
    using Result = bool;
    using Test = pair<Params, Result>;

    Test test1 = {ListNode::toListNode({1, 2, 2, 1}), true};
    Test test2 = {ListNode::toListNode({1, 2}), false};
    Test test3 = {ListNode::toListNode({1, 2, 1}), true};
    Test test4 = {ListNode::toListNode({1, 2, 3, 2, 1}), true};
    Test test5 = {ListNode::toListNode({1, 2, 3, 2, 2}), false};
    Test test6 = {ListNode::toListNode({1, 2, 3, 3, 2, 1}), true};
    Test test7 = {ListNode::toListNode({1}), true};
    Test test8 = {ListNode::toListNode({}), true};
    Test test9 = {ListNode::toListNode({1, 1}), true};

    // hard tests
    Test hardTest1 = {ListNode::toListNode(vector<int>(100000, 1)), true};
    Test hardTest2 = {ListNode::toListNode(vector<int>(100000, 1)), false};
    hardTest2.first->val = 0;

    QCOMPARE(rdi::isPalindrome(test1.first), test1.second);
    QCOMPARE(rdi::isPalindrome(test2.first), test2.second);
    QCOMPARE(rdi::isPalindrome(test3.first), test3.second);
    QCOMPARE(rdi::isPalindrome(test4.first), test4.second);
    QCOMPARE(rdi::isPalindrome(test5.first), test5.second);
    QCOMPARE(rdi::isPalindrome(test6.first), test6.second);
    QCOMPARE(rdi::isPalindrome(test7.first), test7.second);
    QCOMPARE(rdi::isPalindrome(test8.first), test8.second);
    QCOMPARE(rdi::isPalindrome(test9.first), test9.second);
    QCOMPARE(rdi::isPalindrome(hardTest1.first), hardTest1.second);
    QCOMPARE(rdi::isPalindrome(hardTest2.first), hardTest2.second);
}

void Solution::maxDepth()
{
    using Params = string;
    using Result = int;
    using Test = pair<Params, Result>;

    Test test1 = {"(1+(2*3)+((8)/4))+1", 3};
    Test test2 = {"(1)+((2))+(((3)))", 3};

    QCOMPARE(rdi::maxDepth(test1.first), test1.second);
    QCOMPARE(rdi::maxDepth(test2.first), test2.second);
}

void Solution::numIslands()
{
    using Params = vector<vector<char>>;
    using Result = int;
    using Test = pair<Params, Result>;

    Test test1 = {{{'1', '1', '1', '1', '0'},
                   {'1', '1', '0', '1', '0'},
                   {'1', '1', '0', '0', '0'},
                   {'0', '0', '0', '0', '0'}},
                  1};

    Test test2 = {{{'1', '1', '0', '0', '0'},
                   {'1', '1', '0', '0', '0'},
                   {'0', '0', '1', '0', '0'},
                   {'0', '0', '0', '1', '1'}},
                  3};

    QCOMPARE(rdi::numIslands(test1.first), test1.second);
    QCOMPARE(rdi::numIslands(test2.first), test2.second);
}

void Solution::findMaxK()
{
    using Params = vector<int>;
    using Result = int;
    using Test = pair<Params, Result>;

    Test test1 = {{-1, 2, -3, 3}, 3};
    Test test2 = {{-1, 10, 6, 7, -7, 1}, 7};
    Test test3 = {{-10, 8, 6, 7, -2, -3}, -1};
    Test test4 = {{}, -1};
    Test test5 = {{-1, 1}, 1};

    QCOMPARE(rdi::findMaxK(test1.first), test1.second);
    QCOMPARE(rdi::findMaxK(test2.first), test2.second);
    QCOMPARE(rdi::findMaxK(test3.first), test3.second);
    QCOMPARE(rdi::findMaxK(test4.first), test4.second);
    QCOMPARE(rdi::findMaxK(test5.first), test5.second);
}

void Solution::removeNodes()
{
    using Params = ListNode *;
    using Result = ListNode *;
    using Test = pair<Params, Result>;

    Test test1 = {ListNode::toListNode({5, 2, 13, 3, 8}), ListNode::toListNode({13, 8})};
    Test test2 = {ListNode::toListNode({1, 1, 1, 1}), ListNode::toListNode({1, 1, 1, 1})};
    Test test3 = {ListNode::toListNode({14, 8, 5, 7, 3}), ListNode::toListNode({14, 8, 7, 3})};
    Test test4 = {ListNode::toListNode({10, 23, 22, 21, 27, 31}), ListNode::toListNode({31})};

    QCOMPARE(ListNode::toVector(rdi::removeNodes(test1.first)),
             ListNode::toVector(test1.second));
    QCOMPARE(ListNode::toVector(rdi::removeNodes(test2.first)),
             ListNode::toVector(test2.second));
    QCOMPARE(ListNode::toVector(rdi::removeNodes(test3.first)),
             ListNode::toVector(test3.second));
    QCOMPARE(ListNode::toVector(rdi::removeNodes(test4.first)),
             ListNode::toVector(test4.second));
}

void Solution::doubleIt()
{
    using Params = ListNode *;
    using Result = ListNode *;
    using Test = pair<Params, Result>;

    Test test1 = {ListNode::toListNode({1, 8, 9}), ListNode::toListNode({3, 7, 8})};
    Test test2 = {ListNode::toListNode({9, 9, 9}), ListNode::toListNode({1, 9, 9, 8})};

    QCOMPARE(ListNode::toVector(rdi::doubleIt(test1.first)), ListNode::toVector(test1.second));
    QCOMPARE(ListNode::toVector(rdi::doubleIt(test2.first)), ListNode::toVector(test2.second));
}

void Solution::asteroidsDestroyed()
{
    using Params = pair<int, vector<int>>;
    using Result = bool;
    using Test = pair<Params, Result>;

    Test test1 = {{10, {3, 9, 19, 5, 21}}, true};
    Test test2 = {{5, {4, 9, 23, 4}}, false};

    QCOMPARE(rdi::asteroidsDestroyed(test1.first.first, test1.first.second), test1.second);
    QCOMPARE(rdi::asteroidsDestroyed(test2.first.first, test2.first.second), test2.second);
}

void Solution::canBeEqual()
{
    using Params = pair<vector<int>, vector<int>>;
    using Result = bool;
    using Test = pair<Params, Result>;

    Test test1 = {{{1, 2, 3, 4}, {2, 4, 1, 3}}, true};
    Test test2 = {{{7}, {7}}, true};
    Test test3 = {{{3, 7, 9}, {3, 7, 11}}, false};

    QCOMPARE(rdi::canBeEqual(test1.first.first, test1.first.second), test1.second);
    QCOMPARE(rdi::canBeEqual(test2.first.first, test2.first.second), test2.second);
    QCOMPARE(rdi::canBeEqual(test3.first.first, test3.first.second), test3.second);
}

void Solution::appendCharacters()
{
    using Params = pair<string, string>;
    using Result = int;
    using Test = pair<Params, Result>;

    Test test1 = {{"coaching", "coding"}, 4};
    Test test2 = {{"abcde", "a"}, 0};
    Test test3 = {{"z", "abcde"}, 5};

    QCOMPARE(rdi::appendCharacters(test1.first.first, test1.first.second), test1.second);
    QCOMPARE(rdi::appendCharacters(test2.first.first, test2.first.second), test2.second);
    QCOMPARE(rdi::appendCharacters(test3.first.first, test3.first.second), test3.second);
}

void Solution::longestPalindrome()
{
    using Params = string;
    using Result = int;
    using Test = pair<Params, Result>;

    Test test1 = {"abccccdd", 7};
    Test test2 = {"a", 1};
    Test test3 = {
        "civilwartestingwhetherthatnaptionoranynartionsoconceivedandsodedicatedcanlongendureWeareqmetonagreatbattlefiemldoftzhatwarWehavecometodedicpateaportionofthatfieldasafinalrestingplaceforthosewhoheregavetheirlivesthatthatnationmightliveItisaltogetherfangandproperthatweshoulddothisButinalargersensewecannotdedicatewecannotconsecratewecannothallowthisgroundThebravelmenlivinganddeadwhostruggledherehaveconsecrateditfaraboveourpoorponwertoaddordetractTgheworldadswfilllittlenotlenorlongrememberwhatwesayherebutitcanneverforgetwhattheydidhereItisforusthelivingrathertobededicatedheretotheulnfinishedworkwhichtheywhofoughtherehavethusfarsonoblyadvancedItisratherforustobeherededicatedtothegreattdafskremainingbeforeusthatfromthesehonoreddeadwetakeincreaseddevotiontothatcauseforwhichtheygavethelastpfullmeasureofdevotionthatweherehighlyresolvethatthesedeadshallnothavediedinvainthatthisnationunsderGodshallhaveanewbirthoffreedomandthatgovernmentofthepeoplebythepeopleforthepeopleshallnotperishfromtheearth",
        983};

    QCOMPARE(rdi::longestPalindrome(test1.first), test1.second);
    QCOMPARE(rdi::longestPalindrome(test2.first), test2.second);
    QCOMPARE(rdi::longestPalindrome(test3.first), test3.second);
}

void Solution::commonChars()
{
    using Params = vector<string>;
    using Result = vector<string>;
    using Test = pair<Params, Result>;

    Test test1 = {{"bella", "label", "roller"}, {"e", "l", "l"}};
    Test test2 = {{"cool", "lock", "cook"}, {"c", "o"}};

    QCOMPARE(rdi::commonChars(test1.first), test1.second);
    QCOMPARE(rdi::commonChars(test2.first), test2.second);
}

void Solution::isNStraightHand()
{
    using Params = pair<vector<int>, int>;
    using Result = bool;
    using Test = pair<Params, Result>;

    Test test1 = {{{1, 2, 3, 6, 2, 3, 4, 7, 8}, 3}, true};
    Test test2 = {{{1, 2, 3, 4, 5}, 4}, false};
    Test test3 = {{{8, 10, 12}, 3}, false};

    QCOMPARE(rdi::isNStraightHand(test1.first.first, test1.first.second), test1.second);
    QCOMPARE(rdi::isNStraightHand(test2.first.first, test2.first.second), test2.second);
    QCOMPARE(rdi::isNStraightHand(test3.first.first, test3.first.second), test3.second);
}

void Solution::replaceWords()
{
    using Params = pair<vector<string>, string>;
    using Result = string;
    using Test = pair<Params, Result>;

    Test test1 = {{{"cat", "bat", "rat"}, "the cattle was rattled by the battery"},
                  "the cat was rat by the bat"};
    Test test2 = {{{"a", "b", "c"}, "aadsfasf absbs bbab cadsfafs"}, "a a b c"};

    QCOMPARE(rdi::replaceWords(test1.first.first, test1.first.second), test1.second);
    QCOMPARE(rdi::replaceWords(test2.first.first, test2.first.second), test2.second);

    /****************************/
    /******Test time limit*******/
    /****************************/
    QFile fileSentence(ROOT_PATH "/data/replaceWords/sentence.txt");
    QFile fileDict(ROOT_PATH "/data/replaceWords/dict.txt");
    QFile fileResult(ROOT_PATH "/data/replaceWords/res.txt");

    if (fileSentence.open(QIODevice::ReadOnly | QIODevice::Text) &&
        fileDict.open(QIODevice::ReadOnly | QIODevice::Text) &&
        fileResult.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::string sentence = fileSentence.readAll().toStdString();
        QStringList lst = QString(fileDict.readAll()).split(",");
        std::vector<std::string> dictionary;
        dictionary.reserve(lst.size());
        std::string res = fileResult.readAll().toStdString();

        for (QString &word : lst) {
            word.remove('\n');
            dictionary.emplace_back(word.toStdString());
        }
        rdi::TimeMeter<std::chrono::milliseconds> meter;
        QCOMPARE(rdi::replaceWords(dictionary, sentence), res);
        auto timestamp = meter.currentTime();

        if (timestamp > 2000) {
            std::cout << "Total milliseconds replace words from hard test: " << timestamp
                      << std::endl;
            std::cout << "Test failed in time" << std::endl;
            std::cout << "For tests to pass, each test must run at most 2000 milliseconds"
                      << std::endl;
            QCOMPARE(true, false);
        }
    } else {
        std::cerr << "Failed to load data for complex word replacement test" << std::endl;
    }
    /****************************/
}

void Solution::heightChecker()
{
    using Params = vector<int>;
    using Result = int;
    using Test = pair<Params, Result>;

    Test test1 = {{1, 1, 4, 2, 1, 3}, 3};
    Test test2 = {{5, 1, 2, 3, 4}, 5};
    Test test3 = {{1, 2, 3, 4, 5}, 0};

    QCOMPARE(rdi::heightChecker(test1.first), test1.second);
    QCOMPARE(rdi::heightChecker(test2.first), test2.second);
    QCOMPARE(rdi::heightChecker(test3.first), test3.second);
}

void Solution::getMinDistance()
{
    using Params = std::tuple<vector<int>, int, int>;
    using Result = int;
    using Test = pair<Params, Result>;

    Test test1 = {{{1, 2, 3, 4, 5}, 5, 3}, 1};
    Test test2 = {{{1}, 1, 0}, 0};
    Test test3 = {{{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 1, 0}, 0};

    QCOMPARE(rdi::getMinDistance(std::get<0>(test1.first), std::get<1>(test1.first),
                                 std::get<2>(test1.first)),
             test1.second);
    QCOMPARE(rdi::getMinDistance(std::get<0>(test2.first), std::get<1>(test2.first),
                                 std::get<2>(test2.first)),
             test2.second);
    QCOMPARE(rdi::getMinDistance(std::get<0>(test3.first), std::get<1>(test3.first),
                                 std::get<2>(test3.first)),
             test3.second);
}

void Solution::minMovesToSeat()
{
    using Params = pair<vector<int>, vector<int>>;
    using Result = int;
    using Test = pair<Params, Result>;

    Test test1 = {{{3, 1, 5}, {2, 7, 4}}, 4};
    Test test2 = {{{4, 1, 5, 9}, {1, 3, 2, 6}}, 7};
    Test test3 = {{{2, 2, 6, 6}, {1, 3, 2, 6}}, 4};

    QCOMPARE(rdi::minMovesToSeat(test1.first.first, test1.first.second), test1.second);
    QCOMPARE(rdi::minMovesToSeat(test2.first.first, test2.first.second), test2.second);
    QCOMPARE(rdi::minMovesToSeat(test3.first.first, test3.first.second), test3.second);
}

void Solution::removeOccurrences()
{
    using Params = pair<string, string>;
    using Result = string;
    using Test = pair<Params, Result>;

    Test test1 = {{"daabcbaabcbc", "abc"}, "dab"};
    Test test2 = {{"axxxxyyyyb", "xy"}, "ab"};
    Test test3 = {
        {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
         "a"},
        ""};

    QCOMPARE(rdi::removeOccurrences(test1.first.first, test1.first.second), test1.second);
    QCOMPARE(rdi::removeOccurrences(test2.first.first, test2.first.second), test2.second);
    QCOMPARE(rdi::removeOccurrences(test3.first.first, test3.first.second), test3.second);
}

void Solution::minIncrementForUnique()
{
    using Params = vector<int>;
    using Result = int;
    using Test = pair<Params, Result>;

    Test test1 = {{1, 2, 2}, 1};
    Test test2 = {{3, 2, 1, 2, 1, 7}, 6};
    Test test3 = {{7, 7, 7, 7, 7, 7}, 15};
    Test test4 = {{8, 7, 8, 9}, 2};

    QCOMPARE(rdi::minIncrementForUnique(test1.first), test1.second);
    QCOMPARE(rdi::minIncrementForUnique(test2.first), test2.second);
    QCOMPARE(rdi::minIncrementForUnique(test3.first), test3.second);
    QCOMPARE(rdi::minIncrementForUnique(test4.first), test4.second);
}

void Solution::maxProfitAssignment()
{
    using Params = std::tuple<vector<int>, vector<int>, vector<int>>;
    using Result = int;
    using Test = pair<Params, Result>;

    Test test1 = {{{2, 4, 6, 8, 10}, {10, 20, 30, 40, 50}, {4, 5, 6, 7}}, 100};
    Test test2 = {{{85, 47, 57}, {24, 66, 99}, {40, 25, 25}}, 0};
    Test test3 = {{{68, 35, 52, 47, 86}, {67, 17, 1, 81, 3}, {92, 10, 85, 84, 82}}, 324};

    QCOMPARE(rdi::maxProfitAssignment(std::get<0>(test1.first), std::get<1>(test1.first),
                                      std::get<2>(test1.first)),
             test1.second);
    QCOMPARE(rdi::maxProfitAssignment(std::get<0>(test2.first), std::get<1>(test2.first),
                                      std::get<2>(test2.first)),
             test2.second);
    QCOMPARE(rdi::maxProfitAssignment(std::get<0>(test3.first), std::get<1>(test3.first),
                                      std::get<2>(test3.first)),
             test3.second);
}

void Solution::minDays()
{
    using Params = std::tuple<vector<int>, int, int>;
    using Result = int;
    using Test = pair<Params, Result>;

    Test test1 = {{{1, 10, 3, 10, 2}, 3, 1}, 3};
    Test test2 = {{{1, 10, 3, 10, 2}, 3, 2}, -1};
    Test test3 = {{{7, 7, 7, 7, 12, 7, 7}, 2, 3}, 12};

    QCOMPARE(rdi::minDays(std::get<0>(test1.first), std::get<1>(test1.first),
                          std::get<2>(test1.first)),
             test1.second);
    QCOMPARE(rdi::minDays(std::get<0>(test2.first), std::get<1>(test2.first),
                          std::get<2>(test2.first)),
             test2.second);
    QCOMPARE(rdi::minDays(std::get<0>(test3.first), std::get<1>(test3.first),
                          std::get<2>(test3.first)),
             test3.second);
}

void Solution::maxSatisfied()
{
    using Params = std::tuple<vector<int>, vector<int>, int>;
    using Result = int;
    using Test = pair<Params, Result>;

    Test test1 = {{{1, 0, 1, 2, 1, 1, 7, 5}, {0, 1, 0, 1, 0, 1, 0, 1}, 3}, 16};
    Test test2 = {{{1}, {0}, 1}, 1};

    QCOMPARE(rdi::maxSatisfied(std::get<0>(test1.first), std::get<1>(test1.first),
                               std::get<2>(test1.first)),
             test1.second);
    QCOMPARE(rdi::maxSatisfied(std::get<0>(test2.first), std::get<1>(test2.first),
                               std::get<2>(test2.first)),
             test2.second);
}

void Solution::minDifference()
{
    using Params = std::vector<int>;
    using Result = int;
    using Test = pair<Params, Result>;

    Test test1 = {{5, 3, 2, 4}, 0};
    Test test2 = {{1, 5, 0, 10, 14}, 1};
    Test test3 = {{3, 100, 20}, 0};

    QCOMPARE(rdi::minDifference(test1.first), test1.second);
    QCOMPARE(rdi::minDifference(test2.first), test2.second);
    QCOMPARE(rdi::minDifference(test3.first), test3.second);
}

void Solution::mergeNodes()
{
    using Params = ListNode *;
    using Result = ListNode *;
    using Test = pair<Params, Result>;

    Test test1 = {ListNode::toListNode({0, 3, 1, 0, 4, 5, 2, 0}),
                  ListNode::toListNode({4, 11})};
    Test test2 = {ListNode::toListNode({0, 1, 0, 3, 0, 2, 2, 0}),
                  ListNode::toListNode({1, 3, 4})};

    QCOMPARE(ListNode::toVector(rdi::mergeNodes(test1.first)),
             ListNode::toVector(test1.second));
    QCOMPARE(ListNode::toVector(rdi::mergeNodes(test2.first)),
             ListNode::toVector(test2.second));
}

void Solution::averageWaitingTime()
{
    using Params = vector<vector<int>>;
    using Result = double;
    using Test = pair<Params, Result>;

    Test test1 = {{{1, 2}, {2, 5}, {4, 3}}, 5.0};
    Test test2 = {{{5, 2}, {5, 4}, {10, 3}, {20, 1}}, 3.25};

    QCOMPARE(rdi::averageWaitingTime(test1.first), test1.second);
    QCOMPARE(rdi::averageWaitingTime(test2.first), test2.second);
}

void Solution::reverseParentheses()
{
    using Params = string;
    using Result = string;
    using Test = pair<Params, Result>;

    Test test1 = {"(abcd)", "dcba"};
    Test test2 = {"(u(love)i)", "iloveu"};
    Test test3 = {"(ed(et(oc))el)", "leetcode"};

    QCOMPARE(rdi::reverseParentheses(test1.first), test1.second);
    QCOMPARE(rdi::reverseParentheses(test2.first), test2.second);
    QCOMPARE(rdi::reverseParentheses(test3.first), test3.second);
}

void Solution::maxProduct()
{
    using Params = vector<int>;
    using Result = int;
    using Test = pair<Params, Result>;

    Test test1 = {{2, 3, -2, 4}, 6};
    Test test2 = {{-2, 0, -1}, 0};
    Test test3 = {
        {0, 10, 10, 10, 10, 10, 10, 10, 10, 10, -10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 0},
        1000000000};

    QCOMPARE(rdi::maxProduct(test1.first), test1.second);
    QCOMPARE(rdi::maxProduct(test2.first), test2.second);
    QCOMPARE(rdi::maxProduct(test3.first), test3.second);
}

void Solution::findSubsequences()
{
    using Params = vector<int>;
    using Result = vector<vector<int>>;
    using Test = pair<Params, Result>;

    Test test1 = {
        {4, 6, 7, 7},
        {{4, 6}, {4, 6, 7}, {4, 6, 7, 7}, {4, 7}, {4, 7, 7}, {6, 7}, {6, 7, 7}, {7, 7}}};

    Test test2 = {{4, 4, 3, 2, 1}, {{4, 4}}};

    auto res_test1 = rdi::findSubsequences(test1.first);
    std::sort(res_test1.begin(), res_test1.end());
    std::sort(test1.second.begin(), test1.second.end());

    auto res_test2 = rdi::findSubsequences(test2.first);
    std::sort(res_test2.begin(), res_test2.end());
    std::sort(test2.second.begin(), test2.second.end());

    QCOMPARE(res_test1, test1.second);
    QCOMPARE(res_test2, test2.second);
}

void Solution::minimumPushes()
{
    using Params = string;
    using Result = int;
    using Test = pair<Params, Result>;

    Test test1 = {"abcde", 5};
    Test test2 = {"xyzxyzxyzxyz", 12};
    Test test3 = {"aabbccddeeffgghhiiiiii", 24};

    QCOMPARE(rdi::minimumPushes(test1.first), test1.second);
    QCOMPARE(rdi::minimumPushes(test2.first), test2.second);
    QCOMPARE(rdi::minimumPushes(test3.first), test3.second);
}

void Solution::countTrapezoids()
{
    using Params = vector<vector<int>>;
    using Result = int;
    using Test = pair<Params, Result>;

    Test test1 = {{{1, 0}, {2, 0}, {3, 0}, {2, 2}, {3, 2}}, 3};
    Test test2 = {{{0, 0}, {1, 0}, {0, 1}, {2, 1}}, 1};

    QCOMPARE(rdi::countTrapezoids(test1.first), test1.second);
    QCOMPARE(rdi::countTrapezoids(test2.first), test2.second);
}
}}
