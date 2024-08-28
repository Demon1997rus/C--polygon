#pragma once

#include <queue>

#include <iostream>

namespace rdi {
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
inline void treeNodePrint(TreeNode *root)
{
    if (root == nullptr) {
        return;
    }
    std::queue<std::string> q_str;
    std::queue<TreeNode *> q_node;
    q_node.push(root);

    while (!q_node.empty()) {
        TreeNode *node = q_node.front();
        q_node.pop();

        if (node) {
            q_str.push(std::to_string(node->val));
            q_node.push(node->left);
            q_node.push(node->right);
        } else {
            q_str.push("null");
        }
    }

    std::cout << "[";
    while (!q_str.empty()) {
        std::string str = std::move(q_str.front());
        q_str.pop();
        if (q_str.empty()) {
            std::cout << str;
        } else {
            std::cout << str << ",";
        }
    }
    std::cout << "]" << std::endl;
}

inline void destruct_node(TreeNode *root)
{
    if (!root) {
        return;
    }
    destruct_node(root->left);
    destruct_node(root->right);
    delete root;
    root = nullptr;
}
}
