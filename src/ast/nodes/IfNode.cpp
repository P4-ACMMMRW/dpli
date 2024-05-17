#include <ElseNode.hpp>
#include <IfNode.hpp>

void IfNode::addChild(std::shared_ptr<AstNode> node) {
    if (condNode->getChildNode() == nullptr) {
        condNode->addChild(node);
    } else if (dynamic_cast<ElseNode*>(node.get())) {  // continue and else same rule index
        elseNode->addChild(node);
    } else {
        bodyNodeList->addChild(node);
    }
}

std::string IfNode::print(std::string indent = "", std::string prefix = "") {
    std::string childIndent = AstNode::print(indent, prefix);

    condNode->print(childIndent, "├── Condition: ");

    bool elseNodeExists = elseNode->getChildNode() != nullptr;

    std::string bodyPrefix = (!elseNodeExists) ? "└── " : "├── Body:";
    bodyNodeList->print(childIndent, bodyPrefix);

    elseNode->print(childIndent, "└── ");

    return "";
}

void IfNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<IfNode>(shared_from_this()));
};