#include "Evaluator.hpp"

using namespace dplsrc;

void Evaluator::visit(std::shared_ptr<AssignNode> node) {
    auto leftNode = node->getLeftNode();
    auto rightNode = node->getRightNode();

    //leftNode->accept(shared_from_this());
    //rightNode->accept(shared_from_this());

    std::cout << "Visiting AssignNode" << '\n';
    std::cout << "LValue: " << leftNode->getText() << '\n';
    std::cout << "LType: " << leftNode->getType() << '\n';
    std::cout << "RValue: " << rightNode->getText() << '\n';
    std::cout << "RType: " << rightNode->getType() << '\n';
}

void Evaluator::visit(std::shared_ptr<LeafNode> node) {
    if (node->getIsIdentifier()) {
        Symbol *sym = vtable.lookup(node->getText());
        node->setType(sym->getType());
    }

    std::cout << "Visiting LeafNode" << '\n';
    std::cout << "Value: " << node->getText() << '\n';
    std::cout << "Type: " << node->getType() << '\n';
}
