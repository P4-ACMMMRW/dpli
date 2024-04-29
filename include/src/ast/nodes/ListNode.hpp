#ifndef LISTNODE_HPP
#define LISTNODE_HPP

#include <UnaryNodeList.hpp>
#include "Type.hpp"

class ListNode : public UnaryNodeList {
   public:
    ListNode(std::shared_ptr<AstNode> parent) : UnaryNodeList(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<ListNode>(shared_from_this()));
    };
};

#endif