#include <ProgNode.hpp>

void ProgNode::addChild(std::shared_ptr<AstNode> child) { children.push_back(child); }

void ProgNode::print(std::string indent, std::string prefix) {
    std::cout << indent << prefix << AstNode::getText() << "\n";

    std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

    for (size_t i = 0; i < children.size(); ++i) {
        if (i == children.size() - 1) {
            children[i]->print(childIndent, "└── ");
        } else {
            children[i]->print(childIndent, "├── ");
        }
    }
}