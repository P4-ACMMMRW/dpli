#include <AstBuilder.hpp>

antlrcpp::Any AstBuilder::visitProg(DplParser::ProgContext* parseNode) {
    auto newNode = std::make_shared<ProgNode>();
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText(parser->getRuleNames()[newNode->getRule()]);

    root = newNode;
    currentNode = newNode;

    std::vector<tree::ParseTree*> children = parseNode->children;

    for (size_t i = 0; i < children.size(); i++) {
        if (children[i]->getText() != "\n") {
            children[i]->accept(this);
        }
    }

    return nullptr;
}

antlrcpp::Any AstBuilder::visitBlock(DplParser::BlockContext* parseNode) {
    std::cout << "got to Block" << "\n";
    parseNode->children[2]->accept(this);

    return nullptr;
}

antlrcpp::Any AstBuilder::visitStms(DplParser::StmsContext* parseNode) {
    std::cout << "got to stms" << "\n";
    for (size_t i = 0; i < parseNode->children.size(); i++) {
        if (parseNode->children[i]->getText() != "\n") {
            parseNode->children[i]->accept(this);
        }
    }
    return nullptr;
}

antlrcpp::Any AstBuilder::visitProcdec(DplParser::ProcdecContext* parseNode) {
    std::cout << "got to ProcDec" << "\n";
    std::shared_ptr<ProcDecNode> newNode = std::make_shared<ProcDecNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("def ()");

    std::shared_ptr<AstNode> astNewNode = std::static_pointer_cast<AstNode>(newNode);

    currentNode->addChild(astNewNode);
    std::shared_ptr<AstNode> oldNode = currentNode;
    currentNode = astNewNode;

    parseNode->children[1]->accept(this);

    size_t blockIndex = 5;
    if (parseNode->children.size() > blockIndex) {
        parseNode->children[3]->accept(this);
        blockIndex = 6;
    }
    newNode->stopVisitingParams();
    parseNode->children[blockIndex]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitAssignstm(DplParser::AssignstmContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }
    std::cout << "got to Assign" << "\n";

    std::shared_ptr<AstNode> newNode = std::make_shared<AssignNode>(currentNode);
    newNode->setText(parseNode->children[1]->getText());

    currentNode->addChild(newNode);
    std::shared_ptr<AstNode> oldNode = currentNode;
    currentNode = newNode;


    // Left Node
    parseNode->children[0]->accept(this);

    // Right Node
    parseNode->children[2]->accept(this);
    

    currentNode = oldNode;

    return nullptr;
}

// Return
antlrcpp::Any AstBuilder::visitReturnstm(DplParser::ReturnstmContext* parseNode) {
    std::cout << "got to ReturnStm" << "\n";
    std::shared_ptr<AstNode> newNode = std::make_shared<ReturnNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("Return");

    currentNode->addChild(newNode);
    std::shared_ptr<AstNode> oldNode = currentNode;
    currentNode = newNode;

    if (parseNode->children.size() > 1) {
        parseNode->children[1]->accept(this);
    }

    currentNode = oldNode;

    return nullptr;
}

