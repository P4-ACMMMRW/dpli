#ifndef HEADERINDEXNODE_HPP
#define HEADERINDEXNODE_HPP

#include <IndexNode.hpp>

class HeaderIndexNode : public IndexNode {
   public:
    HeaderIndexNode(std::shared_ptr<AstNode> parent) : IndexNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<HeaderIndexNode>(shared_from_this()));
    };
};

#endif