// TreeRewriter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

TreeNode* rewriteTree(TreeNode* node, short operation, int value) {
    if (node == nullptr) {
        return nullptr;
    }

    if (operation == 0) {
        node->data += value;
    }
    

    node->left = rewriteTree(node->left, operation, value);
    node->right = rewriteTree(node->right, operation, value);

    return node;
}

void printTree(TreeNode* node) {
    if (node == nullptr) {
        return;
    }

    printTree(node->left);
    std::cout << node->data << " ";
    printTree(node->right);
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    std::cout << "Original tree: ";
    printTree(root);
    std::cout << std::endl;

    root = rewriteTree(root, 0, 10);

    std::cout << "Rewritten tree: ";
    printTree(root);
    std::cout << std::endl;

    return 0;
}
