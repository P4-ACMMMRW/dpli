#ifndef TABLENODE_HPP
#define TABLENODE_HPP

#include "UnaryNodeList.hpp"

class TableNode : public UnaryNodeList {
   public:
    TableNode(std::shared_ptr<AstNode> parent) : UnaryNodeList(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<TableNode>(shared_from_this()));
    };
};

#endif