#ifndef ASTBUILDER_HPP
#define ASTBUILDER_HPP

#include <DplLexer.h>
#include <DplParser.h>
#include <DplParserBaseVisitor.h>

#include <AllNodeIncludes.hpp>

using namespace antlr4;
using namespace dplgrammar;

class AstBuilder : public DplParserBaseVisitor {
   private:
    DplParser *parser;  // Add a parser member
    DplLexer *lexer;    // Add a lexer member
    AstNode *root;
    AstNode *currentNode;

   public:
    AstBuilder(DplParser *parser, DplLexer *lexer)
        : parser(parser), lexer(lexer), root(nullptr), currentNode(nullptr) {}

    antlrcpp::Any visitProg(DplParser::ProgContext *parseNode) override;
    antlrcpp::Any visitBlock(DplParser::BlockContext *parseNode) override;

    // Declarations
    antlrcpp::Any visitStms(DplParser::StmsContext *parseNode) override;
    antlrcpp::Any visitProcdec(DplParser::ProcdecContext *parseNode) override;
    antlrcpp::Any visitAssignstm(DplParser::AssignstmContext *parseNode) override;
    antlrcpp::Any visitReturnstm(DplParser::ReturnstmContext *parseNode) override;

    // IF-ELSE
    antlrcpp::Any visitIfstm(DplParser::IfstmContext *parseNode) override;
    antlrcpp::Any visitElsestm(DplParser::ElsestmContext *parseNode) override;

    // While
    antlrcpp::Any visitWhilestm(DplParser::WhilestmContext *parseNode) override;

    // Expressions  The expressions isn't correctly sequenced
    antlrcpp::Any visitJuncexpr(DplParser::JuncexprContext *parseNode) override;
    antlrcpp::Any visitNotexpr(DplParser::NotexprContext *parseNode) override;
    antlrcpp::Any visitCompexpr(DplParser::CompexprContext *parseNode) override;
    antlrcpp::Any visitArthexpr(DplParser::ArthexprContext *parseNode) override;

    // Terms
    antlrcpp::Any visitTerminal(tree::TerminalNode *node) override;
    antlrcpp::Any visitList(DplParser::ListContext *parseNode) override;
    antlrcpp::Any visitTable(DplParser::TableContext *parseNode) override;
    antlrcpp::Any visitColumn(DplParser::ColumnContext *parseNode) override;
    antlrcpp::Any visitTerm(DplParser::TermContext *parseNode) override;
    antlrcpp::Any visitSubscript(DplParser::SubscriptContext *parseNode) override;
    antlrcpp::Any visitIndex(DplParser::IndexContext *parseNode) override;
    antlrcpp::Any visitHeaderindex(DplParser::HeaderindexContext *parseNode) override;
    antlrcpp::Any visitFiltering(DplParser::FilteringContext *parseNode) override;

    antlrcpp::Any visitUnaryexpr(DplParser::UnaryexprContext *parseNode) override;
    antlrcpp::Any visitProccall(DplParser::ProccallContext *parseNode) override;
    antlrcpp::Any visitArgs(DplParser::ArgsContext *parseNode) override;
    antlrcpp::Any visitParams(DplParser::ParamsContext *parseNode) override;

    AstNode *getRoot();
};

#endif