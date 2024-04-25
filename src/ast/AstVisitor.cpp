#include <AllNodeIncludes.hpp>
#include <AstVisitor.hpp>

std::any AstVisitor::visit(std::shared_ptr<AndExprNode> node) {
    return visit(std::static_pointer_cast<BinaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<AssignNode> node) {
    return visit(std::static_pointer_cast<BinaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<ColumnNode> node) {
    return visit(std::static_pointer_cast<UnaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<DivExprNode> node) {
    return visit(std::static_pointer_cast<BinaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<ElseNode> node) {
    return visit(std::static_pointer_cast<UnaryNodeList>(node));
}

std::any AstVisitor::visit(std::shared_ptr<EqualExprNode> node) {
    return visit(std::static_pointer_cast<BinaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<ExpoExprNode> node) {
    return visit(std::static_pointer_cast<BinaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<FilterNode> node) {
    return visit(std::static_pointer_cast<BinaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<GreaterEqualExprNode> node) {
    return visit(std::static_pointer_cast<BinaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<GreaterExprNode> node) {
    return visit(std::static_pointer_cast<BinaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<HeaderIndexNode> node) {
    return visit(std::static_pointer_cast<BinaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<IfNode> node) {
    std::shared_ptr<AstNode> condNode = node->getCondNode();
    std::vector<std::shared_ptr<AstNode>> bodyNodes = node->getBodyNodes();
    std::shared_ptr<AstNode> elseNode = node->getElseNode();

    if (condNode != nullptr) {
        condNode->accept(shared_from_this());
    }
    for (size_t i = 0; i < bodyNodes.size(); ++i) {
        bodyNodes[i]->accept(shared_from_this());
    }
    if (elseNode != nullptr) {
        elseNode->accept(shared_from_this());
    }
    return nullptr;
}

std::any AstVisitor::visit(std::shared_ptr<IndexNode> node) {
    return visit(std::static_pointer_cast<BinaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<IntersectionExprNode> node) {
    return visit(std::static_pointer_cast<BinaryNode>(node));
}

std::any AstVisitor::visit([[maybe_unused]]std::shared_ptr<LeafNode> node) { 
    return nullptr;
}

std::any AstVisitor::visit(std::shared_ptr<LessEqualExprNode> node) {
    return visit(std::static_pointer_cast<BinaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<LessExprNode> node) {
    return visit(std::static_pointer_cast<BinaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<ListNode> node) {
    return visit(std::static_pointer_cast<UnaryNodeList>(node));
}

std::any AstVisitor::visit(std::shared_ptr<MinusExprNode> node) {
    return visit(std::static_pointer_cast<BinaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<MinusNode> node) {
    return visit(std::static_pointer_cast<UnaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<ModExprNode> node) {
    return visit(std::static_pointer_cast<BinaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<MultExprNode> node) {
    return visit(std::static_pointer_cast<BinaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<NotEqualExprNode> node) {
    return visit(std::static_pointer_cast<BinaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<NotNode> node) {
    return visit(std::static_pointer_cast<UnaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<OrExprNode> node) {
    return visit(std::static_pointer_cast<BinaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<ParNode> node) {
    return visit(std::static_pointer_cast<UnaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<PlusExprNode> node) {
    return visit(std::static_pointer_cast<BinaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<PlusNode> node) {
    return visit(std::static_pointer_cast<UnaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<ProcCallNode> node) {
    std::shared_ptr<AstNode> procNode = node->getChildNode();
    if (procNode != nullptr) {
        procNode->accept(shared_from_this());
    }

    std::vector<std::shared_ptr<AstNode>> argNodes = node->getChildNodeList();
    for (size_t i = 0; i < argNodes.size(); ++i) {
        argNodes[i]->accept(shared_from_this());
    }
    return nullptr;
}

std::any AstVisitor::visit(std::shared_ptr<ProcDecNode> node) {
    std::vector<std::shared_ptr<AstNode>> paramNodes = node->getParamNodes();
    for (size_t i = 0; i < paramNodes.size(); ++i) {
        paramNodes[i]->accept(shared_from_this());
    }

    std::vector<std::shared_ptr<AstNode>> bodyNodes = node->getBodyNodes();
    for (size_t i = 0; i < bodyNodes.size(); ++i) {
        bodyNodes[i]->accept(shared_from_this());
    }
    return nullptr;
}

std::any AstVisitor::visit(std::shared_ptr<ProgNode> node) {
    return visit(std::static_pointer_cast<UnaryNodeList>(node));
}

std::any AstVisitor::visit(std::shared_ptr<ReturnNode> node) {
    return visit(std::static_pointer_cast<UnaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<TableNode> node) {
    return visit(std::static_pointer_cast<UnaryNodeList>(node));
}

std::any AstVisitor::visit(std::shared_ptr<UnaryExprNode> node) {
    return visit(std::static_pointer_cast<UnaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<UnionExprNode> node) {
    return visit(std::static_pointer_cast<BinaryNode>(node));
}

std::any AstVisitor::visit(std::shared_ptr<WhileNode> node) {
    std::shared_ptr<AstNode> condNode = node->getChildNode();
    if (condNode != nullptr) {
        condNode->accept(shared_from_this());
    }

    std::vector<std::shared_ptr<AstNode>> stmNodes = node->getChildNodeList();
    for (size_t i = 0; i < stmNodes.size(); ++i) {
        stmNodes[i]->accept(shared_from_this());
    }
    return nullptr;
}

// Util

std::any AstVisitor::visit(const std::shared_ptr<BinaryNode> node) {
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    std::shared_ptr<AstNode> rightNode = node->getRightNode();

    if (leftNode != nullptr) {
        leftNode->accept(shared_from_this());
    }
    if (rightNode != nullptr) {
        rightNode->accept(shared_from_this());
    }
    return nullptr;
}

std::any AstVisitor::visit(const std::shared_ptr<UnaryNode> node) {
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    if (childNode != nullptr) {
        childNode->accept(shared_from_this());
    }
    return nullptr;
}

std::any AstVisitor::visit(const std::shared_ptr<UnaryNodeList> node) {
    std::vector<std::shared_ptr<AstNode>> childNodes = node->getChildNodeList();
    for (size_t i = 0; i < childNodes.size(); ++i) {
        childNodes[i]->accept(shared_from_this());
    }
    return nullptr;
}