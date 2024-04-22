#include <AstNode.hpp>

std::string AstNode::print(std::string indent, std::string prefix) {
    std::cout << indent << prefix << AstNode::getText() << "\n";

    return (indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   ")));
}