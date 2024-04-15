#include <IndexNode.hpp>

void IndexNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<IndexNode>(shared_from_this()));
};