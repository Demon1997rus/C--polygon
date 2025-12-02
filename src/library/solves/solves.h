#pragma once

#include <queue>

#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <boost/sort/spreadsort/integer_sort.hpp>

#include "../../library/general/functions.h"
#include "../typenodes/listnode.h"

using namespace std;

namespace rdi {
vector<vector<int>> threeSum(vector<int> &nums);

int maxProfit(vector<int> &prices);

int countPairs(vector<int> &nums, int target);

bool isPalindrome(string s);

void reverseSentence(string &sentence);

bool searchPair(vector<int> &nums, int k, int t);

vector<string> generateParenthesis(int n);

vector<int> sequentialNumbers(int low, int high);

int longestValidParentheses(string s);

ListNode *mergeKLists(vector<ListNode *> &lists);

bool isAnagram(const string &s1, const string &s2);

vector<vector<string>> groupAnagrams(vector<string> &strs);

bool isValidSudoku(vector<vector<char>> &board);

void rotateReverse(vector<vector<int>> &matrix);

string compressedString(const string &str);

int findCustomSubstr(string str, string target);

int lengthOfLastWord(string s);

int removeElement(vector<int> &nums, int target);

int majorityElement(vector<int> &nums);

ListNode *deleteDuplicates(ListNode *head);

vector<int> rearrangeArray(vector<int> &nums);

long long largestPerimeter(vector<int> &nums);

int findLeastNumOfUniqueInts(vector<int> &arr, int k);

int lengthOfLongestSubstring(string s);

string maximumOddBinaryNumber(string s);

ListNode *removeZeroSumSubLists(ListNode *head);

vector<int> productExceptSelf(vector<int> &nums);

int findMinArrowShots(vector<vector<int>> &points);

int leastInterval(const vector<char> &tasks, int n);

ListNode *mergeInBeetween(ListNode *list1, int a, int b, ListNode *list2);

bool isPalindrome(ListNode *head);

int maxDepth(string s);

int numIslands(vector<vector<char>> &grid);

int findMaxK(vector<int> &nums);

ListNode *removeNodes(ListNode *head);

ListNode *doubleIt(ListNode *head);

bool asteroidsDestroyed(int mass, vector<int> &asteroids);

bool canBeEqual(vector<int> &target, vector<int> &arr);

int appendCharacters(string s, string t);

int longestPalindrome(string s);

vector<string> commonChars(vector<string> &words);

bool isNStraightHand(vector<int> &hand, int groupSize);

string replaceWords(vector<string> &dictionary, string sentence);

int heightChecker(vector<int> &heights);

int getMinDistance(vector<int> &nums, int target, int start);

int minMovesToSeat(vector<int> &seats, vector<int> &students);

string removeOccurrences(string s, string part);

int minIncrementForUnique(vector<int> &nums);

int maxProfitAssignment(vector<int> &difficulty, vector<int> &profit, vector<int> &worker);

int minDays(vector<int> &bloomDay, int m, int k);

int maxSatisfied(vector<int> &customers, vector<int> &grumpy, int minutes);

int minDifference(vector<int> &nums);

ListNode *mergeNodes(ListNode *head);

double averageWaitingTime(vector<vector<int>> &customers);

string reverseParentheses(string s);

int maxProduct(vector<int> &nums);

vector<vector<int>> findSubsequences(vector<int> &nums);

pair<int, int> getPairAscendingOrDescending(const vector<int> &nums);

pair<int, int> getPairTargetSumSubArray(const vector<int> &nums, int target);

int minimumPushes(string word);

int countTrapezoids(vector<vector<int>> &points);

int minOperations(vector<int> &nums);

/*!
 * \brief The MyStack class - класс реализовывает функционал стека с дополнительной функций max,
 * которая показывает максимальное число в стеке за O(1)
 */
class MyStack {
public:
    int pop() // О(1)
    {
        int temp = nums.top();
        nums.pop();
        if (maxNums.top() == temp) {
            maxNums.pop();
        }
        return temp;
    }

    void push(int value) // О(1)
    {
        nums.push(value);
        if (maxNums.empty()) {
            maxNums.push(value);
        } else {
            if (maxNums.top() <= value) {
                maxNums.push(value);
            }
        }
    }

    int max() const // О(1)
    {
        return maxNums.top();
    }

private:
    stack<int> nums;
    stack<int> maxNums;
};
}
