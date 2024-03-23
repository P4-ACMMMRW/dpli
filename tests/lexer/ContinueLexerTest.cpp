#include <TestingUtil.hpp>

using namespace dplgrammar;

LEXER_TEST("continue.dpl") {
    std::vector<size_t> expectedTokens = {
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Integer,
        DplLexer::While,
        DplLexer::Identifier,
        DplLexer::Less,
        DplLexer::Integer,
        DplLexer::Colon,
        DplLexer::Indent,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::Plus,
        DplLexer::Integer,
        DplLexer::If,
        DplLexer::Identifier,
        DplLexer::Mod,
        DplLexer::Integer,
        DplLexer::Equal,
        DplLexer::Integer,
        DplLexer::Colon,
        DplLexer::Indent,
        DplLexer::Continue,
        DplLexer::Dedent,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Dedent
    };

    util::TestingUtil::testTokens("continue.dpl", expectedTokens);
}