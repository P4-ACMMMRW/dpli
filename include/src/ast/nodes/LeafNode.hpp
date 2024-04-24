#ifndef LEAFNODE_HPP
#define LEAFNODE_HPP

#include <vector>
#include <AstNode.hpp>
#include <memory>

class LeafNode : public AstNode {
   public:
    LeafNode(std::shared_ptr<AstNode> parent) { AstNode::setParent(std::move(parent)); }

    void addChild(std::shared_ptr<AstNode> child) override;

    std::string print(std::string indent, std::string prefix) override;

    void accept(std::shared_ptr<AstVisitor> visitor) override;

    void setIsIdentifier(bool isIdentifier) { this->isIdentifier = isIdentifier; }
    bool getIsIdentifier() { return isIdentifier; }

   private:
    bool isIdentifier;
};

#endif