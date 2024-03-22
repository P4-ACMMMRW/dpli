#include <TestingUtil.hpp>

using namespace dplgrammar;

LEXER_TEST("break.dpl") {
    std::vector<int> expectedTokenTypes = {
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Integer,
        DplLexer::While,
        DplLexer::Bool,
        DplLexer::Colon,
        DplLexer::Indent,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::Plus,
        DplLexer::Integer,
        DplLexer::If,
        DplLexer::Identifier,
        DplLexer::Equal,
        DplLexer::Integer,
        DplLexer::Colon,
        DplLexer::Indent,
        DplLexer::Break,
        DplLexer::Dedent,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::String,
        DplLexer::ClosePar,
        DplLexer::Dedent
    };

    util::TestingUtil::testTokens("break.dpl", expectedTokenTypes);
}
