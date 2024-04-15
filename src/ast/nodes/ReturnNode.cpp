#include <ReturnNode.hpp>

void ReturnNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<ReturnNode>(shared_from_this()));
};