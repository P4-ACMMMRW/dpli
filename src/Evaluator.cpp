#include "Evaluator.hpp"

using namespace dplsrc;

void Evaluator::visit(std::shared_ptr<AssignNode> node) {
    // Assume left node is a leaf node
    std::shared_ptr<LeafNode> leftNode = std::dynamic_pointer_cast<LeafNode>(node->getLeftNode());

    if (!leftNode->getIsIdentifier()) {
        throw std::runtime_error("Error: left side of assignment must be an identifier\n");
    }

    std::shared_ptr<AstNode> rightNode = node->getRightNode();

    // TODO: should use something else than getText()
    vtable.bind(Symbol(leftNode->getText(), rightNode->getText(), rightNode->getType()));
    vtable.print();

    leftNode->accept(shared_from_this());
    rightNode->accept(shared_from_this());
}

void Evaluator::visit(std::shared_ptr<LeafNode> node) {
    if (node->getIsIdentifier()) {
        Symbol *sym;
        try {
            sym = vtable.lookup(node->getText());
        } catch (const std::out_of_range &e) {
            // TODO: call undefined variable error from error handler
            throw std::runtime_error("Error: undefined variable \"" + node->getText() + "\"\n");
        }

        node->setType(sym->getType());
    }
}
