#include "TestingUtil.hpp"

using namespace dplgrammar;

LEXER_TEST("quicksort.dpl") {
    std::vector<size_t> expectedTokens = {
        DplLexer::Newline,
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
        DplLexer::Newline,
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
        DplLexer::Newline,
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
        DplLexer::Newline,
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
        DplLexer::Newline,
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
        DplLexer::Newline,
        DplLexer::Dedent,
        DplLexer::Dedent, // Dedent for if statement
        DplLexer::Newline,
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
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::OpenSquare,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::Plus,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Slash,
        DplLexer::Integer,
        DplLexer::ClosePar,
        DplLexer::CloseSquare,
        DplLexer::Newline,
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::Newline,
        DplLexer::Newline,
        DplLexer::While,
        DplLexer::Identifier,
        DplLexer::LessEqual,
        DplLexer::Identifier,
        DplLexer::Colon,
        DplLexer::Indent, // Indent for while loop
        DplLexer::Newline,
        DplLexer::If,
        DplLexer::Identifier,
        DplLexer::OpenSquare,
        DplLexer::Identifier,
        DplLexer::CloseSquare,
        DplLexer::Less,
        DplLexer::Identifier,
        DplLexer::Colon,
        DplLexer::Indent,
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::Plus,
        DplLexer::Integer,
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::Plus,
        DplLexer::Integer,
        DplLexer::Dedent, // Dedent for if statement
        DplLexer::Newline,
        DplLexer::Else,
        DplLexer::Colon,
        DplLexer::Indent, // Indent for else statement
        DplLexer::Newline,
        DplLexer::If,
        DplLexer::Identifier,
        DplLexer::OpenSquare,
        DplLexer::Identifier,
        DplLexer::CloseSquare,
        DplLexer::Greater,
        DplLexer::Identifier,
        DplLexer::Colon,
        DplLexer::Indent, // Indent for if statement
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::Minus,
        DplLexer::Integer,
        DplLexer::Dedent, // Dedent for if statement
        DplLexer::Newline,
        DplLexer::Else,
        DplLexer::Colon,
        DplLexer::Indent, // Indent for else statement
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::Plus,
        DplLexer::Integer,
        DplLexer::Newline,
        DplLexer::Dedent, // Dedent for else statement
        DplLexer::Dedent,
        DplLexer::Dedent,
        DplLexer::Newline,
        DplLexer::Return,
        DplLexer::OpenSquare,
        DplLexer::Identifier,
        DplLexer::Comma,
        DplLexer::Identifier,
        DplLexer::CloseSquare,
        DplLexer::Newline,
        DplLexer::Dedent, // Dedent for partition function
        DplLexer::Newline,
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
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::OpenSquare,
        DplLexer::Identifier,
        DplLexer::CloseSquare,
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::OpenSquare,
        DplLexer::Identifier,
        DplLexer::CloseSquare,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::OpenSquare,
        DplLexer::Identifier,
        DplLexer::CloseSquare,
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::OpenSquare,
        DplLexer::Identifier,
        DplLexer::CloseSquare,
        DplLexer::Assign,
        DplLexer::Identifier,
        DplLexer::Newline,
        DplLexer::Dedent, // Dedent for swap function
        DplLexer::Newline,
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
        DplLexer::Newline,
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
        DplLexer::Newline,
        DplLexer::Newline,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::String,
        DplLexer::Plus,
        DplLexer::Identifier,
        DplLexer::OpenPar,
        DplLexer::Identifier,
        DplLexer::ClosePar,
        DplLexer::ClosePar,
        DplLexer::Newline
    };

    dplutil::TestingUtil::testTokens("quicksort.dpl", expectedTokens);
}