#include <ListNode.hpp>

void ListNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<ListNode>(shared_from_this()));
};