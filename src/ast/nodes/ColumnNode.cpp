#include <ColumnNode.hpp>

void ColumnNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<ColumnNode>(shared_from_this()));
};