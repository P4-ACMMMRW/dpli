#include <TestingUtil.hpp>

using namespace dplgrammar;

LEXER_TEST("math.dpl") {
    std::vector<size_t> expectedTokens = {
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Integer,
        DplLexer::Exponent,
        DplLexer::Integer,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Integer,
        DplLexer::Star,
        DplLexer::Integer,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Integer,
        DplLexer::Slash,
        DplLexer::Integer,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Integer,
        DplLexer::Mod,
        DplLexer::Integer,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::ClosePar
    };

    util::TestingUtil::testTokens("math.dpl", expectedTokens);
}