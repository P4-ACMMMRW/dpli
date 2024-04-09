#ifndef LISTNODE_HPP
#define LISTNODE_HPP

using namespace antlr4;
using namespace dplgrammar;

class ListNode : public AstNode {
public:
    ListNode(AstNode *parent) : AstNode(parent) {setText("[]");}
    std::vector<AstNode*> getChildren() { return children; };
    
    void addChild(AstNode* node) override {
        children.push_back(node);
    }

    void print(std::string indent = "", std::string prefix = "") override {
        std::cout << indent << prefix << AstNode::getText() << "\n";

        // Use a new level of indentation for the children
        std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

        // Print all children nodes
        for (size_t i = 0; i < children.size(); i++) {
            if (children[i] != nullptr) {
                std::string childPrefix = (i == children.size() - 1) ? "└── " : "├── ";
                children[i]->print(childIndent, childPrefix);
            }
        }
    }
private:
    std::vector<AstNode*> children;
};

#endif