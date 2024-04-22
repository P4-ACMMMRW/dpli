parser grammar DplParser;

options {
	tokenVocab = DplLexer;
}

prog: (stm Newline? | procdec Newline? | Newline)+ EOF;


procdec: Def Identifier OpenPar ClosePar Colon block 
       | Def Identifier OpenPar params ClosePar Colon block;


params: Identifier (Comma Identifier)*;
 
// Stms
stm: ifstm
   | whilestm
   | assignstm
   | flowstm
   | returnstm
   | juncexpr;

stms: (stm Newline?)+;

block: Indent Newline? stms Dedent Newline?;


// If
ifstm: If juncexpr Colon block elsestm?;

elsestm: Else Colon block;


// While
whilestm: While juncexpr Colon block;


// Assign
assignstm: subscript Assign juncexpr;

// Flow
flowstm: Break
       | Continue;

// Return
returnstm: Return juncexpr
         | Return;

// Expressions
juncexpr: notexpr ((And | Or) notexpr)*;

notexpr: Not* equlexpr;

equlexpr: compexpr ((Equal | NotEqual) compexpr)*;

compexpr: plusexpr ((Equal | NotEqual | Greater | GreaterEqual | Less | LessEqual) plusexpr)*;

plusexpr: tablexpr ((Plus | Minus)  tablexpr)*;

tablexpr: multexpr ((Union | Intersection) multexpr)*; 

multexpr: polaexpr ((Star | Slash |  Mod) polaexpr)*;

polaexpr: ((Plus | Minus))* expoexpr;

expoexpr: <assoc = right> term (Exponent term)*;
         
term: OpenPar juncexpr ClosePar
    | list
    | table
    | Float
    | Integer
    | Bool 
    | String 
    | None
    | subscript; 

subscript: Identifier (proccall | headerindex | index | filtering)*;

list: OpenSquare args CloseSquare
    | OpenSquare CloseSquare;

table: OpenCurly column (Comma column)* CloseCurly
     | OpenCurly CloseCurly; 

column: String Colon list;

// Trailers
index: (OpenSquare juncexpr CloseSquare);

headerindex: (OpenSquare Dollar juncexpr CloseSquare);

filtering: (OpenSquare unaryexpr CloseSquare);


unaryexpr: (Equal | NotEqual | Greater | GreaterEqual | Less | Less) juncexpr;


proccall: OpenPar ClosePar  
        | OpenPar args ClosePar;

args: juncexpr (Comma juncexpr)*;