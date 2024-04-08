#ifndef UNARYEXPRNODE_HPP
#define UNARYEXPRNODE_HPP

using namespace antlr4;
using namespace dplgrammar;

class UnaryExprNode : public AstNode {
public:

    UnaryExprNode(AstNode* parent) : AstNode(parent) { }

    AstNode* getchild() { return child; };
    void     addChild(AstNode* child) { this->child = child; }

    void print(std::string indent = "", std::string prefix = "") {
        std::cout << indent << prefix << AstNode::getText() << "\n";

        // Use a new level of indentation for the children
        std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "    "));

        // Print the child node, if it exists
        if (child != nullptr) {
            child->print(childIndent, "└── ");
        }
    }
private:
    AstNode* child = nullptr;
};

#endif