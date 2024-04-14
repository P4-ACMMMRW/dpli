#include <WhileNode.hpp>

void WhileNode::addChild(std::shared_ptr<AstNode> node) {
    if (condNode == nullptr) {
        condNode = std::move(node);
    } else {
        stmNodes.push_back(std::move(node));
    }
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
void WhileNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<WhileNode>(shared_from_this()));
};