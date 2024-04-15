#include <NotNode.hpp>

void NotNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<NotNode>(shared_from_this()));
};