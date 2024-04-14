#include <AllNodeIncludes.hpp>
#include <AstTestVisitor.hpp>

void AstTestVisitor::visit(std::shared_ptr<ArthExprNode> node) {
    std::cout << "Visiting " << node->getText() << '\n';
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    std::shared_ptr<AstNode> rightNode = node->getRightNode();

    if (leftNode != nullptr) {
        leftNode->accept(shared_from_this());
    }
    if (rightNode != nullptr) {
        rightNode->accept(shared_from_this());
    }
}

void AstTestVisitor::visit(std::shared_ptr<AssignNode> node) {
    std::cout << "Visiting " << node->getText() << '\n';
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    std::shared_ptr<AstNode> rightNode = node->getRightNode();

    if (leftNode != nullptr) {
        leftNode->accept(shared_from_this());
    }
    if (rightNode != nullptr) {
        rightNode->accept(shared_from_this());
    }
}

void AstTestVisitor::visit(std::shared_ptr<ColumnNode> node) {
    std::cout << "Visiting " << node->getText() << '\n';
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    if (childNode != nullptr) {
        childNode->accept(shared_from_this());
    }
}

void AstTestVisitor::visit(std::shared_ptr<CompExprNode> node) {
    std::cout << "Visiting " << node->getText() << '\n';
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    std::shared_ptr<AstNode> rightNode = node->getRightNode();

    if (leftNode != nullptr) {
        leftNode->accept(shared_from_this());
    }
    if (rightNode != nullptr) {
        rightNode->accept(shared_from_this());
    }
}

void AstTestVisitor::visit(std::shared_ptr<ElseNode> node) {
    std::cout << "Visiting " << node->getText() << '\n';
    std::vector<std::shared_ptr<AstNode>> bodyNodes = node->getBodyNodes();
    for (size_t i = 0; i < bodyNodes.size(); ++i) {
        bodyNodes[i]->accept(shared_from_this());
    }
}

void AstTestVisitor::visit(std::shared_ptr<FilterNode> node) {
    std::cout << "Visiting " << node->getText() << '\n';
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    std::shared_ptr<AstNode> rightNode = node->getRightNode();

    if (leftNode != nullptr) {
        leftNode->accept(shared_from_this());
    }
    if (rightNode != nullptr) {
        rightNode->accept(shared_from_this());
    }
}

void AstTestVisitor::visit(std::shared_ptr<HeaderIndexNode> node) {
    std::cout << "Visiting " << node->getText() << '\n';
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    std::shared_ptr<AstNode> rightNode = node->getRightNode();

    if (leftNode != nullptr) {
        leftNode->accept(shared_from_this());
    }
    if (rightNode != nullptr) {
        rightNode->accept(shared_from_this());
    }
}

void AstTestVisitor::visit(std::shared_ptr<IfNode> node) {
    std::cout << "Visiting " << node->getText() << '\n';
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
}

void AstTestVisitor::visit(std::shared_ptr<IndexNode> node) {
    std::cout << "Visiting " << node->getText() << '\n';
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    std::shared_ptr<AstNode> rightNode = node->getRightNode();

    if (leftNode != nullptr) {
        leftNode->accept(shared_from_this());
    }
    if (rightNode != nullptr) {
        rightNode->accept(shared_from_this());
    }
}

void AstTestVisitor::visit(std::shared_ptr<JuncExprNode> node) {
    std::cout << "Visiting " << node->getText() << '\n';
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    std::shared_ptr<AstNode> rightNode = node->getRightNode();

    if (leftNode != nullptr) {
        leftNode->accept(shared_from_this());
    }
    if (rightNode != nullptr) {
        rightNode->accept(shared_from_this());
    }
}

void AstTestVisitor::visit(std::shared_ptr<LeafNode> node) {
    std::cout << "Visiting " << node->getText() << '\n';
}

void AstTestVisitor::visit(std::shared_ptr<ListNode> node) {
    std::cout << "Visiting " << node->getText() << '\n';
    std::vector<std::shared_ptr<AstNode>> childNodes = node->getChildNodes();
    for (size_t i = 0; i < childNodes.size(); ++i) {
        childNodes[i]->accept(shared_from_this());
    }
}

void AstTestVisitor::visit(std::shared_ptr<NotNode> node) {
    std::cout << "Visiting " << node->getText() << '\n';
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    if (childNode != nullptr) {
        childNode->accept(shared_from_this());
    }
}

void AstTestVisitor::visit(std::shared_ptr<ParNode> node) {
    std::cout << "Visiting " << node->getText() << '\n';
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    if (childNode != nullptr) {
        childNode->accept(shared_from_this());
    }
}

void AstTestVisitor::visit(std::shared_ptr<ProcCallNode> node) {
    std::cout << "Visiting " << node->getText() << '\n';
    std::shared_ptr<AstNode> procNode = node->getProcNode();
    if (procNode != nullptr) {
        procNode->accept(shared_from_this());
    }

    std::vector<std::shared_ptr<AstNode>> argNodes = node->getArgNodes();
    for (size_t i = 0; i < argNodes.size(); ++i) {
        argNodes[i]->accept(shared_from_this());
    }
}

void AstTestVisitor::visit(std::shared_ptr<ProcDecNode> node) {
    std::cout << "Visiting " << node->getText() << '\n';
    std::vector<std::shared_ptr<AstNode>> paramNodes = node->getParamNodes();
    for (size_t i = 0; i < paramNodes.size(); ++i) {
        paramNodes[i]->accept(shared_from_this());
    }

    std::vector<std::shared_ptr<AstNode>> bodyNodes = node->getBodyNodes();
    for (size_t i = 0; i < bodyNodes.size(); ++i) {
        bodyNodes[i]->accept(shared_from_this());
    }
}

void AstTestVisitor::visit(std::shared_ptr<ProgNode> node) {
    std::cout << "Visiting " << node->getText() << '\n';
    std::vector<std::shared_ptr<AstNode>> childNodes = node->getChildNodes();
    for (size_t i = 0; i < childNodes.size(); ++i) {
        childNodes[i]->accept(shared_from_this());
    }
}

void AstTestVisitor::visit(std::shared_ptr<ReturnNode> node) {
    std::cout << "Visiting " << node->getText() << '\n';
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    if (childNode != nullptr) {
        childNode->accept(shared_from_this());
    }
}

void AstTestVisitor::visit(std::shared_ptr<TableNode> node) {
    std::cout << "Visiting " << node->getText() << '\n';
    std::vector<std::shared_ptr<AstNode>> columnNodes = node->getColumnNodes();
    for (size_t i = 0; i < columnNodes.size(); ++i) {
        columnNodes[i]->accept(shared_from_this());
    }
}

void AstTestVisitor::visit(std::shared_ptr<UnaryExprNode> node) {
    std::cout << "Visiting " << node->getText() << '\n';
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    if (childNode != nullptr) {
        childNode->accept(shared_from_this());
    }
}

void AstTestVisitor::visit(std::shared_ptr<WhileNode> node) {
    std::cout << "Visiting " << node->getText() << '\n';
    std::shared_ptr<AstNode> condNode = node->getCondNode();
    if (condNode != nullptr) {
        condNode->accept(shared_from_this());
    }

    std::vector<std::shared_ptr<AstNode>> stmNodes = node->getStmNodes();
    for (size_t i = 0; i < stmNodes.size(); ++i) {
        stmNodes[i]->accept(shared_from_this());
    }
}
