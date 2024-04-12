#include <ElseNode.hpp>

void ElseNode::addChild(AstNode* node) { bodyNodes.push_back(node); }

void ElseNode::print(std::string indent = "", std::string prefix = "") {
    std::cout << indent << prefix << AstNode::getText() << "\n";

    // Use a new level of indentation for the children
    std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

    // Print each if statement node
    for (size_t i = 0; i < bodyNodes.size(); ++i) {
        // For the last if statement node, we want to print a different prefix
        if (i == bodyNodes.size() - 1) {
            bodyNodes[i]->print(childIndent, "└── ");
        } else {
            bodyNodes[i]->print(childIndent, "├── ");
        }
    }
}
