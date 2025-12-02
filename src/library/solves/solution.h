#pragma once

#include <QObject>
#include <QtTest>

namespace rdi { namespace unit_test {
class Solution : public QObject {
    Q_OBJECT

private slots:
    void productExceptSelf();
    void lengthOfLongestSubstring();
    void findMinArrowShots();
    void leastInterval();
    void mergeInBeetween();
    void isPalindrome();
    void maxDepth();
    void numIslands();
    void findMaxK();
    void removeNodes();
    void doubleIt();
    void asteroidsDestroyed();
    void canBeEqual();
    void appendCharacters();
    void longestPalindrome();
    void commonChars();
    void isNStraightHand();
    void replaceWords();
    void heightChecker();
    void getMinDistance();
    void minMovesToSeat();
    void removeOccurrences();
    void minIncrementForUnique();
    void maxProfitAssignment();
    void minDays();
    void maxSatisfied();
    void minDifference();
    void mergeNodes();
    void averageWaitingTime();
    void reverseParentheses();
    void maxProduct();
    void findSubsequences();
    void minimumPushes();
    void countTrapezoids();
    void minOperations();
};
}}

#define INIT_UNIT_TEST_SOLVES QTEST_MAIN(rdi::unit_test::Solution)
