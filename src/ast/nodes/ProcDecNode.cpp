#include <ProcDecNode.hpp>

void ProcDecNode::addChild(AstNode* node) {
    if (visitingParams) {
        paramNodes.push_back(node);
    } else {
        bodyNodes.push_back(node);
    }
}

void ProcDecNode::print(std::string indent = "", std::string prefix = "") {
    std::cout << indent << prefix << "def " << getName() << "():"
              << "\n";

    std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

    for (size_t i = 0; i < paramNodes.size(); ++i) {
        paramNodes[i]->print(childIndent, "├── param: ");
    }

    for (size_t i = 0; i < bodyNodes.size(); ++i) {
        // For the last statement node, we want to print a different prefix
        if (i == bodyNodes.size() - 1) {
            bodyNodes[i]->print(childIndent, "└── ");
        } else {
            bodyNodes[i]->print(childIndent, "├── ");
        }
    }
}
