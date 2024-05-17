#ifndef ELSENODE_HPP
#define ELSENODE_HPP

#include "AstNode.hpp"
#include "UnaryNodeList.hpp"

class ElseNode : public UnaryNodeList {
   public:
    ElseNode(std::shared_ptr<AstNode> parent) : UnaryNodeList(std::move(parent)){};

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<ElseNode>(shared_from_this()));
    };
};

#endif