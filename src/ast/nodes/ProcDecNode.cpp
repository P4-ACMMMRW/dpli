#include <ProcDecNode.hpp>
#include <memory>

void ProcDecNode::addChild(std::shared_ptr<AstNode> node) {
    if (visitingParams) {
        paramNodes.push_back(std::move(node));
    } else {
        bodyNodes.push_back(std::move(node));
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
void ProcDecNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<ProcDecNode>(shared_from_this()));
};