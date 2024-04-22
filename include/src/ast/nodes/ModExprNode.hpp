#ifndef MODEXPRNODE_HPP
#define MODEXPRNODE_HPP

#include <BinaryNode.hpp>

class ModExprNode : public BinaryNode {
   public:
    ModExprNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<ModExprNode>(shared_from_this()));
    };
};

#endif