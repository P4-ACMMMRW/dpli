#include "TestingUtil.hpp"

using namespace dplgrammar;

LEXER_TEST("math.dpl") {
    std::vector<size_t> expectedTokens = {
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Integer,
        DplLexer::Exponent,
        DplLexer::Integer,
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Integer,
        DplLexer::Star,
        DplLexer::Integer,
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Integer,
        DplLexer::Slash,
        DplLexer::Integer,
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Integer,
        DplLexer::Mod,
        DplLexer::Integer,
        DplLexer::Newline,
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Newline
    };

    dplutil::TestingUtil::testTokens("math.dpl", expectedTokens);
}