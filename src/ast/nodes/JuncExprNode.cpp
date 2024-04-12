#include <JuncExprNode.hpp>

void JuncExprNode::addChild(AstNode* node) {
    if (left == nullptr) {
        left = node;
    } else if (right == nullptr) {
        right = node;
    } else {
        throw std::runtime_error("ExprNode can only have two children");
    }
}

void JuncExprNode::print(std::string indent = "", std::string prefix = "") {
    std::cout << indent << prefix << AstNode::getText() << "\n";

    // Use a new level of indentation for the children
    std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

    // Print the left child, if it exists
    if (left != nullptr) {
        left->print(childIndent, "├── ");
    }

    // Print the right child, if it exists
    if (right != nullptr) {
        right->print(childIndent, "└── ");
    }
}
