#include <UnaryNode.hpp>

using namespace dplsrc;

void UnaryNode::addChild(std::shared_ptr<AstNode> child) {
    if (childNode->getChildNode() == nullptr) {
        childNode->addChild(child);
    } else {
        throw AstException("UnaryNode already has two children");
    }
}

std::string UnaryNode::print(std::string indent = "", std::string prefix = "") {
    std::string childIndent = AstNode::print(indent, prefix);
    childNode->print(childIndent, "└── ");
    return "";
}