#ifndef LEAFNODE_HPP
#define LEAFNODE_HPP

#include <AstNode.hpp>
#include <memory>
#include <vector>

class LeafNode : public AstNode {
   public:
    LeafNode(std::shared_ptr<AstNode> parent) { AstNode::setParent(std::move(parent)); }

    void addChild(std::shared_ptr<AstNode> child) override;

    std::string print(std::string indent, std::string prefix) override;

    void accept(std::shared_ptr<AstVisitor> visitor) override;

    void setIsIdentifier(bool isIdentifier) { this->isIdentifier = isIdentifier; }
    bool getIsIdentifier() const { return isIdentifier; }

    void setIsFunctionCall(bool isFunctionCall) { this->isFunctionCall = isFunctionCall; }
    bool getIsFunctionCall() const { return isFunctionCall; }

   private:
    bool isIdentifier{};
    bool isFunctionCall{};
};

#endif