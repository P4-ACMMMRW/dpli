#include <ProcCallNode.hpp>

void ProcCallNode::addChild(std::shared_ptr<AstNode> node) {
    if (visitingParams) {
        argNodes.push_back(std::move(node));
    } else if (proc == nullptr) {
        proc = std::move(node);
    } else {
        throw std::runtime_error(
            "ProcCallNode can add more children after stopped visitingParams and procdure has been "
            "added");
    }
}

void ProcCallNode::print(std::string indent = "", std::string prefix = "") {
    std::cout << indent << prefix << AstNode::getText() << " proccall"
              << "\n";

    // Use a new level of indentation for the children
    std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

    if (proc != nullptr) {
        proc->print(childIndent, (argNodes.empty()) ? "└── " : "├── Name: ");
    }

    // Print each if statement node
    for (size_t i = 0; i < argNodes.size(); ++i) {
        // For the last if statement node, we want to print a different prefix
        if (i == argNodes.size() - 1) {
            argNodes[i]->print(childIndent, "└── ");
        } else {
            argNodes[i]->print(childIndent, "├── ");
        }
    }
}
void ProcCallNode::accept(std::shared_ptr<AstVisitor> visitor) { visitor->visit(std::static_pointer_cast<ProcCallNode>(shared_from_this())); };