#include <iostream>
#include <string>
#include <memory>


struct ExpressionNode {
    std::string operation; 
    std::shared_ptr<ExpressionNode> left;
    std::shared_ptr<ExpressionNode> right;

    ExpressionNode(const std::string& op, std::shared_ptr<ExpressionNode> l = nullptr, std::shared_ptr<ExpressionNode> r = nullptr)
        : operation(op), left(l), right(r) {}
};

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
    else {
        return std::stod(root->operation);
    }
}

int main() {
    
    std::shared_ptr<ExpressionNode> expressionTree =
        std::make_shared<ExpressionNode>("+",
            std::make_shared<ExpressionNode>("*",
                std::make_shared<ExpressionNode>("2"),
                std::make_shared<ExpressionNode>("x")
            ),
            std::make_shared<ExpressionNode>("3")
        );

 
    std::string variable = "x";
    double value = 5.0;

    
    double result = evaluateExpression(expressionTree, variable, value);

    std::cout << "Result: " << result << std::endl;

    return 0;
}
