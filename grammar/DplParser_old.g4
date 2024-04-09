parser grammar DplParser;

options {
	tokenVocab = DplLexer;
}

// These are all supported parser sections:

// Parser file header. Appears at the top in all parser related files. Use e.g. for copyrights.
@parser::header {/* parser/listener/visitor header section */}

// Appears before any #include in h + cpp files.
@parser::preinclude {/* parser precinclude section */}

// Follows directly after the standard #includes in h + cpp files.
@parser::postinclude {
/* parser postinclude section */
#ifndef _WIN32
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
}

// Directly preceeds the parser class declaration in the h file (e.g. for additional types etc.).
@parser::context {/* parser context section */}

// Appears in the private part of the parser in the h file.
// The function bodies could also appear in the definitions section, but I want to maximize
// Java compatibility, so we can also create a Java parser from this grammar.
// Still, some tweaking is necessary after the Java file generation (e.g. bool -> boolean).
@parser::members {
/* public parser declarations/members section */
bool myAction() { return true; }
bool doesItBlend() { return true; }
void cleanUp() {}
void doInit() {}
void doAfter() {}
}

// Actual grammar start.
prog: (stm | procdec)* EOF;

// Statement 
stm: ifstm
   | loopstm
   | flowstm
   | assignstm
   | replacestm
   | expr
   | Identifier;

// Control Statements
ifstm: If expr Colon Indent stm+ Dedent
     | If expr Colon Indent stm+ Dedent elsestm;

elsestm: Else Colon Indent stm+ Dedent;

// Loop Statements
loopstm: While expr Colon Indent stm+ Dedent
       | While expr Star Colon Indent stm+ Dedent;

// Flow Statements
flowstm: Break
       | Continue
       | Return expr
       | Return;

assignstm: (Identifier | listcall | tablecall) Assign expr;

replacestm: Replace expr With expr;

// Expressions
expr: notexpr
    | expr arthexpr
    | expr boolexpr
    | listcall
    | tablecall
    | proccall
    | literal
    | Identifier
    | OpenPar expr ClosePar;

arthexpr: (Plus | Minus | Star | Slash | Mod | Exponent) expr;

boolexpr: junctionopr | compareopr;

notexpr: Not expr;


// Table Unary Expression
unaryexpr: compareopr junctionopr*;



// Table Non-Terminals
table:  OpenCurly (String Colon list (Comma String Colon list)*)? CloseCurly; 

tablecall: Identifier (OpenSquare expr CloseSquare (OpenSquare unaryexpr CloseSquare)?) 
         | tablecall OpenSquare expr CloseSquare (OpenSquare unaryexpr CloseSquare)?
         | OpenPar tablecall ClosePar OpenSquare expr CloseSquare (OpenSquare unaryexpr CloseSquare)?;



// List Non-Terminals 
list:  OpenSquare args? CloseSquare;

listcall: Identifier (OpenSquare expr CloseSquare)+;



// Procedures Non-Terminals
procdec: Def Identifier OpenPar params ClosePar Colon Indent stm+ Dedent
       | Def Identifier OpenPar ClosePar Colon Indent stm+ Dedent;

proccall: Identifier OpenPar args ClosePar 
        | Identifier OpenPar ClosePar;



// Args
args: expr (Comma expr)*;

// Params
params: Identifier (Comma Identifier)*;





// Compare Operators
compareopr : (Equal | NotEqual | Less | Greater | LessEqual | GreaterEqual) expr;

// Junction Operator
junctionopr: (And | Or) expr;



// Literals
literal: Float 
       | Integer
       | Bool
       | String
       | list
       | table
       | None;

