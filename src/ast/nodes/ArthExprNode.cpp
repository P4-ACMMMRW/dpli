#include <ArthExprNode.hpp>

void ArthExprNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<ArthExprNode>(shared_from_this()));
};