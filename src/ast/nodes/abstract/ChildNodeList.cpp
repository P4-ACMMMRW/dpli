#include <ChildNodeList.hpp>

void ChildNodeList::addChild(std::shared_ptr<AstNode> node) {
    childNodeList.push_back(std::move(node));
}

std::string ChildNodeList::print(std::string indent, std::string prefix) {
    for (size_t i = 0; i < childNodeList.size(); ++i) {
        std::string bodyPrefix = (i == childNodeList.size() - 1 && (prefix == "├── ")) ? "└── " : "├── ";
        childNodeList[i]->print(indent, bodyPrefix);
    }
}


void ChildNodeList::accept(std::shared_ptr<AstVisitor> visitor) {
    throw std::runtime_error("Can't accept composite node");
}