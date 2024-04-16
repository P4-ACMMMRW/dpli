#ifndef RUTURNNODE_HPP
#define RUTURNNODE_HPP

#include <UnaryNode.hpp>

class ReturnNode : public UnaryNode {
   public:
    ReturnNode(std::shared_ptr<AstNode> parent) : UnaryNode(std::move(parent)){};

    void accept(std::shared_ptr<AstVisitor> visitor) override;
};

#endif