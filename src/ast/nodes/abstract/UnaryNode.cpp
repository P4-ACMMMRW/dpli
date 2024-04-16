#include <UnaryNode.hpp>

void UnaryNode::addChild(std::shared_ptr<AstNode> child) {
    if (childNode->getChildNode() != nullptr) {
        childNode->addChild(child);
    } else {
        throw std::runtime_error("UnaryNode already has two children");
    }
}

std::string UnaryNode::print(std::string indent = "", std::string prefix = "") {
    std::string childIndent = AstNode::print(indent, prefix);

    childNode->print(childIndent, "└── ");
}