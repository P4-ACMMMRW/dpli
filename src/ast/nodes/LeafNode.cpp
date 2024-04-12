#include <LeafNode.hpp>

void LeafNode::print(std::string indent = "", std::string prefix = "") {
    std::cout << indent << prefix << AstNode::getText() << "\n";
}

void LeafNode::addChild([[maybe_unused]] AstNode* child) {
    throw std::runtime_error("LeafNode cannot have children");
}
