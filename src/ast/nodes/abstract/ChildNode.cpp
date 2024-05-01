#include <ChildNode.hpp>

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

void ChildNode::accept(std::shared_ptr<AstVisitor> visitor) {
    throw std::runtime_error("Can't accept composite node");
}