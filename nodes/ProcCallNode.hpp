#ifndef PROCCALLNODE_HPP
#define PROCCALLNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <string>
#include <vector>

class ProcCallNode : public AstNode {
   public:
    ProcCallNode(AstNode* parent) : AstNode(parent) {}

    AstNode* getProcNode() { return proc; };
    std::vector<AstNode*> getArgNodes() { return argNodes; };
    void stopVisitingParams() { visitingParams = false; }

    void addChild(AstNode* node) override;

    void print(std::string indent, std::string prefix) override;

   private:
    AstNode* proc = nullptr;
    std::vector<AstNode*> argNodes;
    bool visitingParams = true;
};

#endif