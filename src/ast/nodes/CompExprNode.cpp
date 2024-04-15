#include <CompExprNode.hpp>

void CompExprNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<CompExprNode>(shared_from_this()));
};