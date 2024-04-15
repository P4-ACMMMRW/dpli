#include <ChildNode.hpp>

void ChildNode::addChild(std::shared_ptr<AstNode> node) {
    if (childNode == nullptr) {
        childNode = std::move(node); 
    }
}

void ChildNode::print(std::string indent, std::string prefix) {
    if (childNode != nullptr) {
        childNode->print(indent, prefix);
    }
}