#include <BinaryNode.hpp>

using namespace dplsrc;

void BinaryNode::addChild(std::shared_ptr<AstNode> child) {
    if (rightNode->getChildNode() == nullptr) {
        rightNode->addChild(child);
    } else if (leftNode->getChildNode() == nullptr) {
        leftNode->addChild(child);
    } else {
        throw AstException("BinaryNode already has two children");
    }
}

std::string BinaryNode::print(std::string indent = "", std::string prefix = "") {
    std::string childIndent = AstNode::print(indent, prefix);

    leftNode->print(childIndent, "├── ");
    rightNode->print(childIndent, "└── ");

    return "";
}