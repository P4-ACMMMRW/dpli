#include <DplParserBaseVisitor.h>

#include <IfNode.hpp>

void IfNode::addChild(std::shared_ptr<AstNode> node) {
    if (condNode->getChildNode() == nullptr) {
        condNode->addChild(node);
    } else if (node->getRule() == dplgrammar::DplParser::RuleElsestm) {
        elseNode->addChild(node);
    } else {
        bodyNodeList->addChild(node);
    }
}

std::string IfNode::print(std::string indent = "", std::string prefix = "") {
    std::string childIndent = AstNode::print(indent, prefix);

    condNode->print(childIndent, "├── Condition: ");

    bodyNodeList->print(childIndent, "├── Body: ");

    elseNode->print(childIndent, "└── ");
    return "";
}

void IfNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<IfNode>(shared_from_this()));
};