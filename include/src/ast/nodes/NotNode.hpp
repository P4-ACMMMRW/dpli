#ifndef NOTNODE_HPP
#define NOTNODE_HPP

#include "UnaryNode.hpp"

class NotNode : public UnaryNode {
   public:
    NotNode(std::shared_ptr<AstNode> parent) : UnaryNode(std::move(parent)){};

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<NotNode>(shared_from_this()));
    };
};

#endif