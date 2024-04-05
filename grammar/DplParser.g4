parser grammar DplParser;

options {
	tokenVocab = DplLexer;
}

prog: (stm | procdec)+ EOF;

stm: ifstm
   | whilestm
   | assignstm
   | flowstm
   | returnstm
   | replacestm
   | proccall;

ifstm: If expr Colon Indent stm+ Dedent (Else Colon Indent stm+ Dedent)?;

whilestm: While expr Colon Indent stm+ Dedent;

assignstm: listcall   Assign expr
         | tablecall  Assign expr
         | proccall   Assign expr
         | Identifier Assign expr;

flowstm: Break
       | Continue;

returnstm: Return expr
         | Return;

replacestm: Replace expr With expr;


expr: eqexpr (Or  eqexpr)*
    | eqexpr (And eqexpr)*; 

eqexpr: relexpr (Equal    relexpr)* 
      | relexpr (NotEqual relexpr)*;

relexpr: plusexpr (Greater      plusexpr)*
       | plusexpr (Less         plusexpr)*
       | plusexpr (GreaterEqual plusexpr)*
       | plusexpr (LessEqual    plusexpr)*;

plusexpr: multexpr (Plus  multexpr)*
        | multexpr (Minus multexpr)*;

multexpr: expoexpr (Star  expoexpr)*
        | expoexpr (Slash expoexpr)*
        | expoexpr (Mod   expoexpr)*;

expoexpr: notexpr (Exponent notexpr)*;
 
notexpr: (Not | Minus)* term;

term: proccall 
    | list
    | table
    | list
    | Identifier 
    | Float 
    | Integer 
    | Bool 
    | String 
    | None 
    | OpenPar expr ClosePar;


unaryexpr: (Equal | NotEqual | Greater | GreaterEqual | Less | Less) expr;


list: OpenSquare args CloseSquare;

listcall: Identifier (OpenSquare expr CloseSquare)+;


table: OpenCurly (String Colon list (Comma String Colon list)*)? CloseCurly; 

tablecall: Identifier                 OpenSquare expr CloseSquare (OpenSquare unaryexpr CloseSquare)?
         | tablecall                  OpenSquare expr CloseSquare (OpenSquare unaryexpr CloseSquare)?
         | OpenPar tablecall ClosePar OpenSquare expr CloseSquare (OpenSquare unaryexpr CloseSquare)?;


procdec: Def Identifier OpenPar params ClosePar Colon Indent stm+ Dedent
       | Def Identifier OpenPar ClosePar Colon Indent stm+ Dedent;

proccall: Identifier OpenPar args ClosePar 
        | Identifier OpenPar ClosePar;


// Args
args: expr (Comma expr)*;

// Params
params: Identifier (Comma Identifier)*;
 