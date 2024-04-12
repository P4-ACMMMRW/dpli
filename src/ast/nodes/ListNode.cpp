#include <ListNode.hpp>

void ListNode::addChild(AstNode* node) { children.push_back(node); }

void ListNode::print(std::string indent = "", std::string prefix = "") {
    std::cout << indent << prefix << AstNode::getText() << "\n";

    // Use a new level of indentation for the children
    std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

    // Print all children nodes
    for (size_t i = 0; i < children.size(); i++) {
        if (children[i] != nullptr) {
            std::string childPrefix = (i == children.size() - 1) ? "└── " : "├── ";
            children[i]->print(childIndent, childPrefix);
        }
    }
}
