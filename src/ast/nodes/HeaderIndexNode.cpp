#include <HeaderIndexNode.hpp>

void HeaderIndexNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<HeaderIndexNode>(shared_from_this()));
};