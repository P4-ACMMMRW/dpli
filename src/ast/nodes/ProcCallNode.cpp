#include <ProcCallNode.hpp>

void ProcCallNode::addChild(std::shared_ptr<AstNode> node) {
    if (visitingParams) {
        childNodeList->addChild(node);
    } else if (childNode->getChildNode() == nullptr) { // problem here 
        std::cout << "hello hihi" << "\n";
        childNode->addChild(node);
    } else {
        throw std::runtime_error(
            "ProcCallNode can add more children after stopped visitingParams and procdure has been "
            "added");
    }
}

std::string ProcCallNode::print(std::string indent = "", std::string prefix = "") {
    std::string childIndent = AstNode::print(indent, prefix);

    bool isChildNodeListEmpty = childNodeList->getChildNodeList().empty();
    childNode->print(childIndent, (isChildNodeListEmpty) ? "└── " : "├── Name: ");
    
    childNodeList->print(childIndent, "└── ");
}

void ProcCallNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<ProcCallNode>(shared_from_this()));
};