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

namespace util {
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
                std::cout << "DplParser::Rule" << name + ",\n";
            }

            void testNode(antlr4::ParserRuleContext *ctx) {
                INFO(std::to_string(ctx->getRuleIndex()) + " != " + std::to_string(expectedTreeNodes[0]) + '\n');
                REQUIRE(static_cast<int>(ctx->getRuleIndex()) == static_cast<int>(expectedTreeNodes[0]));
                expectedTreeNodes.erase(expectedTreeNodes.begin());
            }

            antlrcpp::Any visitChildren(antlr4::tree::ParseTree *tree) override {
                for (size_t i = 0; i < tree->children.size(); ++i) {

                    antlr4::ParserRuleContext* ctx = dynamic_cast<antlr4::ParserRuleContext*>(tree->children[i]);
                    if (ctx) {
                        testNode(ctx);
                    }
                    tree->children[i]->accept(this);
                }
                return nullptr;
            }
    };

    class TestingUtil {
        public:
            static void testTokens(std::string testFileName, std::vector<size_t> expectedTokenTypes) {
                std::string filePath = std::filesystem::path(std::string{exampleLocation} + testFileName).string();

                if (!std::filesystem::exists(filePath)) {
                    FAIL("File does not exist: " + filePath);
                }

                std::ifstream file{filePath};
                if (!file.is_open()) {
                    FAIL("Failed to open file: " + filePath);
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

            static void testParser(std::string testFileName, std::vector<int> expectedTreeNodes) {
                std::string filePath = std::filesystem::path(std::string{exampleLocation} + testFileName).string();

                if (!std::filesystem::exists(filePath)) {
                    FAIL("File does not exist: " + filePath);
                }

                std::ifstream file{filePath};
                if (!file.is_open()) {
                    FAIL("Failed to open file: " + filePath);
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

        private:
            static constexpr std::string_view exampleLocation = "../../docs/examples/"; 
    };
}

#endif
