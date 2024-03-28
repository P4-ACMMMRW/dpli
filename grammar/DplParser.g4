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
prog: (stm | procdec)+;

// Statement 
stm: Indent stm+ Dedent
   | expr
   | Identifier
   | listdec
   | tabledec
   | ctrlstm
   | loopstm
   | flowstm
   | assignstm
   | replacestm;

// Control Statements
ctrlstm: If expr Colon stm
       | If expr Colon stm Else Colon stm;

// Loop Statements
loopstm: While expr Colon stm     
       | While expr Star Colon stm;

// Flow Statements
flowstm: Break
       | Continue
       | Return
       | Return expr;

assignstm: (Identifier | tablecall | listcall) Assign expr;

replacestm: Replace expr With expr;

// Expressions
expr: notexpr
    | OpenPar expr ClosePar
    | expr arthexpr
    | expr boolexpr
    | Identifier
    | tablecall
    | listcall
    | proccall
    | literal;

arthexpr: (Plus | Minus | Star | Slash | Mod | Exponent) expr;

boolexpr: (junctionopr | compareopr) expr;

notexpr: Not expr;


// Table Unary Expression
unaryexpr: compareopr expr (junctionopr expr)*;



// Table Non-Terminals
table:  OpenCurly (String Colon list (Comma String Colon list)*)? CloseCurly; 

tabledec: Identifier Assign table;

tablecall: OpenPar tablecall ClosePar
         | Identifier (OpenSquare expr CloseSquare (OpenSquare unaryexpr CloseSquare)?)? 
         | tablecall  OpenSquare expr CloseSquare (OpenSquare unaryexpr CloseSquare)?;



// List Non-Terminals 
list: OpenSquare args CloseSquare;

listdec: Identifier Assign list;

listcall: Identifier (OpenSquare Integer CloseSquare)+;



// Procedures Non-Terminals
procdec: Def Identifier OpenPar params ClosePar Colon stm;

proccall: Identifier OpenPar args ClosePar;



// Args
args: (expr (Comma expr)*)?;

// Params
params: (Identifier (Comma Identifier)*)?;





// Compare Operators
compareopr : (Equal | NotEqual | Less | Greater | LessEqual | GreaterEqual);

// Junction Operator
junctionopr: (And | Or);



// Literals
literal: Float 
       | Integer
       | Bool
       | String
       | list
       | table
       | None;

