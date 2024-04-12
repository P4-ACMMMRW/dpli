#include <UnaryExprNode.hpp>

void UnaryExprNode::addChild(AstNode* child) { this->child = child; }

void UnaryExprNode::print(std::string indent = "", std::string prefix = "") {
    std::cout << indent << prefix << AstNode::getText() << "\n";

    // Use a new level of indentation for the children
    std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "    "));

    // Print the child node, if it exists
    if (child != nullptr) {
        child->print(childIndent, "└── ");
    }
}
