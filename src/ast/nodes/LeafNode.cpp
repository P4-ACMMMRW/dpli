#include <LeafNode.hpp>

std::string LeafNode::print(std::string indent = "", std::string prefix = "") {
    std::cout << indent << prefix << AstNode::getText() << "\n";
    return "";
}

void LeafNode::addChild(std::shared_ptr<AstNode> child) {
    throw std::runtime_error("LeafNode cannot have children");
}

void LeafNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<LeafNode>(shared_from_this()));
};