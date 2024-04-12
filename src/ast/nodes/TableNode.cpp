#include <TableNode.hpp>

void TableNode::addChild(AstNode* node) {
    columnNodes.push_back(node);
}

void TableNode::print(std::string indent = "", std::string prefix = "") {
    std::cout << indent << prefix << AstNode::getText() << "\n";

    // Use a new level of indentation for the children
    std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

    // Print each column node
    for (size_t i = 0; i < columnNodes.size(); ++i) {
        // For the last column node, we want to print a different prefix
        if (i == columnNodes.size() - 1) {
            columnNodes[i]->print(childIndent, "└── ");
        } else {
            columnNodes[i]->print(childIndent, "├── ");
        }
    }
}
