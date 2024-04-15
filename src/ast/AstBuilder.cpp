#include <AstBuilder.hpp>

antlrcpp::Any AstBuilder::visitProg(DplParser::ProgContext* parseNode) {
    std::shared_ptr<ProgNode> newNode = std::make_shared<ProgNode>();
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

    return void;
}

antlrcpp::Any AstBuilder::visitBlock(DplParser::BlockContext* parseNode) {
    parseNode->children[2]->accept(this);

    return void;
}

antlrcpp::Any AstBuilder::visitStms(DplParser::StmsContext* parseNode) {
    for (size_t i = 0; i < parseNode->children.size(); i++) {
        if (parseNode->children[i]->getText() != "\n") {
            parseNode->children[i]->accept(this);
        }
    }
    return void;
}

antlrcpp::Any AstBuilder::visitProcdec(DplParser::ProcdecContext* parseNode) {
    std::string name = parseNode->children[1]->getText();

    std::shared_ptr<ProcDecNode> newNode = std::make_shared<ProcDecNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setName(name);

    std::shared_ptr<AstNode> astNewNode = std::static_pointer_cast<AstNode>(newNode);

    currentNode->addChild(astNewNode);
    std::shared_ptr<AstNode> oldNode = currentNode;
    currentNode = astNewNode;

    size_t blockIndex = 5;
    if (parseNode->children.size() > blockIndex) {
        parseNode->children[3]->accept(this);
        blockIndex = 6;
    }
    newNode->stopVisitingParams();
    parseNode->children[blockIndex]->accept(this);

    currentNode = oldNode;

    return void;
}

antlrcpp::Any AstBuilder::visitAssignstm(DplParser::AssignstmContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }
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

    return void;
}

// Return
antlrcpp::Any AstBuilder::visitReturnstm(DplParser::ReturnstmContext* parseNode) {
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

    return void;
}

// IF-ELSE
antlrcpp::Any AstBuilder::visitIfstm(DplParser::IfstmContext* parseNode) {
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

    return void;
}

antlrcpp::Any AstBuilder::visitElsestm(DplParser::ElsestmContext* parseNode) {
    std::shared_ptr<AstNode> newNode = std::make_shared<ElseNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("Else");

    currentNode->addChild(newNode);
    std::shared_ptr<AstNode> oldNode = currentNode;
    currentNode = newNode;

    parseNode->children[2]->accept(this);

    currentNode = oldNode;

    return void;
}

// While
antlrcpp::Any AstBuilder::visitWhilestm(DplParser::WhilestmContext* parseNode) {
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

    return void;
}

// Expressions  The expressions isn't correctly sequenced
antlrcpp::Any AstBuilder::visitJuncexpr(DplParser::JuncexprContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }
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

    return void;
}

antlrcpp::Any AstBuilder::visitNotexpr(DplParser::NotexprContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }
    std::shared_ptr<AstNode> newNode = std::make_shared<NotNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText(parseNode->op->getText());

    currentNode->addChild(newNode);
    std::shared_ptr<AstNode> oldNode = currentNode;
    currentNode = newNode;

    parseNode->children[1]->accept(this);

    currentNode = oldNode;

    return void;
}

antlrcpp::Any AstBuilder::visitCompexpr(DplParser::CompexprContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }
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

    return void;
}

antlrcpp::Any AstBuilder::visitArthexpr(DplParser::ArthexprContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }
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

    return void;
}

// Terms
antlrcpp::Any AstBuilder::visitTerminal(tree::TerminalNode* node) {
    std::shared_ptr<AstNode> newNode = std::make_shared<LeafNode>(currentNode);
    newNode->setRule(node->getSymbol()->getType());
    newNode->setText(node->getText());

    currentNode->addChild(newNode);

    return void;
}

antlrcpp::Any AstBuilder::visitList(DplParser::ListContext* parseNode) {
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

    return void;
}

