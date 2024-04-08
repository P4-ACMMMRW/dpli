#ifndef PROCCALLNODE_HPP
#define PROCCALLNODE_HPP

using namespace antlr4;
using namespace dplgrammar;

class ProcCallNode : public AstNode {
public:
    ProcCallNode(AstNode *parent) : AstNode(parent) {setText("()");}

    std::vector<AstNode*> getArgNodes()   { return argNodes; };
    void                  addChild(AstNode* node) override { argNodes.push_back(node); }

    void print(std::string indent = "", std::string prefix = "") override {
        std::cout << indent << prefix << AstNode::getText() << "\n";

        // Use a new level of indentation for the children
        std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

        // Print each if statement node
        for (size_t i = 0; i < argNodes.size(); ++i) {
            // For the last if statement node, we want to print a different prefix
            if (i == argNodes.size() - 1 ) {
                argNodes[i]->print(childIndent, "└── arg: ");
            } else {
                argNodes[i]->print(childIndent, "├── arg: ");
            }
        }
    }
private:
    std::vector<AstNode*> argNodes;
};

#endif