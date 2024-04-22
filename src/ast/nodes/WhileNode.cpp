#include <WhileNode.hpp>

void WhileNode::addChild(std::shared_ptr<AstNode> node) {
    if (childNode->getChildNode() == nullptr) {
        childNode->addChild(node);
    } else {
        childNodeList->addChild(node);
    }
}

std::string WhileNode::print(std::string indent = "", std::string prefix = "") {
    std::string childIndent = AstNode::print(indent, prefix);

    childNode->print(childIndent, "├── ");

    childNodeList->print(childIndent, "└── ");
    return "";
}

void WhileNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<WhileNode>(shared_from_this()));
};