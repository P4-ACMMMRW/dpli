#ifndef ANDEXPRNODE_HPP
#define ANDEXPRNODE_HPP

#include <BinaryNode.hpp>

class AndExprNode : public BinaryNode {
   public:
    AndExprNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<AndExprNode>(shared_from_this()));
    };
};

#endif