#ifndef BREAKNODE_HPP
#define BREAKNODE_HPP

#include <LeafNode.hpp>

class BreakNode : public LeafNode {
   public:
    BreakNode(std::shared_ptr<AstNode> parent) : LeafNode(std::move(parent)){
        LeafNode::setIsIdentifier(false);
        AstNode::setVal("Break");
    };

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<BreakNode>(shared_from_this()));
    };
};

#endif