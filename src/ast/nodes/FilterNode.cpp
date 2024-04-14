#include <FilterNode.hpp>

void FilterNode::addChild(std::shared_ptr<AstNode> node) {
    if (rightNode == nullptr) {
        rightNode = std::move(node);
    } else if (leftNode == nullptr) {
        leftNode = std::move(node);
    } else {
        throw std::runtime_error("FilterNode can only have two children");
    }
}

void FilterNode::print(std::string indent = "", std::string prefix = "") {
    std::cout << indent << prefix << AstNode::getText() << "\n";

    // Use a new level of indentation for the children
    std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

    // Print the leftNode child, if it exists
    if (leftNode != nullptr) {
        leftNode->print(childIndent, "├── ");
    }

    // Print the rightNode child, if it exists
    if (rightNode != nullptr) {
        rightNode->print(childIndent, "└── ");
    }
}

void FilterNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<FilterNode>(shared_from_this()));
};