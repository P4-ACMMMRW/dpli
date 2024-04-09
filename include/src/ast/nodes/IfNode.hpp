#ifndef IFNODE_HPP
#define IFNODE_HPP

using namespace antlr4;
using namespace dplgrammar;

class IfNode : public AstNode {
public:
    IfNode(AstNode *parent) : AstNode(parent) {};
    AstNode*              getCondNode()  { return condNode; };
    std::vector<AstNode*> getBodyNodes() { return bodyNodes; };

    void addChild(AstNode* node) override {
        if (condNode == nullptr) {
            condNode = node;
        } else if (node->getRule() == dplgrammar::DplParser::RuleElsestm) {
            elseNode = node;
        }
        else {
            bodyNodes.push_back(node);
        }
    }

    void print(std::string indent = "", std::string prefix = "") override {
        std::cout << indent << prefix << AstNode::getText() << "\n";

        // Use a new level of indentation for the children
        std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

        // Print the condition node, if it exists
        if (condNode != nullptr) {
            condNode->print(childIndent, "├── Condition: ");
        }


        // Print each if statement node
        for (size_t i = 0; i < bodyNodes.size(); ++i) {
            // For the last if statement node, we want to print a different prefix
            std::string bodyPrefix = (i == bodyNodes.size() - 1 && elseNode == nullptr) ? "└── " : "├── ";
            bodyNodes[i]->print(childIndent, bodyPrefix);
        }

        // Print the else node, if it exists
        if (elseNode != nullptr) {
            elseNode->print(childIndent, "└── ");
        }
    }
private:
    AstNode* condNode = nullptr;
    std::vector<AstNode*> bodyNodes;
    AstNode* elseNode = nullptr;
};

#endif