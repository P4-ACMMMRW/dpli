#include <ParNode.hpp>
#include <memory>

void ParNode::addChild(std::shared_ptr<AstNode> node) {
    if (childNode == nullptr) {
        childNode = std::move(node);
    } else {
        throw std::runtime_error("ParNode can only have one child");
    }
}

void ParNode::print(std::string indent = "", std::string prefix = "") {
    std::cout << indent << prefix << AstNode::getText() << "\n";

    // Use a new level of indentation for the children
    std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

    // Print the condition node, if it exists
    if (childNode != nullptr) {
        childNode->print(childIndent, "└── ");
    }
}

void ParNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<ParNode>(shared_from_this()));
};