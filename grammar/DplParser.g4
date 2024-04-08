parser grammar DplParser;

options {
	tokenVocab = DplLexer;
}

prog:  (stm Newline? | procdec Newline?)+ EOF;


stm: ifstm
   | whilestm
   | assignstm
   | flowstm
   | returnstm
   | replacestm;

ifstm: If expr Colon Indent stm+ Dedent (Else Colon Indent stm+ Dedent)?;

whilestm: While expr Colon Indent stm+ Dedent;

assignstm: expr (Assign expr)?;

flowstm: Break
       | Continue;

returnstm: Return expr
         | Return;

replacestm: Replace expr With expr;

expr: compexpr
    | Not expr
    | expr op = And expr
    | expr op = Or expr;

compexpr: compexpr op = (Equal | NotEqual | Greater | GreaterEqual | Less | LessEqual) compexpr
        | arthexpr;

arthexpr: subscript
        | <assoc = right> arthexpr op = Exponent arthexpr
        | op = (Plus | Minus)                    arthexpr
        | arthexpr op = (Star | Slash |  Mod)    arthexpr
        | arthexpr op = (Plus | Minus)           arthexpr; 

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

number: Minus? (Float | Integer);

indexing: (OpenSquare expr CloseSquare);

filtering: (OpenSquare unaryexpr CloseSquare);

proccall: Identifier OpenPar ClosePar  
        | Identifier OpenPar args ClosePar;

unaryexpr: (Equal | NotEqual | Greater | GreaterEqual | Less | Less) expr;



list: OpenSquare args CloseSquare;

table: OpenCurly (column (Comma column)*)? CloseCurly; 

column: String Colon list;

procdec: Def Identifier OpenPar params ClosePar Colon Indent (stm Newline?)+ Dedent
       | Def Identifier OpenPar ClosePar Colon Indent (stm Newline?)+ Dedent;


args: expr (Comma expr)*;


params: Identifier (Comma Identifier)*;
 