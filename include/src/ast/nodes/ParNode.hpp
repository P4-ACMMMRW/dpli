#ifndef PARNODE_HPP
#define PARNODE_HPP

#include <UnaryNode.hpp>

class ParNode : public UnaryNode {
   public:
    ParNode(std::shared_ptr<AstNode> parent) : UnaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<ParNode>(shared_from_this()));
    };
};

#endif