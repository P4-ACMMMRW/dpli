#ifndef PROCDECNODE_HPP
#define PROCDECNODE_HPP

using namespace antlr4;
using namespace dplgrammar;

class ProcDecNode : public AstNode {
    public: 
        ProcDecNode(AstNode *parent) : AstNode(parent) {};
        std::string getName() { return name; };
        void setName(std::string name) { this->name = name; };
        std::vector<AstNode*> getParamNodes() { return paramNodes; };
        std::vector<AstNode*> getBodyNodes() { return bodyNodes; };
        void stopVisitingParams() {visitingParams = false; } 

        void addChild(AstNode* node) override {
            if (visitingParams) {
                paramNodes.push_back(node);
            } else {
                bodyNodes.push_back(node);
            }
        }

        void print(std::string indent = "", std::string prefix = "") override {
            std::cout << indent << prefix << "def " << getName() << "():" << "\n";

            std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

            for (size_t i = 0; i < paramNodes.size(); ++i) {
                paramNodes[i]->print(childIndent, "├── param: ");
            }

            for (size_t i = 0; i < bodyNodes.size(); ++i) {
                // For the last statement node, we want to print a different prefix
                if (i == bodyNodes.size() - 1) {
                    bodyNodes[i]->print(childIndent, "└── ");
                } else {
                    bodyNodes[i]->print(childIndent, "├── ");
                }
            }
        }

    private:
        bool visitingParams = true;
        std::string name;
        std::vector<AstNode*> paramNodes;
        std::vector<AstNode*> bodyNodes;

        
};

#endif