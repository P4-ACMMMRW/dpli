#ifndef ELSENODE_HPP
#define ELSENODE_HPP

using namespace antlr4;
using namespace dplgrammar;

class ElseNode : public AstNode {
public:
    ElseNode(AstNode *parent) : AstNode(parent) {};
    std::vector<AstNode*> getBodyNodes() { return bodyNodes; };

    void addChild(AstNode* node) override {
        bodyNodes.push_back(node);
    }

    void print(std::string indent = "", std::string prefix = "") override {
        std::cout << indent << prefix << AstNode::getText() << "\n";

        // Use a new level of indentation for the children
        std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

        // Print each if statement node
        for (size_t i = 0; i < bodyNodes.size(); ++i) {
            // For the last if statement node, we want to print a different prefix
            if (i == bodyNodes.size() - 1) {
                bodyNodes[i]->print(childIndent, "└── ");
            } else {
                bodyNodes[i]->print(childIndent, "├── ");
            }
        }
    }
private:
    std::vector<AstNode*> bodyNodes;
};

#endif