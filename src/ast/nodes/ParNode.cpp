#include <ParNode.hpp>
#include <memory>

void ParNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<ParNode>(shared_from_this()));
};