#include <ProcDecNode.hpp>
#include <memory>

void ProcDecNode::addChild(std::shared_ptr<AstNode> node) {
    if (nameNode->getChildNode() == nullptr) {
        nameNode->addChild(node);
    } else if (visitingParams) {
        paramNodeList->addChild(node);
    } else {
        bodyNodeList->addChild(node);
    }
}

std::string ProcDecNode::print(std::string indent = "", std::string prefix = "") {
    std::string childIndent = AstNode::print(indent, prefix);
    nameNode->print(childIndent, "├── Name: ");
    paramNodeList->print(childIndent, "├── Params: ");
    bodyNodeList->print(childIndent, "└── ");
}

void ProcDecNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<ProcDecNode>(shared_from_this()));
};