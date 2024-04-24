#include "Evaluator.hpp"

using namespace dplsrc;

void Evaluator::visit(std::shared_ptr<AndExprNode> node) {}

void Evaluator::visit(std::shared_ptr<AssignNode> node) {
    // Assume left node is a leaf node
    std::shared_ptr<LeafNode> leftNode = std::dynamic_pointer_cast<LeafNode>(node->getLeftNode());

    if (!leftNode->getIsIdentifier()) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Error: left side of assignment must be an identifier\n");
    }

    // Compute type of right node
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    vtable.bind(Symbol(leftNode->getText(), rightNode->getVal(), rightNode->getType()));
}

void Evaluator::visit(std::shared_ptr<ColumnNode> node) {}

void Evaluator::visit(std::shared_ptr<DivExprNode> node) {}

void Evaluator::visit(std::shared_ptr<ElseNode> node) {}

void Evaluator::visit(std::shared_ptr<EqualExprNode> node) {}

void Evaluator::visit(std::shared_ptr<ExpoExprNode> node) {}

void Evaluator::visit(std::shared_ptr<FilterNode> node) {}

void Evaluator::visit(std::shared_ptr<GreaterEqualExprNode> node) {}

void Evaluator::visit(std::shared_ptr<GreaterExprNode> node) {}

void Evaluator::visit(std::shared_ptr<HeaderIndexNode> node) {}

void Evaluator::visit(std::shared_ptr<IfNode> node) {}

void Evaluator::visit(std::shared_ptr<IndexNode> node) {}

void Evaluator::visit(std::shared_ptr<LeafNode> node) {
    if (node->getIsIdentifier()) {
        // TODO: there should probably be two table classes, one for variables and one for procedures. also two different entry types
        if (node->getIsFunctionCall()) {
            try {
                Symbol *sym = ptable.lookup(node->getText());
                node->setType(sym->getType());
                node->setVal(sym->getVal());
            } catch (const std::out_of_range &e) {
                throw std::runtime_error("Error: undefined procedure \"" + node->getText() + "\"\n");
            }
        } else {
            try {
                Symbol *sym = vtable.lookup(node->getText());
                node->setType(sym->getType());
                node->setVal(sym->getVal());
            } catch (const std::out_of_range &e) {
                // TODO: call undefined variable error from error handler
                throw std::runtime_error("Error: undefined variable \"" + node->getText() + "\"\n");
            }
        }
    } else {
        node->setVal(node->getText());
    }
}

void Evaluator::visit(std::shared_ptr<LessEqualExprNode> node) {}

void Evaluator::visit(std::shared_ptr<LessExprNode> node) {}

void Evaluator::visit(std::shared_ptr<ListNode> node) {}

void Evaluator::visit(std::shared_ptr<MinusExprNode> node) {}

void Evaluator::visit(std::shared_ptr<MinusNode> node) {}

void Evaluator::visit(std::shared_ptr<ModExprNode> node) {}

void Evaluator::visit(std::shared_ptr<MultExprNode> node) {}

void Evaluator::visit(std::shared_ptr<NotEqualExprNode> node) {}

void Evaluator::visit(std::shared_ptr<NotNode> node) {}

void Evaluator::visit(std::shared_ptr<OrExprNode> node) {}

void Evaluator::visit(std::shared_ptr<ParNode> node) {}

void Evaluator::visit(std::shared_ptr<PlusExprNode> node) {}

void Evaluator::visit(std::shared_ptr<PlusNode> node) {}

void Evaluator::visit(std::shared_ptr<ProcCallNode> node) {
    std::shared_ptr<LeafNode> procNode = std::dynamic_pointer_cast<LeafNode>(node->getChildNode());
    procNode->setIsFunctionCall(true);
    procNode->accept(shared_from_this());

    std::vector<std::shared_ptr<AstNode>> argNodes = node->getChildNodeList();
    for (size_t i = 0; i < argNodes.size(); ++i) {
        argNodes[i]->accept(shared_from_this());
    }
}

void Evaluator::visit(std::shared_ptr<ProcDecNode> node) {}

void Evaluator::visit(std::shared_ptr<ProgNode> node) {
    AstVisitor::visit(std::static_pointer_cast<UnaryNodeList>(node));
}

void Evaluator::visit(std::shared_ptr<ReturnNode> node) {}

void Evaluator::visit(std::shared_ptr<TableNode> node) {}

void Evaluator::visit(std::shared_ptr<UnaryExprNode> node) {}

void Evaluator::visit(std::shared_ptr<WhileNode> node) {}
