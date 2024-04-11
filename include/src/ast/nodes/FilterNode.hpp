#ifndef FILTERNODE_HPP
#define FILTERNODE_HPP

using namespace antlr4;
using namespace dplgrammar;

class FilterNode : public AstNode {
public:
    FilterNode(AstNode *parent) : AstNode(parent) { }
    AstNode* getLeftNode()  { return left; };
    AstNode* getRightNode() { return right; };
    void addChild(AstNode* node) override {
        if      (right == nullptr) right = node;
        else if (left == nullptr)  left  = node;
        else throw std::runtime_error("FilterNode can only have two children");
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
    AstNode* left  = nullptr;
    AstNode* right = nullptr;
};

#endif