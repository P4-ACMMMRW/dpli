#ifndef LEAFNODE_HPP
#define LEAFNODE_HPP

#include <vector>
#include <AstNode.hpp>
#include <Symbol.hpp>
#include <SymbolType.hpp>
#include <memory>


using namespace dplsrc;

class LeafNode : public AstNode {
   public:
    LeafNode(std::shared_ptr<AstNode> parent) { AstNode::setParent(std::move(parent)); }

    void setEvaluatedType(const dplsrc::SymbolType leafType) { this->leafType = leafType; }

    const dplsrc::SymbolType &getEvaluatedType() const { 
        if (!leafType.is(SymbolSuperType::TYPE_INVALID))
            return leafType; 
        if (children.size() != 1)
            throw std::runtime_error("Cannot deduce evaluted type of symbol");
        return std::static_pointer_cast<LeafNode>(children.front())->getEvaluatedType();
    }

    void addChild([[maybe_unused]] std::shared_ptr<AstNode> child) override;

    std::string print(std::string indent, std::string prefix) override;

    void accept(std::shared_ptr<AstVisitor> visitor) override;

    
    AstNode *parent;
    std::vector<AstNode *> children;
   private: 
    dplsrc::SymbolType leafType = SymbolSuperType::TYPE_INVALID;
    
};

#endif