// IF-ELSE
antlrcpp::Any AstBuilder::visitIfstm(DplParser::IfstmContext* parseNode) {
    std::cout << "got to IfStm" << "\n";
    std::shared_ptr<AstNode> newNode = std::make_shared<IfNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("If");

    currentNode->addChild(newNode);
    std::shared_ptr<AstNode> oldNode = currentNode;
    currentNode = newNode;

    // Condition
    parseNode->children[1]->accept(this);

    // Body
    parseNode->children[3]->accept(this);

    // Else
    if (parseNode->children.size() > 4) {
        parseNode->children[4]->accept(this);
    }

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitElsestm(DplParser::ElsestmContext* parseNode) {
    std::cout << "got to Elsestm" << "\n";
    std::shared_ptr<AstNode> newNode = std::make_shared<ElseNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("Else");

    currentNode->addChild(newNode);
    std::shared_ptr<AstNode> oldNode = currentNode;
    currentNode = newNode;

    parseNode->children[2]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

// While
antlrcpp::Any AstBuilder::visitWhilestm(DplParser::WhilestmContext* parseNode) {
    std::cout << "got to While" << "\n";
    std::shared_ptr<AstNode> newNode = std::make_shared<WhileNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("While");

    currentNode->addChild(newNode);
    std::shared_ptr<AstNode> oldNode = currentNode;
    currentNode = newNode;

    // Condition
    parseNode->children[1]->accept(this);

    // Body
    parseNode->children[3]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

// Expressions  The expressions isn't correctly sequenced
antlrcpp::Any AstBuilder::visitJuncexpr(DplParser::JuncexprContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }
    std::cout << "got to Junc" << "\n";
    std::shared_ptr<AstNode> newNode = std::make_shared<JuncExprNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText(parseNode->op->getText());

    currentNode->addChild(newNode);
    std::shared_ptr<AstNode> oldNode = currentNode;
    currentNode = newNode;

    // Left Node
    parseNode->children[0]->accept(this);

    // Right Node
    parseNode->children[2]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitNotexpr(DplParser::NotexprContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }
    std::cout << "got to Not" << "\n";
    std::shared_ptr<AstNode> newNode = std::make_shared<NotNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText(parseNode->op->getText());

    currentNode->addChild(newNode);
    std::shared_ptr<AstNode> oldNode = currentNode;
    currentNode = newNode;

    parseNode->children[1]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitCompexpr(DplParser::CompexprContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }
    std::cout << "got to Compexpr" << "\n";
    std::shared_ptr<AstNode> newNode = std::make_shared<CompExprNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText(parseNode->op->getText());

    currentNode->addChild(newNode);
    std::shared_ptr<AstNode> oldNode = currentNode;
    currentNode = newNode;

    // Left Node
    parseNode->children[0]->accept(this);

    // Right Node
    parseNode->children[2]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitArthexpr(DplParser::ArthexprContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }
    std::cout << "got to Arthexpr" << "\n";

    std::shared_ptr<AstNode> newNode = std::make_shared<ArthExprNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText(parseNode->op->getText());

    currentNode->addChild(newNode);
    std::shared_ptr<AstNode> oldNode = currentNode;
    currentNode = newNode;

    // Left Node
    parseNode->children[0]->accept(this);

    // Right Node
    parseNode->children[2]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

// Terms
antlrcpp::Any AstBuilder::visitTerminal(tree::TerminalNode* node) {
    std::cout << "got to terminal" << "\n";
    std::shared_ptr<AstNode> newNode = std::make_shared<LeafNode>(currentNode);
    newNode->setRule(node->getSymbol()->getType());
    newNode->setText(node->getText());

    std::cout << "got to terminal 1" << "\n";
    currentNode->addChild(newNode);
    std::cout << "got to terminal 2" << "\n";

    return nullptr;
}

antlrcpp::Any AstBuilder::visitList(DplParser::ListContext* parseNode) {
    std::cout << "got to list" << "\n";
    std::shared_ptr<AstNode> newNode = std::make_shared<ListNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("[] List");

    currentNode->addChild(newNode);
    std::shared_ptr<AstNode> oldNode = currentNode;
    currentNode = newNode;

    if (parseNode->children.size() == 3) {
        parseNode->children[1]->accept(this);
    }

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitTable(DplParser::TableContext* parseNode) {
    std::cout << "got to table" << "\n";
    std::shared_ptr<AstNode> newNode = std::make_shared<TableNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("{} Table");

    currentNode->addChild(newNode);
    std::shared_ptr<AstNode> oldNode = currentNode;
    currentNode = newNode;

    std::vector<tree::ParseTree*> children = parseNode->children;

    for (size_t i = 1; i < children.size(); i = i + 2) {
        children[i]->accept(this);
    }

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitColumn(DplParser::ColumnContext* parseNode) {
    std::cout << "got to column" << "\n";
    std::shared_ptr<AstNode> newNode = std::make_shared<ColumnNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText(parseNode->children[0]->getText() + ":");

    currentNode->addChild(newNode);
    std::shared_ptr<AstNode> oldNode = currentNode;
    currentNode = newNode;

    parseNode->children[2]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitTerm(DplParser::TermContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }
    std::cout << "got to term" << "\n";

    std::shared_ptr<AstNode> newNode = std::make_shared<ParNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("() Parenthesis");

    currentNode->addChild(newNode);
    std::shared_ptr<AstNode> oldNode = currentNode;
    currentNode = newNode;

    parseNode->children[1]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitSubscript(DplParser::SubscriptContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }
    std::cout << "got to subscript" << "\n";

    std::shared_ptr<AstNode> oldNode = currentNode;

    parseNode->children[1]->accept(this);

    parseNode->children[0]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitIndex(DplParser::IndexContext* parseNode) {
    std::cout << "got to index" << "\n";
    std::shared_ptr<AstNode> newNode = std::make_shared<IndexNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("[] Indexing");

    currentNode->addChild(newNode);
    currentNode = newNode;

    parseNode->children[1]->accept(this);

    return nullptr;
}

antlrcpp::Any AstBuilder::visitHeaderindex(DplParser::HeaderindexContext* parseNode) {
    std::cout << "got to headerindex" << "\n";
    std::shared_ptr<AstNode> newNode = std::make_shared<HeaderIndexNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("[$] Header Indexing");

    currentNode->addChild(newNode);
    currentNode = newNode;

    parseNode->children[2]->accept(this);

    return nullptr;
}

antlrcpp::Any AstBuilder::visitFiltering(DplParser::FilteringContext* parseNode) {
    std::cout << "got to filtering" << "\n";
    std::shared_ptr<AstNode> newNode = std::make_shared<FilterNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("[] Filter");

    currentNode->addChild(newNode);
    currentNode = newNode;

    parseNode->children[1]->accept(this);

    return nullptr;
}

antlrcpp::Any AstBuilder::visitUnaryexpr(DplParser::UnaryexprContext* parseNode) {
    std::cout << "got to unaryexpr" << "\n";
    std::shared_ptr<AstNode> newNode = std::make_shared<UnaryExprNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText(parseNode->children[0]->getText());

    currentNode->addChild(newNode);
    std::shared_ptr<AstNode> oldNode = currentNode;
    currentNode = newNode;

    parseNode->children[1]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitProccall(DplParser::ProccallContext* parseNode) {
    std::cout << "got to proccall" << "\n";
    std::shared_ptr<ProcCallNode> newNode = std::make_shared<ProcCallNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("() proccall");

    std::shared_ptr<AstNode> astNewNode = std::static_pointer_cast<AstNode>(newNode);
    currentNode->addChild(astNewNode);
    currentNode = astNewNode;


    if (parseNode->children.size() == 2) {
        std::cout << "got to proccall 4" << "\n";
        newNode->stopVisitingParams();
        return nullptr;
    }

    parseNode->children[1]->accept(this);
    newNode->stopVisitingParams();

    return nullptr;
}

antlrcpp::Any AstBuilder::visitArgs(DplParser::ArgsContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }
    std::cout << "got to args" << "\n";

    for (size_t i = 0; i < parseNode->children.size(); i = i + 2) {
        parseNode->children[i]->accept(this);
    }

    return nullptr;
}

antlrcpp::Any AstBuilder::visitParams(DplParser::ParamsContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }
    std::cout << "got to params" << "\n";

    for (size_t i = 0; i < parseNode->children.size(); i = i + 2) {
        parseNode->children[i]->accept(this);
    }

    return nullptr;
}

std::shared_ptr<AstNode> AstBuilder::getRoot() { return root; }
