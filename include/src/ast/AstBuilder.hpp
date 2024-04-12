#ifndef ASTBUILDER_HPP
#define ASTBUILDER_HPP

#include <DplParserBaseVisitor.h>
#include <DplLexer.h>
#include <DplParser.h>
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
    
    virtual antlrcpp::Any visitProg(DplParser::ProgContext *parseNode) override;
    virtual antlrcpp::Any visitBlock(DplParser::BlockContext *parseNode) override;

    // Declarations
    virtual antlrcpp::Any visitStms(DplParser::StmsContext *parseNode) override;
    virtual antlrcpp::Any visitProcdec(DplParser::ProcdecContext *parseNode) override;
    virtual antlrcpp::Any visitAssignstm(DplParser::AssignstmContext *parseNode) override;
    virtual antlrcpp::Any visitReturnstm(DplParser::ReturnstmContext *parseNode) override;

    // IF-ELSE
    virtual antlrcpp::Any visitIfstm(DplParser::IfstmContext *parseNode) override;
    virtual antlrcpp::Any visitElsestm(DplParser::ElsestmContext *parseNode) override;

    // While
    virtual antlrcpp::Any visitWhilestm(DplParser::WhilestmContext *parseNode) override;

    // Expressions  The expressions isn't correctly sequenced
    virtual antlrcpp::Any visitJuncexpr(DplParser::JuncexprContext *parseNode) override;
    virtual antlrcpp::Any visitNotexpr(DplParser::NotexprContext *parseNode) override;
    virtual antlrcpp::Any visitCompexpr(DplParser::CompexprContext *parseNode) override;
    virtual antlrcpp::Any visitArthexpr(DplParser::ArthexprContext *parseNode) override;

    // Terms
    virtual antlrcpp::Any visitTerminal(tree::TerminalNode *node) override;
    virtual antlrcpp::Any visitList(DplParser::ListContext *parseNode) override;
    virtual antlrcpp::Any visitTable(DplParser::TableContext *parseNode) override;
    virtual antlrcpp::Any visitColumn(DplParser::ColumnContext *parseNode) override;
    virtual antlrcpp::Any visitTerm(DplParser::TermContext *parseNode) override;
    virtual antlrcpp::Any visitSubscript(DplParser::SubscriptContext *parseNode) override;
    virtual antlrcpp::Any visitIndex(DplParser::IndexContext *parseNode) override;
    virtual antlrcpp::Any visitHeaderindex(DplParser::HeaderindexContext *parseNode) override;
    virtual antlrcpp::Any visitFiltering(DplParser::FilteringContext *parseNode) override;

    virtual antlrcpp::Any visitUnaryexpr(DplParser::UnaryexprContext *parseNode) override;
    virtual antlrcpp::Any visitProccall(DplParser::ProccallContext *parseNode) override;
    virtual antlrcpp::Any visitArgs(DplParser::ArgsContext *parseNode) override;
    virtual antlrcpp::Any visitParams(DplParser::ParamsContext *parseNode) override;

    AstNode* getRoot();
};

#endif