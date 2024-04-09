#ifndef TABLENODE_HPP
#define TABLENODE_HPP

using namespace antlr4;
using namespace dplgrammar;

class TableNode : public AstNode {
public:
    TableNode(AstNode *parent) : AstNode(parent) {}
    std::vector<AstNode*> getColumnNodes() { return columnNodes; };

    void addChild(AstNode* node) override {
        columnNodes.push_back(node);
    }

    void print(std::string indent = "", std::string prefix = "") override {
        std::cout << indent << prefix << AstNode::getText() << "\n";

        // Use a new level of indentation for the children
        std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

        // Print each column node
        for (size_t i = 0; i < columnNodes.size(); ++i) {
            // For the last column node, we want to print a different prefix
            if (i == columnNodes.size() - 1) {
                columnNodes[i]->print(childIndent, "└── ");
            } else {
                columnNodes[i]->print(childIndent, "├── ");
            }
        }
    }
private:
    std::vector<AstNode*> columnNodes;
};

#endif