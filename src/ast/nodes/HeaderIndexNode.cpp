#include <HeaderIndexNode.hpp>

void HeaderIndexNode::addChild(std::shared_ptr<AstNode> node) {
    if (right == nullptr) {
        right = std::move(node);
    } else if (left == nullptr) {
        left = std::move(node);
    } else {
        throw std::runtime_error("HeaderIndexNode can only have two children");
    }
}

void HeaderIndexNode::print(std::string indent = "", std::string prefix = "") {
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