antlrcpp::Any AstBuilder::visitTable(DplParser::TableContext* parseNode) {
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

    return void;
}

antlrcpp::Any AstBuilder::visitColumn(DplParser::ColumnContext* parseNode) {
    std::shared_ptr<AstNode> newNode = std::make_shared<ColumnNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText(parseNode->children[0]->getText() + ":");

    currentNode->addChild(newNode);
    std::shared_ptr<AstNode> oldNode = currentNode;
    currentNode = newNode;

    parseNode->children[2]->accept(this);

    currentNode = oldNode;

    return void;
}

antlrcpp::Any AstBuilder::visitTerm(DplParser::TermContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }

    std::shared_ptr<AstNode> newNode = std::make_shared<ParNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("() Parenthesis");

    currentNode->addChild(newNode);
    std::shared_ptr<AstNode> oldNode = currentNode;
    currentNode = newNode;

    parseNode->children[1]->accept(this);

    currentNode = oldNode;

    return void;
}

antlrcpp::Any AstBuilder::visitSubscript(DplParser::SubscriptContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }

    std::shared_ptr<AstNode> oldNode = currentNode;

    parseNode->children[1]->accept(this);

    parseNode->children[0]->accept(this);

    currentNode = oldNode;

    return void;
}

antlrcpp::Any AstBuilder::visitIndex(DplParser::IndexContext* parseNode) {
    std::shared_ptr<AstNode> newNode = std::make_shared<IndexNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("[] Indexing");

    currentNode->addChild(newNode);
    currentNode = newNode;

    parseNode->children[1]->accept(this);

    return void;
}

antlrcpp::Any AstBuilder::visitHeaderindex(DplParser::HeaderindexContext* parseNode) {
    std::shared_ptr<AstNode> newNode = std::make_shared<HeaderIndexNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("[$] Header Indexing");

    currentNode->addChild(newNode);
    currentNode = newNode;

    parseNode->children[2]->accept(this);

    return void;
}

antlrcpp::Any AstBuilder::visitFiltering(DplParser::FilteringContext* parseNode) {
    std::shared_ptr<AstNode> newNode = std::make_shared<FilterNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("[] Filter");

    currentNode->addChild(newNode);
    currentNode = newNode;

    parseNode->children[1]->accept(this);

    return void;
}

antlrcpp::Any AstBuilder::visitUnaryexpr(DplParser::UnaryexprContext* parseNode) {
    std::shared_ptr<AstNode> newNode = std::make_shared<UnaryExprNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText(parseNode->children[0]->getText());

    currentNode->addChild(newNode);
    std::shared_ptr<AstNode> oldNode = currentNode;
    currentNode = newNode;

    parseNode->children[1]->accept(this);

    currentNode = oldNode;

    return void;
}

antlrcpp::Any AstBuilder::visitProccall(DplParser::ProccallContext* parseNode) {
    std::shared_ptr<ProcCallNode> newNode = std::make_shared<ProcCallNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());

    std::shared_ptr<AstNode> astNewNode = std::static_pointer_cast<AstNode>(newNode);
    currentNode->addChild(astNewNode);
    currentNode = astNewNode;

    if (parseNode->children.size() == 2) {
        newNode->stopVisitingParams();
        return void;
    }

    parseNode->children[1]->accept(this);
    newNode->stopVisitingParams();

    return void;
}

antlrcpp::Any AstBuilder::visitArgs(DplParser::ArgsContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }

    for (size_t i = 0; i < parseNode->children.size(); i = i + 2) {
        parseNode->children[i]->accept(this);
    }

    return void;
}

antlrcpp::Any AstBuilder::visitParams(DplParser::ParamsContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }

    for (size_t i = 0; i < parseNode->children.size(); i = i + 2) {
        parseNode->children[i]->accept(this);
    }

    return void;
}

std::shared_ptr<AstNode> AstBuilder::getRoot() { return root; }
