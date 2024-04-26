#include <TestingUtil.hpp>

using namespace dplgrammar;

LEXER_TEST("quicksort.dpl") {
    std::vector<size_t> expectedTokens = {
        DplLexer::Def,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Colon,
        DplLexer::Indent,
        DplLexer::If,
        DplLexer::Identifier,
        DplLexer::GreaterEqual,
        DplLexer::Integer,
        DplLexer::And,
        DplLexer::Identifier,
        DplLexer::Less,
        DplLexer::Identifier,
        DplLexer::Colon,
        DplLexer::Indent,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::OpenSquare,
        DplLexer::Integer,
        DplLexer::CloseSquare,
        DplLexer::Minus,
        DplLexer::Integer,
        DplLexer::ClosePar,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::OpenSquare,
        DplLexer::Integer,
        DplLexer::CloseSquare,
        DplLexer::Plus,
        DplLexer::Integer,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Dedent,
        DplLexer::Dedent, // Dedent for if statement
        DplLexer::Def,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Colon,
        DplLexer::Indent, // Indent for partition function
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::OpenSquare,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::Plus,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Slash,
        DplLexer::Integer,
        DplLexer::CloseSquare,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::While,
        DplLexer::Identifier,
        DplLexer::LessEqual,
        DplLexer::Identifier,
        DplLexer::Colon,
        DplLexer::Indent, // Indent for while loop
        DplLexer::If,
        DplLexer::Identifier,
        DplLexer::OpenSquare,
        DplLexer::Identifier,
        DplLexer::CloseSquare,
        DplLexer::Less,
        DplLexer::Identifier,
        DplLexer::Colon,
        DplLexer::Indent,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::Plus,
        DplLexer::Integer,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::Plus,
        DplLexer::Integer,
        DplLexer::Dedent, // Dedent for if statement
        DplLexer::Else,
        DplLexer::Colon,
        DplLexer::Indent, // Indent for else statement
        DplLexer::If,
        DplLexer::Identifier,
        DplLexer::OpenSquare,
        DplLexer::Identifier,
        DplLexer::CloseSquare,
        DplLexer::Greater,
        DplLexer::Identifier,
        DplLexer::Colon,
        DplLexer::Indent, // Indent for if statement
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::Minus,
        DplLexer::Integer,
        DplLexer::Dedent, // Dedent for if statement
        DplLexer::Else,
        DplLexer::Colon,
        DplLexer::Indent, // Indent for else statement
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::Plus,
        DplLexer::Integer,
        DplLexer::Dedent, // Dedent for else statement
        DplLexer::Dedent,
        DplLexer::Dedent,
        DplLexer::Return,
        DplLexer::OpenSquare,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::CloseSquare,
        DplLexer::Dedent, // Dedent for partition function
        DplLexer::Def,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Colon,
        DplLexer::Indent, // Indent for swap function
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::OpenSquare,
        DplLexer::Identifier,
        DplLexer::CloseSquare,
        DplLexer::Identifier,
        DplLexer::OpenSquare,
        DplLexer::Identifier,
        DplLexer::CloseSquare,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::OpenSquare,
        DplLexer::Identifier,
        DplLexer::CloseSquare,
        DplLexer::Identifier,
        DplLexer::OpenSquare,
        DplLexer::Identifier,
        DplLexer::CloseSquare,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::Dedent, // Dedent for swap function
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::OpenSquare,
        DplLexer::Integer,
        DplLexer::Comma,
        DplLexer::Integer,
        DplLexer::Comma,
        DplLexer::Integer,
        DplLexer::Comma,
        DplLexer::Integer,
        DplLexer::Comma,
        DplLexer::Integer,
        DplLexer::Comma,
        DplLexer::Integer,
        DplLexer::Comma,
        DplLexer::Integer,
        DplLexer::Comma,
        DplLexer::Integer,
        DplLexer::Comma,
        DplLexer::Integer,
        DplLexer::Comma,
        DplLexer::Integer,
        DplLexer::Comma,
        DplLexer::Integer,
        DplLexer::CloseSquare,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Integer,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Minus,
        DplLexer::Integer,
        DplLexer::ClosePar,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::String,
        DplLexer::Plus,
        DplLexer::Identifier,
        DplLexer::ClosePar,
    };

    //dplutil::TestingUtil::testTokens("quicksort.dpl", expectedTokens);
}