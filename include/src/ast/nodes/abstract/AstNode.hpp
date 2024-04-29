#ifndef ASTNODE_HPP
#define ASTNODE_HPP

#include <AstVisitor.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "Type.hpp"
#include "Value.hpp"

class AstNode : public std::enable_shared_from_this<AstNode> {
   public:
    AstNode() = default;
    AstNode(std::shared_ptr<AstNode> parent) : parent(std::move(parent)) {}

    // Rule of five
    virtual ~AstNode() = default;
    AstNode(const AstNode& other) = default;
    AstNode& operator=(AstNode&& other) = default;
    AstNode(AstNode&& other) = default;
    AstNode& operator=(const AstNode& other) = default;

    size_t getRule() const { return rule; }
    std::string getText() { return text; }
    std::shared_ptr<AstNode> getParent() { return parent; }
    void setRule(size_t rule) { this->rule = rule; }
    void setText(std::string text) { this->text = std::move(text); }
    void setParent(std::shared_ptr<AstNode> parent) { this->parent = std::move(parent); }

    void setType(dplsrc::Type type) { this->type = type; }
    dplsrc::Type getType() const { return type; }

    void setVal(dplsrc::Value val) { this->val = std::move(val); }
    dplsrc::Value getVal() { return val; }

    virtual std::string print(std::string indent = "", std::string prefix = "");
    virtual void addChild(std::shared_ptr<AstNode> child) = 0;
    virtual void accept(std::shared_ptr<AstVisitor> visitor) = 0;

   private:
    size_t rule{};
    std::shared_ptr<AstNode> parent;
    std::string text;
    dplsrc::Type type = dplsrc::Type::NONETYPE;
    dplsrc::Value val;
};

#endif