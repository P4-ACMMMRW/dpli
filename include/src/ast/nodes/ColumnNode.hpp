#ifndef COLUMNNODE_HPP
#define COLUMNNODE_HPP

#include <UnaryNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class ColumnNode : public UnaryNode {
   public:
    ColumnNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)){};

    void accept(std::shared_ptr<AstVisitor> visitor) override;

};

#endif