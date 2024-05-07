#ifndef ASTBUILDER_HPP
#define ASTBUILDER_HPP

#include <DplLexer.h>
#include <DplParser.h>
#include <DplParserBaseVisitor.h>

#include <AllNodeIncludes.hpp>
#include <functional>
#include <memory>

using namespace antlr4;
using namespace dplgrammar;

class AstBuilder : public DplParserBaseVisitor {
   private:
    DplParser *parser;  // Add a parser member
    DplLexer *lexer;    // Add a lexer member
    std::shared_ptr<AstNode> root;
    std::shared_ptr<AstNode> currentNode;

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
    antlrcpp::Any visitOrexpr(DplParser::OrexprContext *parseNode) override;
    antlrcpp::Any visitAndexpr(DplParser::AndexprContext *parseNode) override;
    antlrcpp::Any visitNotexpr(DplParser::NotexprContext *parseNode) override;
    antlrcpp::Any visitEqulexpr(DplParser::EqulexprContext *parseNode) override;
    antlrcpp::Any visitCompexpr(DplParser::CompexprContext *parseNode) override;
    antlrcpp::Any visitPlusexpr(DplParser::PlusexprContext *parseNode) override;
    antlrcpp::Any visitTablexpr(DplParser::TablexprContext *parseNode) override;
    antlrcpp::Any visitMultexpr(DplParser::MultexprContext *parseNode) override;
    antlrcpp::Any visitPolaexpr(DplParser::PolaexprContext *parseNode) override;
    antlrcpp::Any visitExpoexpr(DplParser::ExpoexprContext *parseNode) override;

    // Terms
    antlrcpp::Any visitTerminal(tree::TerminalNode *node) override;
    antlrcpp::Any visitNumber(DplParser::NumberContext *parseNode) override;
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

    std::shared_ptr<AstNode> getRoot();

   private:
    void initNewNode(antlr4::ParserRuleContext *parseNode, const std::shared_ptr<AstNode> &newNode,
                     const std::string &text = "");

    antlrcpp::Any indexNode(const std::function<std::shared_ptr<AstNode>()>& createNode,
                                    antlr4::ParserRuleContext* parseNode, size_t childIndex,
                                    const std::string& text = "");

    antlrcpp::Any unaryNode(const std::function<std::shared_ptr<AstNode>()> &createNode,
                            antlr4::ParserRuleContext *parseNode, size_t childIndex,
                            const std::string &text = "", bool hasChild = true);

    antlrcpp::Any unaryNodeList(const std::function<std::shared_ptr<AstNode>()> &createNode,
                                antlr4::ParserRuleContext *parseNode, size_t startIndex,
                                size_t interval, const std::string &text = "", bool hasChild = true);

    antlrcpp::Any binaryNode(const std::function<std::shared_ptr<AstNode>()> &createNode,
                             antlr4::ParserRuleContext *parseNode, size_t leftIndex,
                             size_t rightIndex, bool restoreOldCurrent = true,
                             const std::string &text = "");

    antlrcpp::Any unaryExpr(const std::function<std::shared_ptr<AstNode>(size_t)> &createNode,
                            antlr4::ParserRuleContext *parseNode);

    antlrcpp::Any binaryExpr(const std::function<std::shared_ptr<AstNode>(size_t)> &createNode,
                             antlr4::ParserRuleContext *parseNode);

    static antlr4::Token *getChildToken(antlr4::tree::ParseTree *parseNode, size_t childIndex);
};

#endif