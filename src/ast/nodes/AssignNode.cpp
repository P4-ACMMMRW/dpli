#include <AssignNode.hpp>

void AssignNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<AssignNode>(shared_from_this()));
};