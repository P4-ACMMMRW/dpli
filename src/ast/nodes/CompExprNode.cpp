#include <CompExprNode.hpp>

void CompExprNode::addChild(std::shared_ptr<AstNode> node) {
    if (left == nullptr) {
        left = std::move(node);
    } else if (right == nullptr) {
        right = std::move(node);
    } else {
        throw std::runtime_error("CompExprNode already has two children");
    }
}

void CompExprNode::print(std::string indent = "", std::string prefix = "") {
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
