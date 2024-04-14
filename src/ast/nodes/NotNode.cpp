#include <NotNode.hpp>

void NotNode::addChild(std::shared_ptr<AstNode> node) {
    if (childNode == nullptr) {
        childNode = node;
    } else {
        throw std::runtime_error("NotNode can only have one child");
    }
}

void NotNode::print(std::string indent, std::string prefix) {
    std::cout << indent << prefix << AstNode::getText() << "\n";

    std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

    if (childNode != nullptr) {
        childNode->print(childIndent, "└── ");
    }
}

void NotNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<NotNode>(shared_from_this()));
};