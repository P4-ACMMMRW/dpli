#ifndef NOTNODE_HPP
#define NOTNODE_HPP

using namespace antlr4;
using namespace dplgrammar;

class NotNode : public AstNode {
public:
    NotNode(AstNode *parent) : AstNode(parent) { };
    AstNode* getchild() { return child; };

    void addChild(AstNode* node) override {
        if (child == nullptr) {
            child = node;
        } else {
            throw std::runtime_error("NotNode can only have one child");
        }
    }

    void print(std::string indent = "", std::string prefix = "") override {
        std::cout << indent << prefix << AstNode::getText() << "\n";

        // Use a new level of indentation for the children
        std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

        // Print the child node, if it exists
        if (child != nullptr) {
            child->print(childIndent, "└── ");
        }
    }
private:
    AstNode* child = nullptr;
};

#endif