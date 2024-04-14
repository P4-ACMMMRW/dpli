#include <TableNode.hpp>

void TableNode::addChild(std::shared_ptr<AstNode> node) { columnNodes.push_back(std::move(node)); }

void TableNode::print(std::string indent = "", std::string prefix = "") {
    std::cout << indent << prefix << AstNode::getText() << "\n";

    // Use a new level of indentation for the children
    std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

    // Print each column node
    for (size_t i = 0; i < columnNodes.size(); ++i) {
        // For the last column node, we want to print a different prefix
        if (i == columnNodes.size() - 1) {
            columnNodes[i]->print(childIndent, "└── ");
        } else {
            columnNodes[i]->print(childIndent, "├── ");
        }
    }
}
void TableNode::accept(std::shared_ptr<AstVisitor> visitor) {
    visitor->visit(std::static_pointer_cast<TableNode>(shared_from_this()));
};