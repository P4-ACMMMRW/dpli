#ifndef PARNODE_HPP
#define PARNODE_HPP

using namespace antlr4;
using namespace dplgrammar;

class ParNode : public AstNode {
public:
    ParNode(AstNode *parent) : AstNode(parent) {}
    AstNode* getChildNode() { return childNode; };
    void addChild(AstNode* node) override {
        if (childNode == nullptr) {
            childNode = node;
        } else {
            throw std::runtime_error("ParNode can only have one child");
        }
    }

    void print(std::string indent = "", std::string prefix = "") override {
        std::cout << indent << prefix << AstNode::getText() << "\n";

        // Use a new level of indentation for the children
        std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

        // Print the condition node, if it exists
        if (childNode != nullptr) {
            childNode->print(childIndent, "└── ");
        }
    }
private:
    AstNode* childNode = nullptr;
};

#endif