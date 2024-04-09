#ifndef WHILENODE_HPP
#define WHILENODE_HPP

using namespace antlr4;
using namespace dplgrammar;

class WhileNode : public AstNode {
public:
    WhileNode(AstNode *parent) : AstNode(parent) {};
    AstNode*              getCondNode() { return condNode; };
    std::vector<AstNode*> getStmNodes() { return stmNodes; };

    void addChild(AstNode* node) override {
        if (condNode == nullptr) {
            condNode = node;
        } else {
            stmNodes.push_back(node);
        }
    }

    void print(std::string indent = "", std::string prefix = "") override {
    std::cout << indent << prefix << AstNode::getText() << "\n";

    // Use a new level of indentation for the children
    std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

    // Print the condition node, if it exists
    if (condNode != nullptr) {
        condNode->print(childIndent, "├── ");
    }

    // Print each statement node
    for (size_t i = 0; i < stmNodes.size(); ++i) {
        // For the last statement node, we want to print a different prefix
        if (i == stmNodes.size() - 1) {
            stmNodes[i]->print(childIndent, "└── ");
        } else {
            stmNodes[i]->print(childIndent, "├── ");
        }
    }
}
private:
    AstNode* condNode = nullptr;
    std::vector<AstNode*> stmNodes;
};

#endif