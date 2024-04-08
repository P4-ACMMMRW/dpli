#ifndef ASTNODE_HPP
#define ASTNODE_HPP

using namespace antlr4;
using namespace dplgrammar;


class AstNode  { 
public:
    AstNode(AstNode *parent) : parent(parent) {}
    AstNode() {}
    int          getRule()   { return rule; }
    std::string  getText()   { return text; }
    AstNode*     getParent() { return parent; }
    void         setRule(int r) { rule = r; }
    void         setText(std::string t) { text = t; }
    void         setParent(AstNode* p) { parent = p; }
    virtual void print(std::string indent = "", std::string prefix = "") = 0;
    virtual void addChild(AstNode* child) = 0;
private:
    int rule;
    AstNode* parent;
    std::string text;
};

#endif