#ifndef PLUSNODE_HPP
#define PLUSNODE_HPP

#include <UnaryNode.hpp>

class PlusNode : public UnaryNode {
   public:
    PlusNode(std::shared_ptr<AstNode> parent) : UnaryNode(std::move(parent)){};

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<PlusNode>(shared_from_this()));
    };
};

#endif