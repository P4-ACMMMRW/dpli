#include <AllNodeIncludes.hpp>
#include <AstTestVisitor.hpp>

void AstTestVisitor::visit(ArthExprNode* node) {
    std::cout << "Visiting " << node->getText() << std::endl;
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    std::shared_ptr<AstNode> rightNode = node->getRightNode();

    if (leftNode != nullptr) {
        leftNode->accept(this);
    }
    if (rightNode != nullptr) {
        rightNode->accept(this);
    }
}

void AstTestVisitor::visit(AssignNode* node) {
    std::cout << "Visiting " << node->getText() << std::endl;
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    std::shared_ptr<AstNode> rightNode = node->getRightNode();

    if (leftNode != nullptr) {
        leftNode->accept(this);
    }
    if (rightNode != nullptr) {
        rightNode->accept(this);
    }
}

void AstTestVisitor::visit(ColumnNode* node) {
    std::cout << "Visiting " << node->getText() << std::endl;
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    if (childNode != nullptr) {
        childNode->accept(this);
    }
}

void AstTestVisitor::visit(CompExprNode* node) {
    std::cout << "Visiting " << node->getText() << std::endl;
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    std::shared_ptr<AstNode> rightNode = node->getRightNode();

    if (leftNode != nullptr) {
        leftNode->accept(this);
    }
    if (rightNode != nullptr) {
        rightNode->accept(this);
    }
}

void AstTestVisitor::visit(ElseNode* node) {
    std::cout << "Visiting " << node->getText() << std::endl;
    std::vector<std::shared_ptr<AstNode>> bodyNodes = node->getBodyNodes();
    for (size_t i = 0; i < bodyNodes.size(); ++i) {
        bodyNodes[i]->accept(this);
    }
}

void AstTestVisitor::visit(FilterNode* node) {
    std::cout << "Visiting " << node->getText() << std::endl;
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    std::shared_ptr<AstNode> rightNode = node->getRightNode();

    if (leftNode != nullptr) {
        leftNode->accept(this);
    }
    if (rightNode != nullptr) {
        rightNode->accept(this);
    }
}

void AstTestVisitor::visit(HeaderIndexNode* node) {
    std::cout << "Visiting " << node->getText() << std::endl;
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    std::shared_ptr<AstNode> rightNode = node->getRightNode();

    if (leftNode != nullptr) {
        leftNode->accept(this);
    }
    if (rightNode != nullptr) {
        rightNode->accept(this);
    }
}

void AstTestVisitor::visit(IfNode* node) {
    std::cout << "Visiting " << node->getText() << std::endl;
    std::shared_ptr<AstNode> condNode = node->getCondNode();
    std::vector<std::shared_ptr<AstNode>> bodyNodes = node->getBodyNodes();
    std::shared_ptr<AstNode> elseNode = node->getElseNode();

    if (condNode != nullptr) {
        condNode->accept(this);
    }
    for (size_t i = 0; i < bodyNodes.size(); ++i) {
        bodyNodes[i]->accept(this);
    }
    if (elseNode != nullptr) {
        elseNode->accept(this);
    }
}

void AstTestVisitor::visit(IndexNode* node) {
    std::cout << "Visiting " << node->getText() << std::endl;
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    std::shared_ptr<AstNode> rightNode = node->getRightNode();

    if (leftNode != nullptr) {
        leftNode->accept(this);
    }
    if (rightNode != nullptr) {
        rightNode->accept(this);
    }
}

void AstTestVisitor::visit(JuncExprNode* node) {
    std::cout << "Visiting " << node->getText() << std::endl;
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    std::shared_ptr<AstNode> rightNode = node->getRightNode();

    if (leftNode != nullptr) {
        leftNode->accept(this);
    }
    if (rightNode != nullptr) {
        rightNode->accept(this);
    }
}

void AstTestVisitor::visit(LeafNode* node) {
    std::cout << "Visiting " << node->getText() << std::endl;
}

void AstTestVisitor::visit(ListNode* node) {
    std::cout << "Visiting " << node->getText() << std::endl;
    std::vector<std::shared_ptr<AstNode>> childNodes = node->getChildNodes();
    for (size_t i = 0; i < childNodes.size(); ++i) {
        childNodes[i]->accept(this);
    }
}

void AstTestVisitor::visit(NotNode* node) {
    std::cout << "Visiting " << node->getText() << std::endl;
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    if (childNode != nullptr) {
        childNode->accept(this);
    }
}

void AstTestVisitor::visit(ParNode* node) {
    std::cout << "Visiting " << node->getText() << std::endl;
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    if (childNode != nullptr) {
        childNode->accept(this);
    }
}

void AstTestVisitor::visit(ProcCallNode* node) {
    std::cout << "Visiting " << node->getText() << std::endl;
    std::shared_ptr<AstNode> procNode = node->getProcNode();
    if (procNode != nullptr) {
        procNode->accept(this);
    }

    std::vector<std::shared_ptr<AstNode>> argNodes = node->getArgNodes();
    for (size_t i = 0; i < argNodes.size(); ++i) {
        argNodes[i]->accept(this);
    }
}

void AstTestVisitor::visit(ProcDecNode* node) {
    std::cout << "Visiting " << node->getText() << std::endl;
    std::vector<std::shared_ptr<AstNode>> paramNodes = node->getParamNodes();
    for (size_t i = 0; i < paramNodes.size(); ++i) {
        paramNodes[i]->accept(this);
    }

    std::vector<std::shared_ptr<AstNode>> bodyNodes = node->getBodyNodes();
    for (size_t i = 0; i < bodyNodes.size(); ++i) {
        bodyNodes[i]->accept(this);
    }
}

void AstTestVisitor::visit(ProgNode* node) {
    std::cout << "Visiting " << node->getText() << std::endl;
    std::vector<std::shared_ptr<AstNode>> childNodes = node->getChildNodes();
    for (size_t i = 0; i < childNodes.size(); ++i) {
        childNodes[i]->accept(this);
    }
}

void AstTestVisitor::visit(ReturnNode* node) {
    std::cout << "Visiting " << node->getText() << std::endl;
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    if (childNode != nullptr) {
        childNode->accept(this);
    }
}

void AstTestVisitor::visit(TableNode* node) {
    std::cout << "Visiting " << node->getText() << std::endl;
    std::vector<std::shared_ptr<AstNode>> columnNodes = node->getColumnNodes();
    for (size_t i = 0; i < columnNodes.size(); ++i) {
        columnNodes[i]->accept(this);
    }
}

void AstTestVisitor::visit(UnaryExprNode* node) {
    std::cout << "Visiting " << node->getText() << std::endl;
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    if (childNode != nullptr) {
        childNode->accept(this);
    }
}

void AstTestVisitor::visit(WhileNode* node) {
    std::cout << "Visiting " << node->getText() << std::endl;
    std::shared_ptr<AstNode> condNode = node->getCondNode();
    if (condNode != nullptr) {
        condNode->accept(this);
    }

    std::vector<std::shared_ptr<AstNode>> stmNodes = node->getStmNodes();
    for (size_t i = 0; i < stmNodes.size(); ++i) {
        stmNodes[i]->accept(this);
    }
}
