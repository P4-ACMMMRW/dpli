#include <ColumnNode.hpp>

void ColumnNode::addChild(std::shared_ptr<AstNode> node) {
    if (child == nullptr) {
        child = std::move(node);
    } else {
        throw std::runtime_error("ColumnNode can only have one child");
    }
}

void ColumnNode::print(std::string indent = "", std::string prefix = "") {
    std::cout << indent << prefix << AstNode::getText() << "\n";

    // Use a new level of indentation for the children
    std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

    // Print the child node, if it exists
    if (child != nullptr) {
        child->print(childIndent, "└── ");
    }
}
