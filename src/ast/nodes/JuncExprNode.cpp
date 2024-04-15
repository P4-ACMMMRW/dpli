#include <JuncExprNode.hpp>

void JuncExprNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<JuncExprNode>(shared_from_this()));
};