#ifndef ASTBUILDER_HPP
#define ASTBUILDER_HPP

#include <DplParserBaseVisitor.h>
#include <AllNodeIncludes.hpp>

using namespace antlr4;
using namespace dplgrammar;


class AstBuilder : public DplParserBaseVisitor {
private:
    DplParser* parser; // Add a parser member
    DplLexer* lexer; // Add a lexer member
    AstNode* root;
    AstNode* currentNode;
public:
    AstBuilder(DplParser* parser, DplLexer* lexer) : parser(parser), lexer(lexer),  root(nullptr), currentNode(nullptr) {}
    
    virtual antlrcpp::Any visitProg(DplParser::ProgContext *parseNode) override {
        AstNode* newNode = new ProgNode();
        newNode->setRule(parseNode->getRuleIndex());
        newNode->setText(parser->getRuleNames()[newNode->getRule()]);

        root = newNode;
        currentNode = newNode;

        std::vector<tree::ParseTree*> children = parseNode->children;

        for (size_t i = 0; i < children.size(); i++) {
            if (children[i]->getText() != "\n")  children[i]->accept(this);
        }
        
        return nullptr;
    }

    virtual antlrcpp::Any visitBlock(DplParser::BlockContext *parseNode) override {
        parseNode->children[2]->accept(this);

        return nullptr;
    }

    virtual antlrcpp::Any visitStms(DplParser::StmsContext *parseNode) override {
        for (size_t i = 0; i < parseNode->children.size(); i++) {
            if (parseNode->children[i]->getText() != "\n") parseNode->children[i]->accept(this);
        }
        return nullptr;
    }

    virtual antlrcpp::Any visitProcdec(DplParser::ProcdecContext *parseNode) override {
        std::string name = parseNode->children[1]->getText();
        
        ProcDecNode* newNode = new ProcDecNode(currentNode);
        newNode->setRule(parseNode->getRuleIndex());
        newNode->setText("def " + name);
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
    
    virtual antlrcpp::Any visitAssignstm(DplParser::AssignstmContext *parseNode) override {
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
    virtual antlrcpp::Any visitReturnstm(DplParser::ReturnstmContext *parseNode) override {
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
    virtual antlrcpp::Any visitIfstm(DplParser::IfstmContext *parseNode) override {
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

    virtual antlrcpp::Any visitElsestm(DplParser::ElsestmContext *parseNode) override {
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
    virtual antlrcpp::Any visitWhilestm(DplParser::WhilestmContext *parseNode) override {
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
    virtual antlrcpp::Any visitExpr(DplParser::ExprContext *parseNode) override {
        if (parseNode->children.size() == 1) return parseNode->children[0]->accept(this);
        AstNode* newNode = new ExprNode(currentNode);
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

    virtual antlrcpp::Any visitNotexpr(DplParser::NotexprContext *parseNode) {
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

    virtual antlrcpp::Any visitCompexpr(DplParser::CompexprContext *parseNode) override { 
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

    virtual antlrcpp::Any visitArthexpr(DplParser::ArthexprContext *parseNode) override {
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
    virtual antlrcpp::Any visitTerminal(tree::TerminalNode *node) override {
        AstNode* newNode = new LeafNode(currentNode);
        newNode->setRule(node->getSymbol()->getType());
        newNode->setText(node->getText());

        currentNode->addChild(newNode);

        return nullptr;
    }

    virtual antlrcpp::Any visitList(DplParser::ListContext *parseNode) override {
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

    virtual antlrcpp::Any visitTable(DplParser::TableContext *parseNode) override {
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

    virtual antlrcpp::Any visitColumn(DplParser::ColumnContext *parseNode) override {
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

    virtual antlrcpp::Any visitTerm(DplParser::TermContext *parseNode) override {
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

    virtual antlrcpp::Any visitSubscript(DplParser::SubscriptContext *parseNode) override {
        if (parseNode->children.size() == 1) return parseNode->children[0]->accept(this);

        AstNode* newNode = new SubscriptNode(currentNode);
        newNode->setRule(parseNode->getRuleIndex());
        newNode->setText("Subscript");

        currentNode->addChild(newNode);
        AstNode* oldNode = currentNode;
        currentNode = newNode;

        parseNode->children[0]->accept(this);

        parseNode->children[1]->accept(this);

        currentNode = oldNode;

        return nullptr;
    }

    virtual antlrcpp::Any visitIndexing(DplParser::IndexingContext *parseNode) override { 
        AstNode* newNode = new IndexNode(currentNode);
        newNode->setRule(parseNode->getRuleIndex());
        newNode->setText("[] Indexing");

        currentNode->addChild(newNode);
        AstNode* oldNode = currentNode;
        currentNode = newNode;

        parseNode->children[1]->accept(this);

        currentNode = oldNode;

        return nullptr;
    }

    virtual antlrcpp::Any visitFiltering(DplParser::FilteringContext *parseNode) override {
        AstNode* newNode = new FilterNode(currentNode);
        newNode->setRule(parseNode->getRuleIndex());
        newNode->setText("[] Filter");

        currentNode->addChild(newNode);
        AstNode* oldNode = currentNode;
        currentNode = newNode;

        parseNode->children[1]->accept(this);

        currentNode = oldNode;

        return nullptr;
    }


    virtual antlrcpp::Any visitUnaryexpr(DplParser::UnaryexprContext *parseNode) override {
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

    virtual antlrcpp::Any visitProccall(DplParser::ProccallContext *parseNode) override {
        AstNode* newNode = new ProcCallNode(currentNode);
        newNode->setRule(parseNode->getRuleIndex());
        newNode->setText("() Proccall");

        currentNode->addChild(newNode);

        if (parseNode->children.size() == 2) return nullptr;

        AstNode* oldNode = currentNode;
        currentNode = newNode;

        parseNode->children[1]->accept(this);

        currentNode = oldNode;

        return nullptr;
    }

    virtual antlrcpp::Any visitArgs(DplParser::ArgsContext *parseNode) override {
        if (parseNode->children.size() == 1) return parseNode->children[0]->accept(this);

        for (size_t i = 0; i < parseNode->children.size(); i = i + 2) {
            parseNode->children[i]->accept(this);
        }

        return nullptr;
    }

    AstNode* getRoot() {
        return root;    
    }
};

#endif