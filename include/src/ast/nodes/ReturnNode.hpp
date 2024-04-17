#ifndef RUTURNNODE_HPP
#define RUTURNNODE_HPP

#include <UnaryNode.hpp>

class ReturnNode : public UnaryNode {
   public:
    ReturnNode(std::shared_ptr<AstNode> parent) : UnaryNode(std::move(parent)){};

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<ReturnNode>(shared_from_this()));
    };
};

#endif