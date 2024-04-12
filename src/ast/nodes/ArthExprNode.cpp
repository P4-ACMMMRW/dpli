#include <ArthExprNode.hpp>

void ArthExprNode::addChild(AstNode* child) {
    if (left == nullptr)       left = child;
    else if (right == nullptr) right = child;
    else throw std::runtime_error("ArthExprNode already has two children");
}

void ArthExprNode::print(std::string indent = "", std::string prefix = "") {
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
