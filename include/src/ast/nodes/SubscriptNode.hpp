#ifndef SUBSCRIPTNODE_HPP
#define SUBSCRIPTNODE_HPP

#include <AstNode.hpp> 

using namespace antlr4;
using namespace dplgrammar;

class SubscriptNode : public AstNode {
public:
    SubscriptNode(AstNode* parent) : left(nullptr), right(nullptr) {AstNode::setParent(parent);}
    AstNode* getLeft() { return  left;  };
    AstNode* getRight() { return right; };

    void addChild(AstNode* node) override {
        if (left == nullptr) {
            left = node;
        } else if (right == nullptr) {
            right = node;
        } else {
            throw std::runtime_error("SubscriptNode can only have two children");
        }
    }

    void print(std::string indent = "", std::string prefix = "") override {
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