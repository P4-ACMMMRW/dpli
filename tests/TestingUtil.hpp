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


#define LEXER_TEST(name) TEST_CASE(name, "[lexer]")
#define PARSER_TEST(name) TEST_CASE(name, "[parser]")


class TestVisitor : public dplgrammar::DplParserBaseVisitor {
public:
    virtual antlrcpp::Any visitProg(dplgrammar::DplParser::ProgContext *node) override {
        std::cout << node->getText() + "\n" << std::endl;
        // Visit the children of the node.
        return visitChildren(node);
    }

    virtual std::any visitStm(dplgrammar::DplParser::StmContext *ctx) override {
        std::cout << "Stm " + ctx->getText() + "\n" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitCtrlstm(dplgrammar::DplParser::CtrlstmContext *ctx) override {
        std::cout << "Ctrlstm " + ctx->getText() + "\n" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitLoopstm(dplgrammar::DplParser::LoopstmContext *ctx) override {
        std::cout << "Loopstm " + ctx->getText() + "\n" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitFlowstm(dplgrammar::DplParser::FlowstmContext *ctx) override {
        std::cout << "Flowstm " + ctx->getText() + "\n" << std::endl;
        return visitChildren(ctx);
    }

    virtual std::any visitAssignstm(dplgrammar::DplParser::AssignstmContext *ctx) override {
        
        std::cout << "Assignstm " + ctx->getText() + "\n" << std::endl;
        return visitChildren(ctx);
    }

    // Override other visit methods as needed...
};


namespace util {
    class TestingUtil {
        public:
            static void testTokens(std::string testFileName, std::vector<int> expectedTokenTypes) {
                const std::string exampleLocation = "../docs/examples/";

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
                //REQUIRE(tokensSize == expectedTokenTypes.size());
                

                for (int i = 0; i < tokensSize; ++i) {
                    INFO(i);
                    REQUIRE(tokens.get(i)->getType() == expectedTokenTypes[i]);
                }
            }
        public: 
            static void testParser(std::string testFileName, std::vector<int> expectedTreeNodes) {
                const std::string exampleLocation = "../docs/examples/";

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
                antlr4::tree::ParseTree* tree = parser.prog();

                TestVisitor visitor;
                visitor.visit(tree);
            }
    };
}

#endif
