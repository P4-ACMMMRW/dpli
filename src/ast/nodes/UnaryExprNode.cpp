#include <UnaryExprNode.hpp>

void UnaryExprNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<UnaryExprNode>(shared_from_this()));
};