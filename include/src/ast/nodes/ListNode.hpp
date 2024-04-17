#ifndef LISTNODE_HPP
#define LISTNODE_HPP

#include <UnaryNodeList.hpp>

class ListNode : public UnaryNodeList {
   public:
    ListNode(std::shared_ptr<AstNode> parent) : UnaryNodeList(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override;
};

#endif