#include <CompExprNode.hpp>

void CompExprNode::addChild(std::shared_ptr<AstNode> node) {
    if (leftNode == nullptr) {
        leftNode = std::move(node);
    } else if (rightNode == nullptr) {
        rightNode = std::move(node);
    } else {
        throw std::runtime_error("CompExprNode already has two children");
    }
}

void CompExprNode::print(std::string indent = "", std::string prefix = "") {
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
void CompExprNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<CompExprNode>(shared_from_this()));
};