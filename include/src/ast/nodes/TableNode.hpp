#ifndef TABLENODE_HPP
#define TABLENODE_HPP

#include <UnaryNodeList.hpp>

class TableNode : public UnaryNodeList {
   public:
    TableNode(std::shared_ptr<AstNode> parent) : UnaryNodeList(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override;
};

#endif