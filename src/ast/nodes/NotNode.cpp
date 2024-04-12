#include <NotNode.hpp>

void NotNode::addChild(AstNode* node)  {
    if (child == nullptr) {
        child = node;
    } else {
        throw std::runtime_error("NotNode can only have one child");
    }
}

void NotNode::print(std::string indent = "", std::string prefix = "")  {
    std::cout << indent << prefix << AstNode::getText() << "\n";

    // Use a new level of indentation for the children
    std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

    // Print the child node, if it exists
    if (child != nullptr) {
        child->print(childIndent, "└── ");
    }
}
