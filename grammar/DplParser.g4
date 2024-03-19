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

// Appears in the public part of the parser in the h file.
@parser::declarations {/* private parser declarations section */}

// Appears in line with the other class member definitions in the cpp file.
@parser::definitions {/* parser definitions section */}

// Additionally there are similar sections for (base)listener and (base)visitor files.
@parser::listenerpreinclude {/* listener preinclude section */}
@parser::listenerpostinclude {/* listener postinclude section */}
@parser::listenerdeclarations {/* listener public declarations/members section */}
@parser::listenermembers {/* listener private declarations/members section */}
@parser::listenerdefinitions {/* listener definitions section */}

@parser::baselistenerpreinclude {/* base listener preinclude section */}
@parser::baselistenerpostinclude {/* base listener postinclude section */}
@parser::baselistenerdeclarations {/* base listener public declarations/members section */}
@parser::baselistenermembers {/* base listener private declarations/members section */}
@parser::baselistenerdefinitions {/* base listener definitions section */}

@parser::visitorpreinclude {/* visitor preinclude section */}
@parser::visitorpostinclude {/* visitor postinclude section */}
@parser::visitordeclarations {/* visitor public declarations/members section */}
@parser::visitormembers {/* visitor private declarations/members section */}
@parser::visitordefinitions {/* visitor definitions section */}

@parser::basevisitorpreinclude {/* base visitor preinclude section */}
@parser::basevisitorpostinclude {/* base visitor postinclude section */}
@parser::basevisitordeclarations {/* base visitor public declarations/members section */}
@parser::basevisitormembers {/* base visitor private declarations/members section */}
@parser::basevisitordefinitions {/* base visitor definitions section */}

// Actual grammar start.
prog: (stm | vardec | procdec)+;

stm: expr
   | Identifier Assign expr
   | vardec Assign expr
   | If expr Colon stm+
   | If expr Colon stm+ Else Colon stm+
   | While expr Colon stm+
   | While expr Star Colon stm+
   | Break
   | Return
   | Return expr
   | Replace expr With expr;

expr: OpenPar expr ClosePar
    //| arthexpr
    //| boolexpr
    | Identifier
    | Identifier OpenSquare expr CloseSquare
    | Identifier OpenPar args ClosePar
    | expr (Plus | Minus | Star | Slash | Mod) expr
    | Not expr
    | expr (And | Or | Equal | Less | Greater | LessEqual | GreaterEqual) expr
    | literal;

literal: Float 
     | Integer
     | Bool
     | String
     | None;


//arthexpr: expr (Plus | Minus | Star | Slash | Mod) expr;

//boolexpr: Not expr
//        | expr (And | Or | Equal | Less | Greater | LessEqual | LessEqual) expr;

procdec: Def Identifier OpenPar args ClosePar Colon stm+
       | Def Identifier OpenPar args ClosePar Arrow Colon stm+;

vardec: Identifier
      | Identifier Assign expr;

args: (expr (Comma expr)*)?;