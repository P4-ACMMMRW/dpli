#ifndef PROGNODE_HPP
#define PROGNODE_HPP

using namespace antlr4;
using namespace dplgrammar;


class ProgNode : public AstNode {
public:
    std::vector<AstNode*> getChildren()                     { return children; };
    void                  addChild(AstNode* child) override { children.push_back(child); }

    void print(std::string indent = "", std::string prefix = "") override {
        //std::cout << indent << prefix << ruleName << "   (" + text +")" << "\n";
        std::cout << indent << prefix << AstNode::getText() << "\n";

        // Use a new level of indentation for the children
        std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

        for (size_t i = 0; i < children.size(); ++i) {
            // For the last child, we want to print a different prefix
            if (i == children.size() - 1) {
                children[i]->print(childIndent, "└── ");
            } else {
                children[i]->print(childIndent, "├── ");
            }
        }
    }
private:
    std::vector<AstNode*> children;
};

#endif