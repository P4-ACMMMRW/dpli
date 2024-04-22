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
    parseNode->children[2]->accept(this);

    return nullptr;
}

antlrcpp::Any AstBuilder::visitStms(DplParser::StmsContext* parseNode) {
    for (size_t i = 0; i < parseNode->children.size(); i++) {
        if (parseNode->children[i]->getText() != "\n") {
            parseNode->children[i]->accept(this);
        }
    }
    return nullptr;
}

antlrcpp::Any AstBuilder::visitProcdec(DplParser::ProcdecContext* parseNode) {
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


antlrcpp::Any AstBuilder::visitJuncexpr(DplParser::JuncexprContext* parseNode) {
    size_t childAmount = parseNode->children.size();
    if (childAmount == 1) {
        return parseNode->children[0]->accept(this);
    }

    for (int i = childAmount - 1; i > 0; i = i - 2) {
            
        std::shared_ptr<AstNode> newNode = nullptr;

        int operatorType = dynamic_cast<antlr4::tree::TerminalNode*>(parseNode->children[i-1])->getSymbol()->getType();

        switch (operatorType) {
            case DplLexer::And:
                newNode = std::make_shared<AndExprNode>(currentNode);
                break;
            case DplLexer::Or:
                newNode = std::make_shared<OrExprNode>(currentNode);
                break;
            default:
                throw std::runtime_error("Junc expr was not valid operator");
        }
        
        newNode->setRule(parseNode->getRuleIndex());
        newNode->setText(parseNode->op->getText());

        currentNode->addChild(newNode);
        std::shared_ptr<AstNode> oldNode = currentNode;
        currentNode = newNode;

        //rightNode 
        parseNode->children[i]->accept(this);

        // if last iteration, add left node
        if (i == 2) parseNode->children[0]->accept(this);
    }

    currentNode = oldNode;
    
    return nullptr;
}

// Expressions  The expressions isn't correctly sequenced
antlrcpp::Any AstBuilder::visitJuncexpr(DplParser::JuncexprContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }

    //size_t childAmount = parseNode->children.size();

    std::shared_ptr<AstNode> newNode = nullptr;

    switch (parseNode->op->getType()) {
        case DplLexer::And:
            newNode = std::make_shared<AndExprNode>(currentNode);
            break;
        case DplLexer::Or:
            newNode = std::make_shared<OrExprNode>(currentNode);
            break;
        default:
            throw std::runtime_error("Junc expr was not valid operator");
    }

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

    std::shared_ptr<AstNode> oldNode = currentNode;

    size_t notAmount = parseNode->children.size() - 1;

    for (int i = 0; i < notAmount; i++) {

        std::shared_ptr<AstNode> newNode = std::make_shared<NotNode>(currentNode);

        newNode->setRule(parseNode->getRuleIndex());
        newNode->setText(parseNode->op->getText());

        currentNode->addChild(newNode);
        currentNode = newNode;
    }

    parseNode->children[notAmount]->accept(this);

    currentNode = oldNode;
    

    return nullptr;
}

antlrcpp::Any AstBuilder::visitEqulexpr(DplParser::EqulexprContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }

    size_t childAmount = parseNode->children.size();

    for (int i = 0; i < childAmount; i = i + 2) {

        std::shared_ptr<AstNode> newNode = nullptr;

        switch (parseNode->op->getType()) {
            case DplLexer::Equal:
                newNode = std::make_shared<EqualExprNode>(currentNode);
                break;
            case DplLexer::NotEqual:
                newNode = std::make_shared<NotEqualExprNode>(currentNode);
                break;
            default:
                throw std::runtime_error("Junc expr was not valid operator");
        }

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
    }

    return nullptr;
}

