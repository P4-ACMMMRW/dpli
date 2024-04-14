#include <ReturnNode.hpp>

void ReturnNode::addChild(std::shared_ptr<AstNode> node) {
    if (childNode == nullptr) {
        childNode = std::move(node);
    } else {
        throw std::runtime_error("NotNode can only have one child");
    }
}

void ReturnNode::print(std::string indent = "", std::string prefix = "") {
    std::cout << indent << prefix << AstNode::getText() << "\n";

    // Use a new level of indentation for the children
    std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

    // Print the childNode node, if it exists
    if (childNode != nullptr) {
        childNode->print(childIndent, "└── ");
    }
}
void ReturnNode::accept(AstVisitor* visitor) { visitor->visit(this); };