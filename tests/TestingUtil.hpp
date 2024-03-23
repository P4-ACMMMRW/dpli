#ifndef TEST_HPP
#define TEST_HPP

#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <antlr4-runtime.h>
#include <DplLexer.h>
#include <DplParser.h>

#include <DplParserBaseVisitor.h>


#include <DplParserBaseVisitor.h>

#define LEXER_TEST(name) TEST_CASE("Lexer -- " #name, "[lexer]")
#define PARSER_TEST(name) TEST_CASE("Parser -- " #name, "[parser]")


class TestVisitor : public dplgrammar::DplParserBaseVisitor {
private:
    dplgrammar::DplParser* parser; // Add a parser member
    std::vector<int> expectedTreeNodes;

public:
    TestVisitor(dplgrammar::DplParser* parser, std::vector<int> expectedTreeNodes) 
        : parser(parser), expectedTreeNodes(expectedTreeNodes) {} 

    void printTokens(int ruleIndex) {
        std::string name = parser->getRuleNames()[ruleIndex];

        name[0] = std::toupper(static_cast<unsigned char>(name[0]));
        std::cout << "DplParser::Rule" << name + "," << std::endl;
    }

    void testNode(antlr4::ParserRuleContext *ctx) {
        if ( (int) ctx->getRuleIndex() != (int) expectedTreeNodes[0]) {
            std::cerr <<  ctx->getRuleIndex() << " != " << expectedTreeNodes[0] << "\n";
            assert(false);
        }
        expectedTreeNodes.erase(expectedTreeNodes.begin());
    }

    virtual antlrcpp::Any visitProg(dplgrammar::DplParser::ProgContext *ctx) {
        //printTokens(ctx->getRuleIndex());
        testNode(ctx);
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitStm(dplgrammar::DplParser::StmContext *ctx) override {
        //printTokens(ctx->getRuleIndex());
        testNode(ctx);
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitCtrlstm(dplgrammar::DplParser::CtrlstmContext *ctx) override {
         //printTokens(ctx->getRuleIndex());
        testNode(ctx);
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitLoopstm(dplgrammar::DplParser::LoopstmContext *ctx) override {
         //printTokens(ctx->getRuleIndex());
        testNode(ctx);
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitFlowstm(dplgrammar::DplParser::FlowstmContext *ctx) override {
         //printTokens(ctx->getRuleIndex());
        testNode(ctx);
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitAssignstm(dplgrammar::DplParser::AssignstmContext *ctx) override {
         //printTokens(ctx->getRuleIndex());
        testNode(ctx);
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitExpr(dplgrammar::DplParser::ExprContext *ctx) override {
         //printTokens(ctx->getRuleIndex());
        testNode(ctx);
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitArthexpr(dplgrammar::DplParser::ArthexprContext *ctx) override {
         //printTokens(ctx->getRuleIndex());
        testNode(ctx);
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitBoolexpr(dplgrammar::DplParser::BoolexprContext *ctx) override {
         //printTokens(ctx->getRuleIndex());
        testNode(ctx);
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitUnaryexpr(dplgrammar::DplParser::UnaryexprContext *ctx) override {
         //printTokens(ctx->getRuleIndex());
        testNode(ctx);
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitTable(dplgrammar::DplParser::TableContext *ctx) override {
         //printTokens(ctx->getRuleIndex());
        testNode(ctx);
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitTabledec(dplgrammar::DplParser::TabledecContext *ctx) override {
         //printTokens(ctx->getRuleIndex());
        testNode(ctx); 
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitTablecall(dplgrammar::DplParser::TablecallContext *ctx) override {
         //printTokens(ctx->getRuleIndex());
        testNode(ctx);
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitList(dplgrammar::DplParser::ListContext *ctx) override {
         //printTokens(ctx->getRuleIndex());
        testNode(ctx);
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitListdec(dplgrammar::DplParser::ListdecContext *ctx) override {
         //printTokens(ctx->getRuleIndex());
        testNode(ctx);
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitListcall(dplgrammar::DplParser::ListcallContext *ctx) override {
         //printTokens(ctx->getRuleIndex());
        testNode(ctx);
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitProcdec(dplgrammar::DplParser::ProcdecContext *ctx) override {
         //printTokens(ctx->getRuleIndex());
        testNode(ctx);
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitProccall(dplgrammar::DplParser::ProccallContext *ctx) override {
         //printTokens(ctx->getRuleIndex());
        testNode(ctx);
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitArgs(dplgrammar::DplParser::ArgsContext *ctx) override {
         //printTokens(ctx->getRuleIndex());
        testNode(ctx);
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitParams(dplgrammar::DplParser::ParamsContext *ctx) override {
         //printTokens(ctx->getRuleIndex());
        testNode(ctx);
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitCompareopr(dplgrammar::DplParser::CompareoprContext *ctx) override {
         //printTokens(ctx->getRuleIndex());
        testNode(ctx);
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitJunctionopr(dplgrammar::DplParser::JunctionoprContext *ctx) override {
         //printTokens(ctx->getRuleIndex());
        testNode(ctx);
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitLiteral(dplgrammar::DplParser::LiteralContext *ctx) override {
         //printTokens(ctx->getRuleIndex());
        testNode(ctx);
        return visitChildren(ctx);
    }
};


namespace util {
    class TestingUtil {
        public:
            static void testTokens(std::string testFileName, std::vector<size_t> expectedTokenTypes) {
                const std::string exampleLocation = "../../docs/examples/";

                std::string filePath = exampleLocation + testFileName;

                if (!std::filesystem::exists(filePath)) {
                    std::cerr << "File does not exist: " << filePath << '\n';
                    exit(EXIT_FAILURE);
                }

                std::ifstream file = std::ifstream(filePath);
                if (!file.is_open()) {
                    std::cerr << "Failed to open file: " << filePath;
                    FAIL();
                }

                antlr4::ANTLRInputStream input(file);

                dplgrammar::DplLexer lexer(&input);
                antlr4::CommonTokenStream tokens(&lexer);

                tokens.fill();

                size_t tokensSize = tokens.size() - 1;
                INFO("Token stream mismatch");

                for (size_t i = 0; i < tokensSize; ++i) {
                    INFO(i);
                    REQUIRE(tokens.get(i)->getType() == expectedTokenTypes[i]);
                }
            }
        public: 
            static void testParser(std::string testFileName, std::vector<int> expectedTreeNodes) {
                const std::string exampleLocation = "../../docs/examples/";

                std::string filePath = exampleLocation + testFileName;

                if (!std::filesystem::exists(filePath)) {
                    std::cerr << "File does not exist: " << filePath << '\n';
                    exit(EXIT_FAILURE);
                }

                std::ifstream file = std::ifstream(filePath);
                if (!file.is_open()) {
                    std::cerr << "Failed to open file: " << filePath;
                    FAIL();
                }

                antlr4::ANTLRInputStream input(file);

                dplgrammar::DplLexer lexer(&input);
                antlr4::CommonTokenStream tokens(&lexer);

                tokens.fill();

                dplgrammar::DplParser parser(&tokens);

                TestVisitor visitor(&parser, expectedTreeNodes);
                antlr4::tree::ParseTree* tree = parser.prog();
                visitor.visit(tree);
            }
    };
}

#endif
