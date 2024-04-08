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

        return visitChildren(parseNode);
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

    // Expressions  The expressions isn't correctly sequenced
    virtual antlrcpp::Any visitExpr(DplParser::ExprContext *parseNode) override {
        if      (parseNode->children.size() == 1) return parseNode->children[0]->accept(this);
        else if (parseNode->children.size() == 2) return notNode(parseNode);
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

    virtual antlrcpp::Any visitCompexpr(DplParser::CompexprContext *parseNode) override { 
        if      (parseNode->children.size() == 1) return parseNode->children[0]->accept(this);
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

    virtual antlrcpp::Any notNode(DplParser::ExprContext *parseNode) {
        AstNode* newNode = new NotNode(currentNode);
        newNode->setRule(parseNode->getRuleIndex());
        newNode->setText("not");
        
        currentNode->addChild(newNode);
        AstNode* oldNode = currentNode;
        currentNode = newNode;

        parseNode->children[1]->accept(this);

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

    // Not done
    virtual antlrcpp::Any visitTerm(DplParser::TermContext *parseNode) override {
        if (parseNode->children.size() == 1) return parseNode->children[0]->accept(this);

        AstNode* newNode = new ParNode(currentNode);
        newNode->setRule(parseNode->getRuleIndex());
        newNode->setText("() Parenthesis");

        currentNode->addChild(newNode);
        AstNode* oldNode = currentNode;
        currentNode = newNode;

        // Left Node
        parseNode->children[0]->accept(this);
        
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

//    virtual antlrcpp::Any visitLoopstm(DplParser::LoopstmContext *parseNode) override {
//        AstNode* newNode = new AstNode(currentNode);
//        newNode->rule = parseNode->getRuleIndex();
//        newNode->text = parseNode->children[0]->getText();
//
//        currentNode->children.push_back(newNode);
//        AstNode* oldNode = currentNode;
//        currentNode = newNode;
//
//        AstNode* condNode = getTerminalLeafNode(parseNode->children[1]);
//        if (condNode != nullptr)  currentNode->children.push_back(condNode);
//
//        for (size_t i = 4; i < parseNode->children.size() - 1; i++) {
//            AstNode* childNode = getTerminalLeafNode(parseNode->children[i]);
//            if (childNode != nullptr) currentNode->children.push_back(childNode);
//        }
//
//        visitChildren(parseNode);
//
//        currentNode = oldNode;
//
//        return nullptr;
//    }
//
//    virtual antlrcpp::Any visitIfstm(DplParser::IfstmContext *parseNode) override {
//        AstNode* newNode = new AstNode(currentNode);
//        newNode->rule = parseNode->getRuleIndex();
//        newNode->text = parseNode->children[0]->getText();
//
//        currentNode->children.push_back(newNode);
//        AstNode* oldNode = currentNode;
//        currentNode = newNode;
//
//        AstNode* condNode = getTerminalLeafNode(parseNode->children[1]);
//        if (condNode != nullptr)  currentNode->children.push_back(condNode);
//
//        visitChildren(parseNode);
//
//        currentNode = oldNode;
//
//        return nullptr;
//    }
//
//    virtual antlrcpp::Any visitElsestm(DplParser::ElsestmContext *parseNode) override {
//        AstNode* newNode = new AstNode(currentNode);
//        newNode->rule = parseNode->getRuleIndex();
//        newNode->text = parseNode->children[0]->getText();
//
//        currentNode->children.push_back(newNode);
//        AstNode* oldNode = currentNode;
//        currentNode = newNode;
//
//        visitChildren(parseNode);
//
//        currentNode = oldNode;
//
//        return nullptr;
//    }
//
//    virtual antlrcpp::Any visitExpr(DplParser::ExprContext *parseNode) override { // Problem is here
//        AstNode* oldNode = currentNode;
//        bool isArthExpr = (parseNode->arthexpr() != nullptr);
//        bool isBoolExpr = (parseNode->boolexpr() != nullptr);
//
//        if (!isArthExpr  && !isBoolExpr) return visitChildren(parseNode);
//    
//        AstNode *newNode = new AstNode(currentNode);
//
//        tree::ParseTree *childParseTree = (isArthExpr) ? parseNode->children[1] : parseNode->children[1]->children[0];
//        ParserRuleContext *childParseNode = dynamic_cast<ParserRuleContext*>(childParseTree); 
//
//        newNode->rule = childParseNode->getRuleIndex(); 
//        newNode->text = childParseNode->children[0]->getText();
//        currentNode->children.push_back(newNode);
//        currentNode = newNode;
//
//        if (newNode->rule != DplParser::RuleJunctionopr) {
//            AstNode* leftNode = getTerminalLeafNode(parseNode->children[0]);  
//            AstNode* rightNode;    
//
//            if (isBoolExpr) rightNode = getTerminalLeafNode(childParseNode->children[1]->children[0]);     
//            else            rightNode = getTerminalLeafNode(childParseNode->children[1]);      
//            
//            if (leftNode != nullptr) currentNode->children.push_back(leftNode);
//            if (rightNode != nullptr) currentNode->children.push_back(rightNode);
//        }
//        visitChildren(parseNode);
//
//        currentNode = oldNode;
//
//        return nullptr;
//    }
//
//
//    virtual antlrcpp::Any visitFlowstm(DplParser::FlowstmContext *parseNode) override {
//        AstNode* newNode = new AstNode(currentNode);
//        newNode->rule = parseNode->getRuleIndex();
//        newNode->text = parseNode->children[0]->getText();
//    
//        currentNode->children.push_back(newNode);
//        AstNode* oldNode = currentNode;
//        currentNode = newNode;
//
//        if (parseNode->children.size() > 1) {
//            AstNode* childNode = getTerminalLeafNode(parseNode->children[1]);
//            if (childNode != nullptr) currentNode->children.push_back(childNode);
//        }
//    
//        visitChildren(parseNode);
//    
//        currentNode = oldNode;
//    
//        return nullptr;
//    }
//    
//    virtual antlrcpp::Any visitProcdec(DplParser::ProcdecContext *parseNode) override {
//        AstNode* newNode = new AstNode(currentNode);
//        newNode->rule = parseNode->getRuleIndex();
//        newNode->text = parseNode->children[1]->getText();
//    
//        currentNode->children.push_back(newNode);
//        AstNode* oldNode = currentNode;
//        currentNode = newNode;
//    
//        antlr4::ParserRuleContext *childParseNode = dynamic_cast<antlr4::ParserRuleContext*>(parseNode->children[3]); 
//    
//        if (childParseNode->getRuleIndex() == DplParser::RuleParams) {
//            for (size_t i = 0; i < childParseNode->children.size(); i = i + 2) {
//                AstNode* childNode = getTerminalLeafNode(childParseNode->children[i]);
//                if (childNode != nullptr) currentNode->children.push_back(childNode);
//            }
//        }
//    
//        visitChildren(parseNode);
//    
//        currentNode = oldNode;
//    
//        return nullptr;
//    }
//    
//    virtual antlrcpp::Any visitProccall(DplParser::ProccallContext *parseNode) override {
//        AstNode* newNode = new AstNode(currentNode);
//        newNode->rule = parseNode->getRuleIndex();
//        newNode->text = parseNode->children[0]->getText();
//        
//    
//        currentNode->children.push_back(newNode);
//        AstNode* oldNode = currentNode;
//        currentNode = newNode;
//    
//        antlr4::ParserRuleContext *childParseNode = dynamic_cast<antlr4::ParserRuleContext*>(parseNode->children[2]); 
//        for (size_t i = 0; i < childParseNode->children.size(); i = i + 2) {
//            AstNode* childNode = getTerminalLeafNode(childParseNode->children[i]);
//            if (childNode != nullptr) currentNode->children.push_back(childNode);
//        }
//    
//        visitChildren(parseNode);
//    
//        currentNode = oldNode;
//    
//        return nullptr;
//    }
//    
//    virtual antlrcpp::Any visitList(DplParser::ListContext *parseNode) override {
//        AstNode* newNode = new AstNode(currentNode);
//        newNode->rule = parseNode->getRuleIndex();
//        newNode->text = "[]";
//        
//        currentNode->children.push_back(newNode);
//        AstNode* oldNode = currentNode;
//        currentNode = newNode;
//    
//        antlr4::ParserRuleContext *childParseNode = dynamic_cast<antlr4::ParserRuleContext*>(parseNode->children[1]); 
//        for (size_t i = 0; i < childParseNode->children.size(); i = i + 2) {
//            AstNode* childNode = getTerminalLeafNode(childParseNode->children[i]);
//            if (childNode != nullptr) currentNode->children.push_back(childNode);
//        }
//    
//        visitChildren(parseNode);
//    
//        currentNode = oldNode;
//    
//        return nullptr;
//    }
//    
//    virtual antlrcpp::Any visitListcall(DplParser::ListcallContext *parseNode) {
//        AstNode* newNode = new AstNode(currentNode);
//        newNode->rule = parseNode->getRuleIndex();
//        newNode->text = parseNode->children[0]->getText();
//    
//        currentNode->children.push_back(newNode);
//        AstNode* oldNode = currentNode;
//        currentNode = newNode;
//    
//        for (size_t i = 2; i < parseNode->children.size(); i = i + 3) { 
//            AstNode* childNode = getTerminalLeafNode(parseNode->children[i]);
//            if (childNode != nullptr) currentNode->children.push_back(childNode);
//        }
//    
//        visitChildren(parseNode);
//    
//        currentNode = oldNode;
//    
//        return nullptr;
//    }
//    
//    virtual antlrcpp::Any visitTable(DplParser::TableContext *parseNode) {
//        AstNode* newNode = new AstNode(currentNode);
//        newNode->rule = parseNode->getRuleIndex();
//        newNode->text = "{}";
//        
//        currentNode->children.push_back(newNode);
//        AstNode* oldNode = currentNode;
//        currentNode = newNode;
//        
//        for (size_t i = 1; i < parseNode->children.size(); i = i + 4) {
//            AstNode* childNode = getTerminalLeafNode(parseNode->children[i]);
//            if (childNode != nullptr) currentNode->children.push_back(childNode);
//            currentNode = childNode;
//            parseNode->children[i+2]->accept(this);
//            currentNode = newNode;
//        }
//    
//        currentNode = oldNode;
//    
//        return nullptr;
//    }
//    
//    virtual antlrcpp::Any visitTablecall(DplParser::TablecallContext *parseNode) { // problem is here
//        AstNode* oldNode = currentNode;
//        std::vector<tree::ParseTree*> nodeChildren = parseNode->children;
//        if (nodeChildren[0]->children.size() <= 1) {
//            AstNode* newNode = new AstNode(currentNode);
//            newNode->text = nodeChildren[0]->getText();
//            newNode->rule = parseNode->getRuleIndex();
//    
//            currentNode->children.push_back(newNode);
//            currentNode = newNode;
//        }
//    
//        AstNode* rowNode     = getTerminalLeafNode(nodeChildren[2]);
//        AstNode* coloumnNode = (nodeChildren.size() > 5) ? getTerminalLeafNode(nodeChildren[5]) : nullptr;
//        if (rowNode != nullptr)     currentNode->children.push_back(rowNode);
//        if (coloumnNode != nullptr) currentNode->children.push_back(coloumnNode);
//    
//        visitChildren(parseNode);
//    
//        currentNode = oldNode;
//    
//        return nullptr;
//    }
//    
//    virtual antlrcpp::Any visitUnaryexpr(DplParser::UnaryexprContext *parseNode) {
//        AstNode* newNode = new AstNode(currentNode);
//        newNode->rule = parseNode->getRuleIndex();
//        newNode->text = parseNode->children[0]->getText();
//    
//        currentNode->children.push_back(newNode);
//        AstNode* oldNode = currentNode;
//        currentNode = newNode;
//    
//        visitChildren(parseNode);
//    
//        currentNode = oldNode;
//    
//        return nullptr;
//    }
//    
//    virtual antlrcpp::Any visitReplacestm(DplParser::ReplacestmContext *parseNode) {
//        AstNode* newNode = new AstNode(currentNode);
//        newNode->rule = parseNode->getRuleIndex();
//        newNode->text = parseNode->children[0]->getText();
//    
//        currentNode->children.push_back(newNode);
//        AstNode* oldNode = currentNode;
//        currentNode = newNode;
//    
//        AstNode* leftNode = getTerminalLeafNode(parseNode->children[1]);
//        AstNode* rightNode = getTerminalLeafNode(parseNode->children[3]);
//    
//        if (leftNode != nullptr)  currentNode->children.push_back(leftNode);
//        if (rightNode != nullptr) currentNode->children.push_back(rightNode);
//    
//        visitChildren(parseNode);
//    
//        currentNode = oldNode;
//    
//        return nullptr;
//    }
//
//    AstNode* getTerminalLeafNode(tree::ParseTree* childParseNode) {
//        while (childParseNode->children.size() == 1) {
//            childParseNode = childParseNode->children[0];
//        }
//        if (childParseNode->children.size() > 1) return nullptr;
//
//        tree::TerminalNode* parseLeafNode = dynamic_cast<antlr4::tree::TerminalNode*>(childParseNode);
//
//        AstNode* leafNode = new AstNode();
//        leafNode->rule = parseLeafNode->getSymbol()->getType();
//        leafNode->text = parseLeafNode->getText();
//        return leafNode;
//    }

    tree::ParseTree* getTerminalNode(tree::ParseTree* parseNode) {
        tree::ParseTree* newParseNode = parseNode;
        while (newParseNode->children.size() == 1) {
            newParseNode = newParseNode->children[0];
        }
        if (newParseNode->children.size() > 1) return parseNode;
        
        return newParseNode;
    }

    AstNode* getRoot() {
        return root;
    }
};

#endif