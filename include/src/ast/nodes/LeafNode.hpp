#ifndef LEAFNODE_HPP
#define LEAFNODE_HPP

#include <AstNode.hpp>

class LeafNode : public AstNode {
   public:
    LeafNode(std::shared_ptr<AstNode> parent) { AstNode::setParent(std::move(parent)); }

    enum type { IDENTIFIER, INTEGER, FLOAT, STRING, BOOLEAN, NONE, UNDEFINED };

    void setType(type leafType) { this->leafType = leafType; }

    type getType() { return leafType; }

    void addChild([[maybe_unused]] std::shared_ptr<AstNode> child) override;

    std::string print(std::string indent, std::string prefix) override;

    void accept(std::shared_ptr<AstVisitor> visitor) override;

   private: 
    type leafType = type::UNDEFINED;
};

#endif