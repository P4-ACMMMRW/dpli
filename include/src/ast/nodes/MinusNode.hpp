#ifndef MINUSNODE_HPP
#define MINUSNODE_HPP

#include <UnaryNode.hpp>

class MinusNode : public UnaryNode {
   public:
    MinusNode(std::shared_ptr<AstNode> parent) : UnaryNode(std::move(parent)){};

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<MinusNode>(shared_from_this()));
    };
};

#endif