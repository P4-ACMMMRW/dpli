#include "Test.hpp"

using namespace antlr4;
using namespace dplgrammar;

TEST_CASE("gcd.dpl", "[lexer]") {
    std::ifstream file = std::ifstream(std::filesystem::path(exampleLocation + "gcd.dpl"));
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << exampleLocation + "gcd.dpl";
        FAIL();
    }

    ANTLRInputStream input(file);

    DplLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();

    std::vector<int> expectedTokenTypes = {
        DplLexer::Def,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::Colon,
        DplLexer::IntType,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::Colon,
        DplLexer::IntType,
        DplLexer::ClosePar,
        DplLexer::Arrow,
        DplLexer::IntType,
        DplLexer::Colon,
        DplLexer::If,
        DplLexer::Identifier,
        DplLexer::Equal,
        DplLexer::Integer,
        DplLexer::Colon,
        DplLexer::Return,
        DplLexer::Identifier,
        DplLexer::Return,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::Mod,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Integer,
        DplLexer::Comma,
        DplLexer::Integer,
        DplLexer::ClosePar,
        DplLexer::ClosePar
    };

    size_t tokensSize = tokens.size() - 1;
    INFO("Token stream size mismatch");
    REQUIRE(tokensSize == expectedTokenTypes.size());

    for (int i = 0; i < tokensSize; ++i) {
        REQUIRE(tokens.get(i)->getType() == expectedTokenTypes[i]);
    }
}