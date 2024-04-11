parser grammar DplParser;

options {
	tokenVocab = DplLexer;
}

prog: (stm Newline? | procdec Newline? | Newline)+ EOF;


procdec: Def Identifier OpenPar params ClosePar Colon block
       | Def Identifier OpenPar ClosePar Colon block;


params: Identifier (Comma Identifier)*;
 
// Stms
stm: ifstm
   | whilestm
   | assignstm
   | flowstm
   | returnstm;

stms: (stm Newline?)+;

block: Indent Newline? stms Dedent Newline?;


// If
ifstm: If juncexpr Colon block elsestm?;

elsestm: Else Colon block;


// While
whilestm: While juncexpr Colon block;


// Assign
assignstm: juncexpr (Assign juncexpr)?;

// Flow
flowstm: Break
       | Continue;

// Return
returnstm: Return juncexpr
         | Return;

// Expressions
juncexpr: juncexpr op = And juncexpr
        | juncexpr op = Or  juncexpr
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
         | subscript headerindex
         | subscript index
         | subscript filtering
         | term;
         
term: OpenPar juncexpr ClosePar
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
index: (OpenSquare juncexpr CloseSquare);

headerindex: (OpenSquare Dollar juncexpr CloseSquare);

filtering: (OpenSquare unaryexpr CloseSquare);


unaryexpr: (Equal | NotEqual | Greater | GreaterEqual | Less | Less) juncexpr;


proccall: OpenPar ClosePar  
        | OpenPar args ClosePar;

args: juncexpr (Comma juncexpr)*;

 