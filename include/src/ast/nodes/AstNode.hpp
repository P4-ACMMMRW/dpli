#ifndef ASTNODE_HPP
#define ASTNODE_HPP

#include <string>
#include <utility>

class AstNode {
   public:
    AstNode(AstNode* parent) : parent(parent) {}
    AstNode() {}
    virtual ~AstNode() {}
    size_t getRule() const { return rule; }
    std::string getText() { return text; }
    AstNode* getParent() { return parent; }
    void setRule(size_t rule) { this->rule = rule; }
    void setText(std::string text) { this->text = std::move(text); }
    void setParent(AstNode* parent) { this->parent = parent; }

    virtual void print(std::string indent = "", std::string prefix = "") = 0;
    virtual void addChild(AstNode* child) = 0;

   private:
    size_t rule{};
    AstNode* parent{};
    std::string text;
};

#endif