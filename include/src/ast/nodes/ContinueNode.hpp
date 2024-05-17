#ifndef CONTINUENODE_HPP
#define CONTINUENODE_HPP

#include "LeafNode.hpp"

class ContinueNode : public LeafNode {
   public:
    ContinueNode(std::shared_ptr<AstNode> parent) : LeafNode(std::move(parent)) {
        LeafNode::setIsIdentifier(false);
        AstNode::setVal("Continue");
    };

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<ContinueNode>(shared_from_this()));
    };
};

#endif