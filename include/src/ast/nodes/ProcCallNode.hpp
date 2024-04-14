#ifndef PROCCALLNODE_HPP
#define PROCCALLNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class ProcCallNode : public AstNode {
   public:
    ProcCallNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)) {}

    std::shared_ptr<AstNode> getProcNode() { return proc; };
    std::vector<std::shared_ptr<AstNode>> getArgNodes() { return argNodes; };
    void stopVisitingParams() { visitingParams = false; }

    void addChild(std::shared_ptr<AstNode> node) override;

    void print(std::string indent, std::string prefix) override;

    void accept(AstVisitor* visitor) override;

   private:
    std::shared_ptr<AstNode> proc = nullptr;
    std::vector<std::shared_ptr<AstNode>> argNodes;
    bool visitingParams = true;
};

#endif