#ifndef ARTHEXPRNODE_HPP
#define ARTHEXPRNODE_HPP

#include <AstNode.hpp> 

using namespace antlr4;
using namespace dplgrammar;

class ArthExprNode : public AstNode {
public:
    AstNode* getLeft() { return  left;  };
    AstNode* getRight() { return right; };

    void print(std::string indent = "", std::string prefix = "") {
        std::cout << indent << prefix << AstNode::getText() << "\n";

        // Use a new level of indentation for the children
        std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

        // Print the left child, if it exists
        if (left != nullptr) {
            left->print(childIndent, "├── ");
        }

        // Print the right child, if it exists
        if (right != nullptr) {
            right->print(childIndent, "└── ");
        }
    }
private:
    AstNode* left = nullptr;
    AstNode* right = nullptr;
};

#endif