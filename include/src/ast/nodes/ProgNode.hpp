#ifndef PROGNODE_HPP
#define PROGNODE_HPP

#include "UnaryNodeList.hpp"

class ProgNode : public UnaryNodeList {
   public:
    ProgNode() : UnaryNodeList(nullptr) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<ProgNode>(shared_from_this()));
    };
};

#endif