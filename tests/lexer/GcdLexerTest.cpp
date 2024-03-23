#include <TestingUtil.hpp>

using namespace dplgrammar;

LEXER_TEST("gcd.dpl") {
    std::vector<size_t> expectedTokenTypes = {
        DplLexer::Def,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Colon,
        DplLexer::Indent,
        DplLexer::If,
        DplLexer::Identifier,
        DplLexer::Equal,
        DplLexer::Integer,
        DplLexer::Colon,
        DplLexer::Indent,
        DplLexer::Return,
        DplLexer::Identifier,
        DplLexer::Dedent,
        DplLexer::Return,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::Mod,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Dedent,
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

    util::TestingUtil::testTokens("gcd.dpl", expectedTokenTypes);
}