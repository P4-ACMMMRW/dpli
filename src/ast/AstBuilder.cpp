#include "AstBuilder.hpp"

using namespace dplsrc;

antlrcpp::Any AstBuilder::visitProg(DplParser::ProgContext* parseNode) {
    std::shared_ptr<AstNode> newNode = std::make_shared<ProgNode>();
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText(parser->getRuleNames()[newNode->getRule()]);

    root = newNode;
    currentNode = newNode;

    std::vector<tree::ParseTree*> children = parseNode->children;

    for (size_t i = 0; i < children.size(); i++) {
        if (children[i]->getText() !=
            "\n") {  // dirty way to not visit newlines (shoud be fixed in lexer instead)
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
    std::shared_ptr<AstNode> oldNode = currentNode;

    std::shared_ptr<ProcDecNode> procDecNewNode = std::make_shared<ProcDecNode>(currentNode);
    std::shared_ptr<AstNode> newNode = std::static_pointer_cast<AstNode>(procDecNewNode);
    initNewNode(parseNode, newNode, "def ()");

    parseNode->children[1]->accept(this);

    size_t blockIndex = 5;  // if no params
    if (parseNode->children.size() - 1 > blockIndex) {
        parseNode->children[3]->accept(this);
        blockIndex = 6;  // if params
    }
    procDecNewNode->stopVisitingParams();
    parseNode->children[blockIndex]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitProccall(DplParser::ProccallContext* parseNode) {
    std::shared_ptr<ProcCallNode> procCallNewNode = std::make_shared<ProcCallNode>(currentNode);
    std::shared_ptr<AstNode> newNode = std::static_pointer_cast<AstNode>(procCallNewNode);
    initNewNode(parseNode, newNode, "() proccall");

    if (parseNode->children.size() > 2) {  // not empty params
        parseNode->children[1]->accept(this);
    }
    procCallNewNode->stopVisitingParams();
    currentNode = newNode;

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

antlrcpp::Any AstBuilder::visitIfstm(DplParser::IfstmContext* parseNode) {
    std::shared_ptr<AstNode> oldNode = currentNode;
    binaryNode([this]() { return std::make_shared<IfNode>(currentNode); }, parseNode, 3, 1, false,
               "If");

    // Else
    if (parseNode->children.size() > 4) {
        parseNode->children[4]->accept(this);
    }

    currentNode = oldNode;

    return nullptr;
}

// Terms
antlrcpp::Any AstBuilder::visitTerminal(tree::TerminalNode* node) {
    size_t lexerRule = node->getSymbol()->getType();
    if (lexerRule == DplLexer::Break || lexerRule == DplLexer::Continue) {
        return flowStm(node);
    }

    std::shared_ptr<LeafNode> newNode = std::make_shared<LeafNode>(currentNode);
    newNode->setRule(lexerRule);
    newNode->setText(node->getText());

    bool isIdentifier = node->getSymbol()->getType() == DplLexer::Identifier;
    newNode->setIsIdentifier(isIdentifier);

    if (!isIdentifier) {
        switch (node->getSymbol()->getType()) {
            case DplLexer::Integer:
                newNode->setVal(0);
                break;
            case DplLexer::Float:
                newNode->setVal(0.0);
                break;
            case DplLexer::String:
                newNode->setVal("");
                break;
            case DplLexer::Bool:
                newNode->setVal(false);
                break;
            default:
                newNode->setVal(nullptr);
                break;
        }
    }

    currentNode->addChild(std::static_pointer_cast<AstNode>(newNode));

    return nullptr;
}

antlrcpp::Any AstBuilder::visitAssignstm(DplParser::AssignstmContext* parseNode) {
    return binaryNode([this]() { return std::make_shared<AssignNode>(currentNode); }, parseNode, 0,
                      2, true);
}

// Return
antlrcpp::Any AstBuilder::visitReturnstm(DplParser::ReturnstmContext* parseNode) {
    bool hasChild = parseNode->children.size() > 1;
    return unaryNode([this]() { return std::make_shared<ReturnNode>(currentNode); }, parseNode, 1,
                     "Return", hasChild);
}

antlrcpp::Any AstBuilder::visitElsestm(DplParser::ElsestmContext* parseNode) {
    return unaryNode([this]() { return std::make_shared<ElseNode>(currentNode); }, parseNode, 2,
                     "Else");
}

// While
antlrcpp::Any AstBuilder::visitWhilestm(DplParser::WhilestmContext* parseNode) {
    return binaryNode([this]() { return std::make_shared<WhileNode>(currentNode); }, parseNode, 3,
                      1, true);
}

antlrcpp::Any AstBuilder::visitOrexpr(DplParser::OrexprContext* parseNode) {
    return binaryExpr(
        [this]([[maybe_unused]] size_t unused) -> std::shared_ptr<AstNode> {
            return std::make_shared<OrExprNode>(currentNode);
        },
        parseNode);
}

antlrcpp::Any AstBuilder::visitAndexpr(DplParser::AndexprContext* parseNode) {
    return binaryExpr(
        [this]([[maybe_unused]] size_t unused) -> std::shared_ptr<AstNode> {
            return std::make_shared<AndExprNode>(currentNode);
        },
        parseNode);
}

antlrcpp::Any AstBuilder::visitNotexpr(DplParser::NotexprContext* parseNode) {
    return unaryExpr(
        [this]([[maybe_unused]] size_t unused) -> std::shared_ptr<AstNode> {
            return std::make_shared<NotNode>(currentNode);
        },
        parseNode);
}

antlrcpp::Any AstBuilder::visitEqulexpr(DplParser::EqulexprContext* parseNode) {
    return binaryExpr(
        [this](size_t operatorType) -> std::shared_ptr<AstNode> {
            switch (operatorType) {
                case DplLexer::Equal:
                    return std::make_shared<EqualExprNode>(currentNode);
                case DplLexer::NotEqual:
                    return std::make_shared<NotEqualExprNode>(currentNode);
                default:
                    throw AstException("Junc expr was not valid operator");
            }
            return nullptr;
        },
        parseNode);
}

antlrcpp::Any AstBuilder::visitCompexpr(DplParser::CompexprContext* parseNode) {
    return binaryExpr(
        [this](size_t operatorType) -> std::shared_ptr<AstNode> {
            switch (operatorType) {
                case DplLexer::Greater:
                    return std::make_shared<GreaterExprNode>(currentNode);
                case DplLexer::GreaterEqual:
                    return std::make_shared<GreaterEqualExprNode>(currentNode);
                case DplLexer::Less:
                    return std::make_shared<LessExprNode>(currentNode);
                case DplLexer::LessEqual:
                    return std::make_shared<LessEqualExprNode>(currentNode);
                default:
                    throw AstException("Compexpr was not valid operator");
            }
            return nullptr;
        },
        parseNode);
}

antlrcpp::Any AstBuilder::visitPlusexpr(DplParser::PlusexprContext* parseNode) {
    return binaryExpr(
        [this](size_t operatorType) -> std::shared_ptr<AstNode> {
            switch (operatorType) {
                case DplLexer::Plus:
                    return std::make_shared<PlusExprNode>(currentNode);
                case DplLexer::Minus:
                    return std::make_shared<MinusExprNode>(currentNode);
                default:
                    throw AstException("Plusexpr was not valid operator");
            }
            return nullptr;
        },
        parseNode);
}

antlrcpp::Any AstBuilder::visitTablexpr(DplParser::TablexprContext* parseNode) {
    return binaryExpr(
        [this](size_t operatorType) -> std::shared_ptr<AstNode> {
            switch (operatorType) {
                case DplLexer::Union:
                    return std::make_shared<UnionExprNode>(currentNode);
                case DplLexer::Intersection:
                    return std::make_shared<IntersectionExprNode>(currentNode);
                default:
                    throw AstException("Tablexpr was not valid operator");
            }
            return nullptr;
        },
        parseNode);
}

antlrcpp::Any AstBuilder::visitMultexpr(DplParser::MultexprContext* parseNode) {
    return binaryExpr(
        [this](size_t operatorType) -> std::shared_ptr<AstNode> {
            switch (operatorType) {
                case DplLexer::Star:
                    return std::make_shared<MultExprNode>(currentNode);
                case DplLexer::Slash:
                    return std::make_shared<DivExprNode>(currentNode);
                case DplLexer::Mod:
                    return std::make_shared<ModExprNode>(currentNode);
                default:
                    throw AstException("Multexpr was not valid operator");
            }
            return nullptr;
        },
        parseNode);
}

antlrcpp::Any AstBuilder::visitPolaexpr(DplParser::PolaexprContext* parseNode) {
    return unaryExpr(
        [this](size_t operatorType) -> std::shared_ptr<AstNode> {
            switch (operatorType) {
                case DplLexer::Plus:
                    return std::make_shared<PlusNode>(currentNode);
                case DplLexer::Minus:
                    return std::make_shared<MinusNode>(currentNode);
                default:
                    throw AstException("Polaexpr was not valid operator");
            }
            return nullptr;
        },
        parseNode);
}

antlrcpp::Any AstBuilder::visitExpoexpr(DplParser::ExpoexprContext* parseNode) {
    return binaryExpr(
        [this]([[maybe_unused]] size_t unused) {
            return std::make_shared<ExpoExprNode>(currentNode);
        },
        parseNode);
}

antlrcpp::Any AstBuilder::visitList(DplParser::ListContext* parseNode) {
    bool hasChild =
        parseNode->children.size() > 2;  // dirty way to not visit children if empty list
    return unaryNode([this]() { return std::make_shared<ListNode>(currentNode); }, parseNode, 1,
                     "[] List", hasChild);
}

antlrcpp::Any AstBuilder::visitTable(DplParser::TableContext* parseNode) {
    bool hasChild = parseNode->children.size() > 2;
    return unaryNodeList([this]() { return std::make_shared<TableNode>(currentNode); }, parseNode,
                         1, 2, "{} Table", hasChild);
}

antlrcpp::Any AstBuilder::visitColumn(DplParser::ColumnContext* parseNode) {
    return binaryNode([this]() { return std::make_shared<ColumnNode>(currentNode); }, parseNode, 0,
                      2, true, "Column");
}

antlrcpp::Any AstBuilder::visitTerm(DplParser::TermContext* parseNode) {
    if (parseNode->children.size() == 1) {
        return parseNode->children[0]->accept(this);
    }
    return unaryNode(
        [this]() {  // Capture 'this' pointer in the lambda capture list
            return std::make_shared<ParNode>(currentNode);
        },
        parseNode, 1, "() Parenthesis");
}

antlrcpp::Any AstBuilder::visitNumber(DplParser::NumberContext* parseNode) {
    return unaryExpr(
        [this](size_t operatorType) -> std::shared_ptr<AstNode> {
            switch (operatorType) {
                case DplLexer::Plus:
                    return std::make_shared<PlusNode>(currentNode);
                case DplLexer::Minus:
                    return std::make_shared<MinusNode>(currentNode);
                default:
                    throw AstException("Numberexpr was not valid operator");
            }
            return nullptr;
        },
        parseNode);
}

antlrcpp::Any AstBuilder::visitSubscript(DplParser::SubscriptContext* parseNode) {
    size_t childAmount = parseNode->children.size();
    if (childAmount < 2) {
        return parseNode->children[0]->accept(this);
    }

    std::shared_ptr<AstNode> oldNode = currentNode;

    for (size_t i = childAmount - 1; i > 0; i--) {
        parseNode->children[i]->accept(this);
        if (i == 1) {
            parseNode->children[0]->accept(this);
        }
    }

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::visitIndex(DplParser::IndexContext* parseNode) {
    return indexNode([this]() { return std::make_shared<IndexNode>(currentNode); }, parseNode, 1,
                     "[] Index");
}

antlrcpp::Any AstBuilder::visitHeaderindex(DplParser::HeaderindexContext* parseNode) {
    return indexNode([this]() { return std::make_shared<HeaderIndexNode>(currentNode); }, parseNode,
                     2, "[$] Header Indexing");
}

antlrcpp::Any AstBuilder::visitFiltering(DplParser::FilteringContext* parseNode) {
    parseNode->children[1]->accept(this);
    return nullptr;
}

antlrcpp::Any AstBuilder::visitUnaryexpr(DplParser::UnaryexprContext* parseNode) {
    std::string text = parseNode->children[0]->getText();
    return indexNode([this]() { return std::make_shared<FilterNode>(currentNode); }, parseNode, 1,
                     text);
}

std::shared_ptr<AstNode> AstBuilder::getRoot() { return root; }

// util
void AstBuilder::initNewNode(antlr4::ParserRuleContext* parseNode,
                             const std::shared_ptr<AstNode>& newNode, const std::string& text) {
    newNode->setRule(parseNode->getRuleIndex());
    newNode->setText((!text.empty()) ? text : parser->getRuleNames()[newNode->getRule()]);
    currentNode->addChild(newNode);
    currentNode = newNode;
}

antlrcpp::Any AstBuilder::indexNode(const std::function<std::shared_ptr<AstNode>()>& createNode,
                                    antlr4::ParserRuleContext* parseNode, size_t childIndex,
                                    const std::string& text) {
    std::shared_ptr<AstNode> newNode = createNode();
    initNewNode(parseNode, newNode, text);

    parseNode->children[childIndex]->accept(this);

    currentNode = newNode;
    return nullptr;
}

antlrcpp::Any AstBuilder::unaryNode(const std::function<std::shared_ptr<AstNode>()>& createNode,
                                    antlr4::ParserRuleContext* parseNode, size_t childIndex,
                                    const std::string& text, bool hasChild) {
    std::shared_ptr<AstNode> oldNode = currentNode;
    std::shared_ptr<AstNode> newNode = createNode();
    initNewNode(parseNode, newNode, text);

    if (!hasChild) {
        currentNode = oldNode;
        return nullptr;
    }

    parseNode->children[childIndex]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::unaryNodeList(const std::function<std::shared_ptr<AstNode>()>& createNode,
                                        antlr4::ParserRuleContext* parseNode, size_t startIndex,
                                        size_t interval, const std::string& text, bool hasChild) {
    std::shared_ptr<AstNode> oldNode = currentNode;
    std::shared_ptr<AstNode> newNode = createNode();
    initNewNode(parseNode, newNode, text);

    if (!hasChild) {
        currentNode = oldNode;
        return nullptr;
    }

    for (size_t i = startIndex; i < parseNode->children.size(); i = i + interval) {
        parseNode->children[i]->accept(this);
    }

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::binaryNode(const std::function<std::shared_ptr<AstNode>()>& createNode,
                                     antlr4::ParserRuleContext* parseNode, size_t leftIndex,
                                     size_t rightIndex, bool restoreOldCurrent,
                                     const std::string& text) {
    std::shared_ptr<AstNode> oldNode = currentNode;
    std::shared_ptr<AstNode> newNode = createNode();
    initNewNode(parseNode, newNode, text);

    parseNode->children[rightIndex]->accept(this);
    parseNode->children[leftIndex]->accept(this);

    if (restoreOldCurrent) {
        currentNode = oldNode;
    }

    return nullptr;
}

antlrcpp::Any AstBuilder::unaryExpr(
    const std::function<std::shared_ptr<AstNode>(size_t)>& createNode,
    antlr4::ParserRuleContext* parseNode) {
    size_t childAmount = parseNode->children.size();
    if (childAmount == 1) {
        return parseNode->children[0]->accept(this);
    }

    std::shared_ptr<AstNode> oldNode = currentNode;

    for (size_t i = 0; i < childAmount - 1; i++) {
        antlr4::Token* operatorToken = getChildToken(parseNode, i);
        std::shared_ptr<AstNode> newNode = createNode(operatorToken->getType());

        initNewNode(parseNode, newNode, operatorToken->getText());
    }

    parseNode->children[childAmount - 1]->accept(this);

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::binaryExpr(
    const std::function<std::shared_ptr<AstNode>(size_t)>& createNode,
    antlr4::ParserRuleContext* parseNode) {
    size_t childAmount = parseNode->children.size();
    if (childAmount == 1) {
        return parseNode->children[0]->accept(this);
    }

    std::shared_ptr<AstNode> oldNode = currentNode;

    for (size_t i = childAmount - 1; i > 0; i = i - 2) {
        antlr4::Token* operatorToken = getChildToken(parseNode, i - 1);
        std::shared_ptr<AstNode> newNode = createNode(operatorToken->getType());

        initNewNode(parseNode, newNode, operatorToken->getText());

        // rightNode
        parseNode->children[i]->accept(this);

        // if last iteration, add left node
        if (i == 2) {
            parseNode->children[0]->accept(this);
        }
    }

    currentNode = oldNode;

    return nullptr;
}

antlrcpp::Any AstBuilder::flowStm(tree::TerminalNode* node) {
    size_t lexerRule = node->getSymbol()->getType();
    std::shared_ptr<AstNode> newNode;

    if (lexerRule == DplLexer::Break) {
        newNode = std::make_shared<BreakNode>(currentNode);
    } else if (lexerRule == DplLexer::Continue) {
        newNode = std::make_shared<ContinueNode>(currentNode);
    } else {
        throw std::runtime_error("Invalid lexer rule for flowStm in AstBuilder.cpp");
    }
    newNode->setRule(lexerRule);
    newNode->setText(node->getText());

    currentNode->addChild(newNode);  // error here

    return nullptr;
}

antlr4::Token* AstBuilder::getChildToken(antlr4::tree::ParseTree* parseNode, size_t childIndex) {
    antlr4::tree::TerminalNode* terminalNode =
        dynamic_cast<antlr4::tree::TerminalNode*>(parseNode->children[childIndex]);
    if (terminalNode != nullptr) {
        return terminalNode->getSymbol();
    }
    throw AstException("Child node is not a TerminalNode");
}
