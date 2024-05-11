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
#include <AstTestVisitor.hpp>
#include <Evaluator.hpp>

#define LEXER_TEST(name) TEST_CASE("Lexer -- " #name, "[lexer]")
#define PARSER_TEST(name) TEST_CASE("Parser -- " #name, "[parser]")
#define AST_TEST(name) TEST_CASE("Ast -- " #name, "[ast]")
#define EVAL_TEST(name) TEST_CASE("Eval --" #name, "[eval]")

namespace dplutil {
    class TestVisitor : public dplgrammar::DplParserBaseVisitor {
        private:
            dplgrammar::DplParser* parser; // Add a parser member
            std::vector<size_t> expectedTreeNodes;

        public:
            TestVisitor(dplgrammar::DplParser* parser, std::vector<size_t> expectedTreeNodes) 
                : parser(parser), expectedTreeNodes(expectedTreeNodes) {} 

            void printTokens(int ruleIndex);
            void testNode(antlr4::ParserRuleContext *ctx);
            antlrcpp::Any visitChildren(antlr4::tree::ParseTree *tree) override;
    };

    class TestingUtil {
        public:
            static void testTokens(std::string testFileName, std::vector<size_t> expectedTokenTypes);
            static void testParser(std::string testFileName, std::vector<size_t> expectedTreeNodes);
            static void testAst(std::string testFileName, std::vector<size_t> expectedTreeNodes);
            static void testEval(std::string testFileName, std::vector<std::pair<std::string, dplsrc::Value>> expectedVarVec);

        private:
            static constexpr std::string_view exampleLocation = "../../docs/examples/"; 
    };
}

#endif
