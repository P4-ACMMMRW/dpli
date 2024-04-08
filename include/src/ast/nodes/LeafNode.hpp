#ifndef LEAFNODE_HPP
#define LEAFNODE_HPP

using namespace antlr4;
using namespace dplgrammar;

class LeafNode : public AstNode {
public:
    LeafNode(AstNode* parent) {AstNode::setParent(parent);}
    void print(std::string indent = "", std::string prefix = "") override {
        std::cout << indent << prefix << AstNode::getText() << "\n";
    }
    void addChild([[maybe_unused]] AstNode* child) override {
        throw std::runtime_error("LeafNode cannot have children");
    }
};

#endif