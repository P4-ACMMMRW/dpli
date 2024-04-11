#ifndef PROCCALLNODE_HPP
#define PROCCALLNODE_HPP

using namespace antlr4;
using namespace dplgrammar;

class ProcCallNode : public AstNode {
public:
    ProcCallNode(AstNode *parent) : AstNode(parent) {setText("()");}

    AstNode*              getProcNode() { return proc; };
    std::vector<AstNode*> getArgNodes() { return argNodes; };
    void                  stopVisitingParams() {visitingParams = false; } 

    void addChild(AstNode* node) override { 
        if (visitingParams) argNodes.push_back(node); 
        else if (proc == nullptr) proc = node;
        else throw std::runtime_error("ProcCallNode can add more children after stopped visitingParams and procdure has been added");   
    }

    void print(std::string indent = "", std::string prefix = "") override {
        std::cout << indent << prefix << AstNode::getText() << " proccall" << "\n";

        // Use a new level of indentation for the children
        std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

        if (proc != nullptr) {
            proc->print(childIndent, (argNodes.size() == 0) ? "└── " : "├── Name: ");
        }


        // Print each if statement node
        for (size_t i = 0; i < argNodes.size(); ++i) {
            // For the last if statement node, we want to print a different prefix
            if (i == argNodes.size() - 1 ) {
                argNodes[i]->print(childIndent, "└── ");
            } else {
                argNodes[i]->print(childIndent, "├── ");
            }
        }
    }
private:
    AstNode* proc = nullptr;
    std::vector<AstNode*> argNodes;
    bool visitingParams = true;
};

#endif