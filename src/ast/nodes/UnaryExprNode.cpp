#include <UnaryExprNode.hpp>
#include <memory>

void UnaryExprNode::addChild(std::shared_ptr<AstNode> child) { this->childNode = std::move(child); }

void UnaryExprNode::print(std::string indent = "", std::string prefix = "") {
    std::cout << indent << prefix << AstNode::getText() << "\n";

    // Use a new level of indentation for the children
    std::string childIndent = indent + (prefix.empty() ? "" : "    ");

    // Print the childNode node, if it exists
    if (childNode != nullptr) {
        childNode->print(childIndent, "└── ");
    }
}

void UnaryExprNode::accept(AstVisitor* visitor) { visitor->visit(this); };