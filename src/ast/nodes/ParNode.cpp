#include <ParNode.hpp>

void ParNode::addChild(AstNode* node) {
    if (childNode == nullptr) {
        childNode = node;
    } else {
        throw std::runtime_error("ParNode can only have one child");
    }
}

void ParNode::print(std::string indent = "", std::string prefix = "") {
    std::cout << indent << prefix << AstNode::getText() << "\n";

    // Use a new level of indentation for the children
    std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

    // Print the condition node, if it exists
    if (childNode != nullptr) {
        childNode->print(childIndent, "└── ");
    }
}
