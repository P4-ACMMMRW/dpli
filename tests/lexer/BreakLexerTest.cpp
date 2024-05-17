#include "TestingUtil.hpp"

using namespace dplgrammar;

LEXER_TEST("break.dpl") {
    std::vector<size_t> expectedTokenTypes = {
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Integer,
        DplLexer::Newline,
        DplLexer::Newline,
        DplLexer::While,
        DplLexer::Bool,
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
        DplLexer::Equal,
        DplLexer::Integer,
        DplLexer::Colon,
        DplLexer::Indent,
        DplLexer::Newline,
        DplLexer::Break,
        DplLexer::Newline,
        DplLexer::Dedent,
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::String,
        DplLexer::ClosePar,
        DplLexer::Dedent,
        DplLexer::Newline
    };

    dplutil::TestingUtil::testTokens("break.dpl", expectedTokenTypes);
}
