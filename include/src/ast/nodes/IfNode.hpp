#ifndef IFNODE_HPP
#define IFNODE_HPP

using namespace antlr4;
using namespace dplgrammar;

class IfNode : public AstNode {
public:
    AstNode*              getCondNode()     { return condNode; };
    std::vector<AstNode*> getIfStmNodes()   { return ifStmNodes; };
    std::vector<AstNode*> getElseStmNodes() { return elseStmNodes; };

    void print(std::string indent = "", std::string prefix = "") {
        std::cout << indent << prefix << AstNode::getText() << "\n";

        // Use a new level of indentation for the children
        std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

        // Print the condition node, if it exists
        if (condNode != nullptr) {
            condNode->print(childIndent, "├── Condition: ");
        }

        // Print each if statement node
        for (size_t i = 0; i < ifStmNodes.size(); ++i) {
            // For the last if statement node, we want to print a different prefix
            if (i == ifStmNodes.size() - 1 && elseStmNodes.empty()) {
                ifStmNodes[i]->print(childIndent, "└── If: ");
            } else {
                ifStmNodes[i]->print(childIndent, "├── If: ");
            }
        }

        // Print each else statement node
        for (size_t i = 0; i < elseStmNodes.size(); ++i) {
            // For the last else statement node, we want to print a different prefix
            if (i == elseStmNodes.size() - 1) {
                elseStmNodes[i]->print(childIndent, "└── Else: ");
            } else {
                elseStmNodes[i]->print(childIndent, "├── Else: ");
            }
        }
    }
private:
    AstNode* condNode = nullptr;
    std::vector<AstNode*> ifStmNodes;
    std::vector<AstNode*> elseStmNodes;
};

#endif