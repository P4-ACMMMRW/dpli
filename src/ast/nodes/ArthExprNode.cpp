#include <ArthExprNode.hpp>

void ArthExprNode::addChild(std::shared_ptr<AstNode> child) {
    if (leftNode == nullptr) {
        leftNode = std::move(child);
    } else if (rightNode == nullptr) {
        rightNode = std::move(child);
    } else {
        throw std::runtime_error("ArthExprNode already has two children");
    }
}

void ArthExprNode::print(std::string indent = "", std::string prefix = "") {
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
void ArthExprNode::accept(AstVisitor* visitor) { visitor->visit(this); };