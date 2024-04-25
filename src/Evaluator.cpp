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

    vtable.bind(Variable(leftNode->getText(), rightNode->getVal(), rightNode->getType()));
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
    if (node->getIsIdentifier() && !node->getIsFunctionCall()) {
        try {
            Variable *var = vtable.lookup(node->getText());
            node->setType(var->getType());
            node->setVal(var->getVal());
        } catch (const std::out_of_range &e) {
            std::string symbol = node->getIsFunctionCall() ? "procedure" : "variable";
            throw std::runtime_error("Error: undefined " + symbol + " \"" + node->getText() +
                                     "\"\n");
        }
    } else if (!node->getIsIdentifier()) {
        node->setVal(node->getText());
    }

    if (node->getType() == Type::NONETYPE) {
        node->setVal("None");
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
    vtable.enterScope();

    std::shared_ptr<LeafNode> procNode = std::dynamic_pointer_cast<LeafNode>(node->getChildNode());
    procNode->setIsFunctionCall(true);
    procNode->accept(shared_from_this());

    std::string arietyStr = std::to_string(node->getChildNodeList().size());
    std::string id = procNode->getText() + "_" + arietyStr;

    Procedure *proc = nullptr;
    try {
        proc = ptable.lookup(id);
    } catch (const std::out_of_range &e) {
        throw std::runtime_error("Error: undefined procedure \"" + procNode->getText() + "\"\n");
    }

    if (proc->getAriety() != node->getChildNodeList().size()) {
        throw std::runtime_error("Error: procedure \"" + procNode->getText() +
                                 "\" called with incorrect number of arguments\n");
    }

    std::vector<std::shared_ptr<AstNode>> argNodes = node->getChildNodeList();
    for (size_t i = 0; i < argNodes.size(); ++i) {
        argNodes[i]->accept(shared_from_this());
        vtable.bind(Variable(proc->getParams()[i], argNodes[i]->getVal(), argNodes[i]->getType()));
    }

    std::vector<std::shared_ptr<AstNode>> bodyNodes = proc->getBodyNodes();
    for (size_t i = 0; i < bodyNodes.size(); ++i) {
        bodyNodes[i]->accept(shared_from_this());
        std::shared_ptr<ReturnNode> returnNode =
            std::dynamic_pointer_cast<ReturnNode>(bodyNodes[i]);
        if (returnNode) {
            node->setVal(returnNode->getVal());
            node->setType(returnNode->getType());
            break;
        }
    }

    vtable.exitScope();
}

void Evaluator::visit(std::shared_ptr<ProcDecNode> node) {
    std::vector<std::shared_ptr<AstNode>> paramNodes = node->getParamNodes();
    std::vector<std::string> params;
    for (size_t i = 0; i < paramNodes.size(); ++i) {
        params.emplace_back(paramNodes[i]->getText());
    }

    std::vector<std::shared_ptr<AstNode>> bodyNodes = node->getBodyNodes();
    ptable.bind(Procedure(node->getNameNode()->getText(), params, bodyNodes));
}

void Evaluator::visit(std::shared_ptr<ProgNode> node) {
    AstVisitor::visit(std::static_pointer_cast<UnaryNodeList>(node));
}

void Evaluator::visit(std::shared_ptr<ReturnNode> node) {
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    childNode->accept(shared_from_this());
    node->setVal(childNode->getVal());
    node->setType(childNode->getType());
}

void Evaluator::visit(std::shared_ptr<TableNode> node) {}

void Evaluator::visit(std::shared_ptr<UnaryExprNode> node) {}

void Evaluator::visit(std::shared_ptr<WhileNode> node) {}
