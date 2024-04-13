#include <NotNode.hpp>

void NotNode::addChild(std::shared_ptr<AstNode> node) {
    if (child == nullptr) {
        child = node;
    } else {
        throw std::runtime_error("NotNode can only have one child");
    }
}

void NotNode::print(std::string indent, std::string prefix) {
    std::cout << indent << prefix << AstNode::getText() << "\n";

    std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

    if (child != nullptr) {
        child->print(childIndent, "└── ");
    }
}