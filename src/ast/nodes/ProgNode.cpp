#include <ProgNode.hpp>

void ProgNode::addChild(AstNode* child) { children.push_back(child); }

void ProgNode::print(std::string indent = "", std::string prefix = ""){
    //std::cout << indent << prefix << ruleName << "   (" + text +")" << "\n";
    std::cout << indent << prefix << AstNode::getText() << "\n";

    // Use a new level of indentation for the children
    std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

    for (size_t i = 0; i < children.size(); ++i) {
        // For the last child, we want to print a different prefix
        if (i == children.size() - 1) {
            children[i]->print(childIndent, "└── ");
        } else {
            children[i]->print(childIndent, "├── ");
        }
    }
}
