#include <TableNode.hpp>

void TableNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<TableNode>(shared_from_this()));
};