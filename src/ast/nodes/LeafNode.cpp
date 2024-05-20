#include "LeafNode.hpp"

using namespace dplsrc;

std::string LeafNode::print(std::string indent = "", std::string prefix = "") {
    std::cout << indent << prefix << AstNode::getText() << "\n";
    return "";
}

void LeafNode::addChild([[maybe_unused]] std::shared_ptr<AstNode> child) {
    throw AstException("LeafNode cannot have children");
}

void LeafNode::accept([[maybe_unused]] std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<LeafNode>(shared_from_this()));
};