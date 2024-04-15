#ifndef NOTNODE_HPP
#define NOTNODE_HPP

#include <UnaryNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class NotNode : public UnaryNode {
   public:
    NotNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)){};
   
    void accept(std::shared_ptr<AstVisitor> visitor) override;
};

#endif