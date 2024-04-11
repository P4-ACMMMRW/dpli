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
            std::cout << indent << prefix << "Procedure: " << name << "\n";

            // Use a new level of indentation for the children
            std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

            // Print each parameter node
            for (size_t i = 0; i < paramNodes.size(); ++i) {
                std::string paramPrefix = (i == paramNodes.size() - 1 && bodyNodes.empty()) ? "└── " : "├── ";
                paramNodes[i]->print(childIndent, paramPrefix + "Param: ");
            }

            // Print each body node
            for (size_t i = 0; i < bodyNodes.size(); ++i) {
                std::string bodyPrefix = (i == bodyNodes.size() - 1) ? "└── " : "├── ";
                bodyNodes[i]->print(childIndent, bodyPrefix + "Body: ");
            }
        }

    private:
        bool visitingParams = true;
        std::string name;
        std::vector<AstNode*> paramNodes;
        std::vector<AstNode*> bodyNodes;
};

#endif