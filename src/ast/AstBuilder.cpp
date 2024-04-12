#include <AstBuilder.hpp>

antlrcpp::Any AstBuilder::visitProg(DplParser::ProgContext* parseNode) {
    AstNode* newNode = new ProgNode();
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText(parser->getRuleNames()[newNode->getRule()]);

    root = newNode;
    currentNode = newNode;

    std::vector<tree::ParseTree*> children = parseNode->children;

    for (size_t i = 0; i < children.size(); i++) {
        if (children[i]->getText() != "\n") children[i]->accept(this);
    }

    return nullptr;
}

antlrcpp::Any AstBuilder::visitBlock(DplParser::BlockContext* parseNode) {
    parseNode->children[2]->accept(this);

    return nullptr;
}

antlrcpp::Any AstBuilder::visitStms(DplParser::StmsContext* parseNode) {
    for (size_t i = 0; i < parseNode->children.size(); i++) {
        if (parseNode->children[i]->getText() != "\n") parseNode->children[i]->accept(this);
    }
    return nullptr;
}

antlrcpp::Any AstBuilder::visitProcdec(DplParser::ProcdecContext* parseNode) {
    std::string name = parseNode->children[1]->getText();

    ProcDecNode* newNode = new ProcDecNode(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setName(name);

    AstNode* astNewNode = static_cast<AstNode*>(newNode);

    currentNode->addChild(astNewNode);
    AstNode* oldNode = currentNode;
    currentNode = astNewNode;

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
    if (parseNode->children.size() == 1) return parseNode->children[0]->accept(this);
    AstNode* newNode = new AssignNode(currentNode);
    newNode->setText(parseNode->children[1]->getText());

    currentNode->addChild(newNode);
    AstNode* oldNode = currentNode;
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
    AstNode* newNode = new ReturnNode(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("Return");

    currentNode->addChild(newNode);
    AstNode* oldNode = currentNode;
    currentNode = newNode;

    if (parseNode->children.size() > 1) {
        parseNode->children[1]->accept(this);
    }

    currentNode = oldNode;

    return nullptr;
}

// IF-ELSE
antlrcpp::Any AstBuilder::visitIfstm(DplParser::IfstmContext* parseNode) {
    AstNode* newNode = new IfNode(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("If");

    currentNode->addChild(newNode);
    AstNode* oldNode = currentNode;
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
    AstNode* newNode = new ElseNode(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("Else");

    currentNode->addChild(newNode);
    AstNode* oldNode = currentNode;
    currentNode = newNode;

    parseNode->children[2]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

// While
antlrcpp::Any AstBuilder::visitWhilestm(DplParser::WhilestmContext* parseNode) {
    AstNode* newNode = new WhileNode(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("While");

    currentNode->addChild(newNode);
    AstNode* oldNode = currentNode;
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
    if (parseNode->children.size() == 1) return parseNode->children[0]->accept(this);
    AstNode* newNode = new JuncExprNode(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText(parseNode->op->getText());

    currentNode->addChild(newNode);
    AstNode* oldNode = currentNode;
    currentNode = newNode;

    // Left Node
    parseNode->children[0]->accept(this);

    // Right Node
    parseNode->children[2]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitNotexpr(DplParser::NotexprContext* parseNode) {
    if (parseNode->children.size() == 1) return parseNode->children[0]->accept(this);
    AstNode* newNode = new NotNode(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText(parseNode->op->getText());

    currentNode->addChild(newNode);
    AstNode* oldNode = currentNode;
    currentNode = newNode;

    parseNode->children[1]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitCompexpr(DplParser::CompexprContext* parseNode) {
    if (parseNode->children.size() == 1) return parseNode->children[0]->accept(this);
    AstNode* newNode = new CompExprNode(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText(parseNode->op->getText());

    currentNode->addChild(newNode);
    AstNode* oldNode = currentNode;
    currentNode = newNode;

    // Left Node
    parseNode->children[0]->accept(this);

    // Right Node
    parseNode->children[2]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitArthexpr(DplParser::ArthexprContext* parseNode) {
    if (parseNode->children.size() == 1) return parseNode->children[0]->accept(this);
    AstNode* newNode = new ArthExprNode(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText(parseNode->op->getText());

    currentNode->addChild(newNode);
    AstNode* oldNode = currentNode;
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
    AstNode* newNode = new LeafNode(currentNode);
    newNode->setRule(node->getSymbol()->getType());
    newNode->setText(node->getText());

    currentNode->addChild(newNode);

    return nullptr;
}

antlrcpp::Any AstBuilder::visitList(DplParser::ListContext* parseNode) {
    AstNode* newNode = new ListNode(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("[] List");

    currentNode->addChild(newNode);
    AstNode* oldNode = currentNode;
    currentNode = newNode;

    if (parseNode->children.size() == 3) parseNode->children[1]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitTable(DplParser::TableContext* parseNode) {
    AstNode* newNode = new TableNode(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("{} Table");

    currentNode->addChild(newNode);
    AstNode* oldNode = currentNode;
    currentNode = newNode;

    std::vector<tree::ParseTree*> children = parseNode->children;

    for (size_t i = 1; i < children.size(); i = i + 2) {
        children[i]->accept(this);
    }

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitColumn(DplParser::ColumnContext* parseNode) {
    AstNode* newNode = new ColumnNode(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText(parseNode->children[0]->getText() + ":");

    currentNode->addChild(newNode);
    AstNode* oldNode = currentNode;
    currentNode = newNode;

    parseNode->children[2]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitTerm(DplParser::TermContext* parseNode) {
    if (parseNode->children.size() == 1) return parseNode->children[0]->accept(this);

    AstNode* newNode = new ParNode(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("() Parenthesis");

    currentNode->addChild(newNode);
    AstNode* oldNode = currentNode;
    currentNode = newNode;

    parseNode->children[1]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitSubscript(DplParser::SubscriptContext* parseNode) {
    if (parseNode->children.size() == 1) return parseNode->children[0]->accept(this);

    AstNode* oldNode = currentNode;

    parseNode->children[1]->accept(this);

    parseNode->children[0]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitIndex(DplParser::IndexContext* parseNode) {
    AstNode* newNode = new IndexNode(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("[] Indexing");

    currentNode->addChild(newNode);
    currentNode = newNode;

    parseNode->children[1]->accept(this);

    return nullptr;
}

antlrcpp::Any AstBuilder::visitHeaderindex(DplParser::HeaderindexContext* parseNode) {
    AstNode* newNode = new HeaderIndexNode(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("[$] Header Indexing");

    currentNode->addChild(newNode);
    currentNode = newNode;

    parseNode->children[2]->accept(this);

    return nullptr;
}

antlrcpp::Any AstBuilder::visitFiltering(DplParser::FilteringContext* parseNode) {
    AstNode* newNode = new FilterNode(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("[] Filter");

    currentNode->addChild(newNode);
    currentNode = newNode;

    parseNode->children[1]->accept(this);

    return nullptr;
}

antlrcpp::Any AstBuilder::visitUnaryexpr(DplParser::UnaryexprContext* parseNode) {
    AstNode* newNode = new UnaryExprNode(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText(parseNode->children[0]->getText());

    currentNode->addChild(newNode);
    AstNode* oldNode = currentNode;
    currentNode = newNode;

    parseNode->children[1]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitProccall(DplParser::ProccallContext* parseNode) {
    ProcCallNode* newNode = new ProcCallNode(currentNode);
    newNode->setRule(parseNode->getRuleIndex());

    AstNode* astNewNode = static_cast<AstNode*>(newNode);
    currentNode->addChild(astNewNode);
    currentNode = astNewNode;

    if (parseNode->children.size() == 2) {
        newNode->stopVisitingParams();
        return nullptr;
    }

    parseNode->children[1]->accept(this);
    newNode->stopVisitingParams();

    return nullptr;
}

antlrcpp::Any AstBuilder::visitArgs(DplParser::ArgsContext* parseNode) {
    if (parseNode->children.size() == 1) return parseNode->children[0]->accept(this);

    for (size_t i = 0; i < parseNode->children.size(); i = i + 2) {
        parseNode->children[i]->accept(this);
    }

    return nullptr;
}

antlrcpp::Any AstBuilder::visitParams(DplParser::ParamsContext* parseNode) {
    if (parseNode->children.size() == 1) return parseNode->children[0]->accept(this);

    for (size_t i = 0; i < parseNode->children.size(); i = i + 2) {
        parseNode->children[i]->accept(this);
    }

    return nullptr;
}

AstNode* AstBuilder::getRoot() { return root; }
