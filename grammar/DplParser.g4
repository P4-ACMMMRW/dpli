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
   | orexpr;

stms: (stm Newline? | Newline)+;

block: Indent Newline? stms Dedent Newline?;


// If
ifstm: If orexpr Colon block elsestm?;

elsestm: Else Colon block;


// While
whilestm: While orexpr Colon block;


// Assign
assignstm: subscript Assign orexpr;

// Flow
flowstm: Break
       | Continue;

// Return
returnstm: Return orexpr
         | Return;

// Expressions
orexpr: andexpr (Or andexpr)*;

andexpr: notexpr (And notexpr)*;

notexpr: Not notexpr 
       | equlexpr;

equlexpr: compexpr ((Equal | NotEqual) compexpr)*;

compexpr: plusexpr ((Greater | GreaterEqual | Less | LessEqual) plusexpr)*;

plusexpr: tablexpr ((Plus | Minus)  tablexpr)*;

tablexpr: multexpr ((Union | Intersection) multexpr)*; 

multexpr: polaexpr ((Star | Slash |  Mod) polaexpr)*;

polaexpr: (Plus | Minus) polaexpr
        | expoexpr;

expoexpr: <assoc = right> term (Exponent term)*;
         
term: OpenPar orexpr ClosePar
    | list
    | table
    | number
    | Bool 
    | String 
    | None
    | subscript; 

number: (Minus | Plus) number
      | (Integer | Float);

subscript: Identifier (proccall | headerindex | index | filtering)*;

list: OpenSquare args CloseSquare
    | OpenSquare CloseSquare;

table: OpenCurly column (Comma column)* CloseCurly
     | OpenCurly CloseCurly; 

column: orexpr Colon list;

// Trailers
index: (OpenSquare orexpr CloseSquare);

headerindex: (OpenSquare Dollar orexpr CloseSquare);

filtering: (OpenSquare unaryexpr CloseSquare);


unaryexpr: (Equal | NotEqual | Greater | GreaterEqual | Less | LessEqual) orexpr;


proccall: OpenPar ClosePar  
        | OpenPar args ClosePar;

args: orexpr (Comma orexpr)*;