#ifndef PROCDECNODE_HPP
#define PROCDECNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class ProcDecNode : public AstNode {
   public:
    ProcDecNode(AstNode* parent) : AstNode(parent){};
    void setName(std::string name) { this->name = std::move(name); };

    std::string getName() { return name; };
    std::vector<AstNode*> getParamNodes() { return paramNodes; };
    std::vector<AstNode*> getBodyNodes() { return bodyNodes; };

    void stopVisitingParams() { visitingParams = false; }

    void addChild(AstNode* node) override;

    void print(std::string indent, std::string prefix) override;

   private:
    bool visitingParams = true;
    std::string name;
    std::vector<AstNode*> paramNodes;
    std::vector<AstNode*> bodyNodes;
};

#endif