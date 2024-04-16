#ifndef COLUMNNODE_HPP
#define COLUMNNODE_HPP

#include <UnaryNode.hpp>

class ColumnNode : public UnaryNode {
   public:
    ColumnNode(std::shared_ptr<AstNode> parent) : UnaryNode(std::move(parent)) {};

    void accept(std::shared_ptr<AstVisitor> visitor) override;

};

#endif