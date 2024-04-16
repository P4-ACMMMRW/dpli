#include <ProgNode.hpp>

void ProgNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<ProgNode>(shared_from_this()));
};