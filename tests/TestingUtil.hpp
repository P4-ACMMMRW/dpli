#ifndef TEST_HPP
#define TEST_HPP

#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <antlr4-runtime.h>
#include <DplLexer.h>
#include <DplParser.h>


#define LEXER_TEST(name) TEST_CASE(name, "[lexer]")

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
    };
}

#endif
