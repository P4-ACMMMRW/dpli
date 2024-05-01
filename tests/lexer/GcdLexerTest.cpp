#include <TestingUtil.hpp>

using namespace dplgrammar;

LEXER_TEST("gcd.dpl") {
    std::vector<size_t> expectedTokenTypes = {
        DplLexer::Newline,
        DplLexer::Def,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Colon,
        DplLexer::Indent,
        DplLexer::Newline,
        DplLexer::If,
        DplLexer::Identifier,
        DplLexer::Equal,
        DplLexer::Integer,
        DplLexer::Colon,
        DplLexer::Indent,
        DplLexer::Newline,
        DplLexer::Return,
        DplLexer::Identifier,
        DplLexer::Dedent,
        DplLexer::Newline,
        DplLexer::Return,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::Mod,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Newline,
        DplLexer::Dedent,
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Integer,
        DplLexer::Comma,
        DplLexer::Integer,
        DplLexer::ClosePar,
        DplLexer::ClosePar,
        DplLexer::Newline
    };

    dplutil::TestingUtil::testTokens("gcd.dpl", expectedTokenTypes);
}