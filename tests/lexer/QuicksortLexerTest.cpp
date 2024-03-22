#include <TestingUtil.hpp>

using namespace dplgrammar;
/*
def quicksort(A, lo, hi):
    if lo >= 0 and lo < hi:
        p = partition(A, lo, hi)
        quicksort(A, lo, p[0] - 1)
        quicksort(A, p[1] + 1, hi)

def partition(A, lo, hi):
    pivot = A[(lo + hi) / 2]

    lt = lo
    eq = lo
    gt = hi

    while eq <= gt:
        if A[eq] < pivot:
            swap(A, eq, lt)
            lt = lt + 1
            eq = eq + 1
        else:
            if A[eq] > pivot:
                swap(A, eq, gt)
                gt = gt - 1
            else:
                eq = eq + 1
    
    return [lt, gt]

def swap(A, i, j):
    temp = A[i]
    A[i] = A[j]
    A[j] = temp

A = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5]
quicksort(A, 0, len(A) - 1)

print("Sorted list: " + A)
*/


LEXER_TEST("quicksort.dpl") {
    std::vector<int> expectedTokens = {
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

    util::TestingUtil::testTokens("quicksort.dpl", expectedTokens);
}