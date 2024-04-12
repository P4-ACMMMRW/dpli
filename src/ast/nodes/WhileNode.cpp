#include <WhileNode.hpp>

void WhileNode::addChild(AstNode* node) {
    if (condNode == nullptr) condNode = node;
    else stmNodes.push_back(node);
}

void WhileNode::print(std::string indent = "", std::string prefix = "") {
    std::cout << indent << prefix << AstNode::getText() << "\n";

    // Use a new level of indentation for the children
    std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

    // Print the condition node, if it exists
    if (condNode != nullptr) {
        condNode->print(childIndent, "├── ");
    }

    // Print each statement node
    for (size_t i = 0; i < stmNodes.size(); ++i) {
        // For the last statement node, we want to print a different prefix
        if (i == stmNodes.size() - 1) {
            stmNodes[i]->print(childIndent, "└── ");
        } else {
            stmNodes[i]->print(childIndent, "├── ");
        }
    }
}