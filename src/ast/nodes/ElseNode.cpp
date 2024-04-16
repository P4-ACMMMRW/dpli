#include <ElseNode.hpp>

void ElseNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<ElseNode>(shared_from_this()));
};