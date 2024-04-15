#include <FilterNode.hpp>

void FilterNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<FilterNode>(shared_from_this()));
};