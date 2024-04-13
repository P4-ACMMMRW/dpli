#ifndef ASTNODE_HPP
#define ASTNODE_HPP

#include <memory>
#include <string>
#include <utility>

class AstNode {
   public:
    AstNode(std::shared_ptr<AstNode> parent) : parent(std::move(parent)) {}
    AstNode() {}
    virtual ~AstNode() {}
    size_t getRule() const { return rule; }
    std::string getText() { return text; }
    std::shared_ptr<AstNode> getParent() { return parent; }
    void setRule(size_t rule) { this->rule = rule; }
    void setText(std::string text) { this->text = std::move(text); }
    void setParent(std::shared_ptr<AstNode> parent) { this->parent = std::move(parent); }

    virtual void print(std::string indent = "", std::string prefix = "") = 0;
    virtual void addChild(std::shared_ptr<AstNode> child) = 0;

   private:
    size_t rule{};
    std::shared_ptr<AstNode> parent{};
    std::string text;
};

#endif