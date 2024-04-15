#include <ChildNodeList.hpp>

void ChildNodeList::addChild(std::shared_ptr<AstNode> node) {
    childNodeList.push_back(std::move(node));
}

void ChildNodeList::print(std::string indent, std::string prefix) {
    for (size_t i = 0; i < childNodeList.size(); ++i) {
        std::string bodyPrefix = (i == childNodeList.size() - 1 && (prefix == "├── ")) ? "└── " : "├── ";
        childNodeList[i]->print(indent, bodyPrefix);
    }
}