antlrcpp::Any AstBuilder::visitCompexpr(DplParser::CompexprContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }

    std::shared_ptr<AstNode> newNode = nullptr;

    switch (parseNode->op->getType()) {
        case DplLexer::Equal:
            newNode = std::make_shared<EqualExprNode>(currentNode);
            break;
        case DplLexer::NotEqual:
            newNode = std::make_shared<NotEqualExprNode>(currentNode);
            break;
        case DplLexer::Greater:
            newNode = std::make_shared<GreaterExprNode>(currentNode);
            break;
        case DplLexer::GreaterEqual:
            newNode = std::make_shared<GreaterEqualExprNode>(currentNode);
            break;
        case DplLexer::Less:
            newNode = std::make_shared<LessExprNode>(currentNode);
            break;
        case DplLexer::LessEqual:
            newNode = std::make_shared<LessEqualExprNode>(currentNode);
            break;
        default:
            throw std::runtime_error("Compexpr was not valid operator");
    }

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

    std::shared_ptr<AstNode> newNode = nullptr;

    switch (parseNode->op->getType()) {
        case DplLexer::Exponent:
            newNode = std::make_shared<ExpoExprNode>(currentNode);
            break;
        case DplLexer::Star:
            newNode = std::make_shared<MultExprNode>(currentNode);
            break;
        case DplLexer::Slash:
            newNode = std::make_shared<DivExprNode>(currentNode);
            break;
        case DplLexer::Mod:
            newNode = std::make_shared<ModExprNode>(currentNode);
            break;
        case DplLexer::Plus:
            newNode = std::make_shared<PlusExprNode>(currentNode);
            break;
        case DplLexer::Minus:
            newNode = std::make_shared<MinusExprNode>(currentNode);
            break;
        default:
            throw std::runtime_error("Arthexpr was not valid operator");
    }

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
    std::shared_ptr<LeafNode> newNode = std::make_shared<LeafNode>(currentNode);
    newNode->setRule(node->getSymbol()->getType());
    newNode->setText(node->getText());

    switch (node->getSymbol()->getType()) {
        case DplLexer::Identifier:
            newNode->setType(LeafNode::type::IDENTIFIER);
            break;
        case DplLexer::Integer:
            newNode->setType(LeafNode::type::INTEGER);
            break;
        case DplLexer::Float:
            newNode->setType(LeafNode::type::FLOAT);
            break;
        case DplLexer::String:
            newNode->setType(LeafNode::type::STRING);
            break;
        case DplLexer::Bool:
            newNode->setType(LeafNode::type::BOOLEAN);
            break;
        case DplLexer::None:
            newNode->setType(LeafNode::type::NONE);
            break;
        default:
            newNode->setType(LeafNode::type::UNDEFINED);
            break;
    }

    currentNode->addChild(std::static_pointer_cast<AstNode>(newNode));

    return nullptr;
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

    return nullptr;
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

    return nullptr;
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

    return nullptr;
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

    return nullptr;
}

antlrcpp::Any AstBuilder::visitSubscript(DplParser::SubscriptContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }

    std::shared_ptr<AstNode> oldNode = currentNode;

    parseNode->children[1]->accept(this);

    parseNode->children[0]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitIndex(DplParser::IndexContext* parseNode) {
    std::shared_ptr<AstNode> newNode = std::make_shared<IndexNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("[] Indexing");

    currentNode->addChild(newNode);
    currentNode = newNode;

    parseNode->children[1]->accept(this);

    return nullptr;
}

antlrcpp::Any AstBuilder::visitHeaderindex(DplParser::HeaderindexContext* parseNode) {
    std::shared_ptr<AstNode> newNode = std::make_shared<HeaderIndexNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("[$] Header Indexing");

    currentNode->addChild(newNode);
    currentNode = newNode;

    parseNode->children[2]->accept(this);

    return nullptr;
}

antlrcpp::Any AstBuilder::visitFiltering(DplParser::FilteringContext* parseNode) {
    std::shared_ptr<AstNode> newNode = std::make_shared<FilterNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("[] Filter");

    currentNode->addChild(newNode);
    currentNode = newNode;

    parseNode->children[1]->accept(this);

    return nullptr;
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

    return nullptr;
}

antlrcpp::Any AstBuilder::visitProccall(DplParser::ProccallContext* parseNode) {
    std::shared_ptr<ProcCallNode> newNode = std::make_shared<ProcCallNode>(currentNode);
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText("() proccall");

    std::shared_ptr<AstNode> astNewNode = std::static_pointer_cast<AstNode>(newNode);
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
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }

    for (size_t i = 0; i < parseNode->children.size(); i = i + 2) {
        parseNode->children[i]->accept(this);
    }

    return nullptr;
}

antlrcpp::Any AstBuilder::visitParams(DplParser::ParamsContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }

    for (size_t i = 0; i < parseNode->children.size(); i = i + 2) {
        parseNode->children[i]->accept(this);
    }

    return nullptr;
}

std::shared_ptr<AstNode> AstBuilder::getRoot() { return root; }
