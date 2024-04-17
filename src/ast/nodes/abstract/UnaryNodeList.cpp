#include <UnaryNodeList.hpp>

void UnaryNodeList::addChild(std::shared_ptr<AstNode> node) { childNodeList->addChild(node); }

std::string UnaryNodeList::print(std::string indent = "", std::string prefix = "") {
    std::string childIndent = AstNode::print(indent, prefix);
    childNodeList->print(childIndent, "└── ");
    return "";
}
