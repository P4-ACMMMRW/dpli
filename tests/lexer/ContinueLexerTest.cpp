#include <TestingUtil.hpp>

using namespace dplgrammar;

LEXER_TEST("continue.dpl") {
    std::vector<size_t> expectedTokens = {
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Integer,
        DplLexer::Newline,
        DplLexer::Newline,
        DplLexer::While,
        DplLexer::Identifier,
        DplLexer::Less,
        DplLexer::Integer,
        DplLexer::Colon,
        DplLexer::Indent,
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::Plus,
        DplLexer::Integer,
        DplLexer::Newline,
        DplLexer::Newline,
        DplLexer::If,
        DplLexer::Identifier,
        DplLexer::Mod,
        DplLexer::Integer,
        DplLexer::Equal,
        DplLexer::Integer,
        DplLexer::Colon,
        DplLexer::Indent,
        DplLexer::Newline,
        DplLexer::Continue,
        DplLexer::Newline,
        DplLexer::Dedent,
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Dedent,
        DplLexer::Newline
    };

    dplutil::TestingUtil::testTokens("continue.dpl", expectedTokens);
}