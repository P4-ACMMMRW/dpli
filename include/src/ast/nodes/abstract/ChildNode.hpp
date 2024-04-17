#ifndef CHILDNODE_HPP
#define CHILDNODE_HPP

#include <AstNode.hpp>
#include <vector>

class ChildNode : public AstNode {
   public:
    ChildNode() : childNode(nullptr){};

    std::shared_ptr<AstNode>& getChildNode() { return childNode; };

    void addChild(std::shared_ptr<AstNode> node) override;

    std::string print(std::string indent, std::string prefix) override;

    void accept(std::shared_ptr<AstVisitor> visitor) override;

   private:
    std::shared_ptr<AstNode> childNode;
};

#endif