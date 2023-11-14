#include <iostream>
#include <string>
#include <memory>
#include <vector>

struct ExpressionNode {
    std::string operation; 
    std::shared_ptr<ExpressionNode> left;
    std::shared_ptr<ExpressionNode> right;

    ExpressionNode(const std::string& op, std::shared_ptr<ExpressionNode> l = nullptr,
        std::shared_ptr<ExpressionNode> r = nullptr)
        : operation(op), left(l), right(r) {}
};

void swapLeftAndRight(std::shared_ptr<ExpressionNode>& root) {
    if (!root) {
        return;
    }

    // Swap the left and right child nodes (if they exist)
    std::swap(root->left, root->right);

    // Recursively swap the child subtrees
    swapLeftAndRight(root->left);
    swapLeftAndRight(root->right);
    // std::cout << "Tree Left and Right swapped at " << root->operation << " " << std::endl;
}

double evaluateExpression(const std::shared_ptr<ExpressionNode>& root, const std::string& variable, double value) {
    if (!root) {
        return 0.0;
    }

    if (root->operation == variable) {
        return value;
    }
    else if (root->operation == "+") {
        return evaluateExpression(root->left, variable, value) + evaluateExpression(root->right, variable, value);
    }
    else if (root->operation == "-") {
        return evaluateExpression(root->left, variable, value) - evaluateExpression(root->right, variable, value);
    }
    else if (root->operation == "*") {
        return evaluateExpression(root->left, variable, value) * evaluateExpression(root->right, variable, value);
    }
    else if (root->operation == "/") {
        double denominator = evaluateExpression(root->right, variable, value);
        if (denominator != 0.0) {
            return evaluateExpression(root->left, variable, value) / denominator;
        }
        else {
            std::cerr << "Error: Division by zero" << std::endl;
            exit(1);
        }
    }
    // assumes numeric value of string, returns numeric value converted from string
    else {
        return std::stod(root->operation);
    }
}

void printExpression(const std::shared_ptr<ExpressionNode>& root) {
    if (!root) {
        return;
    }
    // if it is not an atom, show as list
    if (root->left || root->right) {
        std::cout << "(";
    }

    std::cout << root->operation;
 
    if (root->left || root->right) {
        if (root->left) {
            std::cout << " ";
            printExpression(root->left);
        }
        if (root->right) {
            std::cout << " ";
            printExpression(root->right);
        }
        std::cout << ")";
    }
}

int main() {
    std::vector<std::shared_ptr<ExpressionNode>> expressionList;


    std::shared_ptr<ExpressionNode> expressionTree =
        std::make_shared<ExpressionNode>("+",
            std::make_shared<ExpressionNode>("*",
                std::make_shared<ExpressionNode>("3"),
                std::make_shared<ExpressionNode>("x")
            ),
            std::make_shared<ExpressionNode>("2")
        );

    swapLeftAndRight(expressionTree);
    printExpression(expressionTree);

    expressionList.push_back(expressionTree);

    std::cout << "Testing Swap Expression..." << std::endl;
    swapLeftAndRight(expressionTree);
    printExpression(expressionTree);
    std::string variable = "x";

    double value = 5.0;

    
    double result = evaluateExpression(expressionTree,
                                        variable, value);

    std::cout << "Tree Result Rewritten: " << result << std::endl;

    return 0;
}
