#include <ColumnNode.hpp>

void ColumnNode::addChild(std::shared_ptr<AstNode> node) {
    if (childNode == nullptr) {
        childNode = std::move(node);
    } else {
        throw std::runtime_error("ColumnNode can only have one child");
    }
}

void ColumnNode::print(std::string indent = "", std::string prefix = "") {
    std::cout << indent << prefix << AstNode::getText() << "\n";

    // Use a new level of indentation for the children
    std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

    // Print the childNode node, if it exists
    if (childNode != nullptr) {
        childNode->print(childIndent, "└── ");
    }
}
void ColumnNode::accept(std::shared_ptr<AstVisitor> visitor) { visitor->visit(std::static_pointer_cast<ColumnNode>(shared_from_this())); };