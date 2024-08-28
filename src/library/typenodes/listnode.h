#pragma once

#include <iostream>
#include <vector>

namespace rdi {
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}

    static std::vector<int> toVector(ListNode *node)
    {
        std::vector<int> res;
        while (node) {
            res.push_back(node->val);
            node = node->next;
        }
        return res;
    }

    static void printListNode(ListNode *head)
    {
        if (head == nullptr) {
            return;
        }
        ListNode *temp = head;
        while (temp != nullptr) {
            std::cout << temp->val << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    static ListNode *toListNode(const std::vector<int> &nums)
    {
        if (nums.empty()) {
            return nullptr;
        }
        ListNode *test = new ListNode(nums[0]);
        ListNode *temp = test;
        for (int i = 1; i < (int) nums.size(); ++i) {
            temp->next = new ListNode(nums[i]);
            temp = temp->next;
        }
        return test;
    }

    static void destruct_node(ListNode *node)
    {
        if (node == nullptr) {
            return;
        }
        destruct_node(node->next);
        delete node;
        node = nullptr;
    }
};
}
