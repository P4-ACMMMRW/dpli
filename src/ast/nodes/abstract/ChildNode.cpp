#include "ChildNode.hpp"

using namespace dplsrc;

void ChildNode::addChild(std::shared_ptr<AstNode> node) {
    if (childNode == nullptr) {
        childNode = std::move(node);
    }
}

std::string ChildNode::print(std::string indent, std::string prefix) {
    if (childNode != nullptr) {
        childNode->print(indent, prefix);
    }
    return "";
}

void ChildNode::accept([[maybe_unused]] std::shared_ptr<AstVisitor> visitor) {
    throw AstException("Can't accept composite node");
}