#ifndef PROCDECNODE_HPP
#define PROCDECNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class ProcDecNode : public AstNode {
   public:
    ProcDecNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)){};
    void setName(std::string name) { this->name = std::move(name); };

    std::string getName() { return name; };
    std::vector<std::shared_ptr<AstNode>>& getParamNodes() { return paramNodes; };
    std::vector<std::shared_ptr<AstNode>>& getBodyNodes() { return bodyNodes; };

    void stopVisitingParams() { visitingParams = false; }

    void addChild(std::shared_ptr<AstNode> node) override;

    void print(std::string indent, std::string prefix) override;

    void accept(AstVisitor* visitor) override;

   private:
    bool visitingParams = true;
    std::string name;
    std::vector<std::shared_ptr<AstNode>> paramNodes;
    std::vector<std::shared_ptr<AstNode>> bodyNodes;
};

#endif