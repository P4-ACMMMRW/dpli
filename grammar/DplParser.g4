parser grammar DplParser;

options {
	tokenVocab = DplLexer;
}

prog:  (stm Newline? | procdec Newline? | Newline)+ EOF;


procdec: Def Identifier OpenPar params ClosePar Colon block
       | Def Identifier OpenPar ClosePar Colon block;


params: Identifier (Comma Identifier)*;
 
// Stms
stm: ifstm
   | whilestm
   | assignstm
   | flowstm
   | returnstm
   | replacestm;

stms: (stm Newline?)+;

block: Indent Newline? stms Dedent Newline?;


// If
ifstm: If expr Colon block elsestm?;

elsestm: Else Colon block;


// While
whilestm: While expr Colon block;


// Assign
assignstm: expr (Assign expr)?;

// Flow
flowstm: Break
       | Continue;

// Return
returnstm: Return expr
         | Return;

replacestm: Replace expr With expr;

// Expressions
expr: expr op = And expr
    | expr op = Or  expr
    | compexpr;

compexpr: compexpr op = (Equal | NotEqual | Greater | GreaterEqual | Less | LessEqual) compexpr
        | arthexpr;

arthexpr: <assoc = right> arthexpr op = Exponent arthexpr
        | arthexpr op = (Star | Slash |  Mod)    arthexpr
        | arthexpr op = (Plus | Minus)           arthexpr
        | notexpr;


// Terms
notexpr: op = Not            notexpr
       | op = (Plus | Minus) notexpr
       | subscript;

subscript: subscript proccall
         | subscript indexing
         | subscript filtering
         | term;
         
term: OpenPar expr ClosePar
    | list
    | table
    | number 
    | Bool 
    | String 
    | None
    | Identifier; 

number: (Plus | Minus)* (Float | Integer);

list: OpenSquare args? CloseSquare;

table: OpenCurly (column (Comma column)*)? CloseCurly; 

column: String Colon list;

// Trailers
indexing: (OpenSquare expr CloseSquare);

filtering: (OpenSquare unaryexpr CloseSquare);


unaryexpr: (Equal | NotEqual | Greater | GreaterEqual | Less | Less) expr;


proccall: OpenPar ClosePar  
        | OpenPar args ClosePar;

args: expr (Comma expr)*;

 