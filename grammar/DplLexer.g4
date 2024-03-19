lexer grammar DplLexer;

// Keywords
If: 'if';
Else: 'else';
While: 'while';
Break: 'break';
Continue: 'continue';
Return: 'return';
Def: 'def';
Replace: 'replace';
With: 'with';

// Type declarations
IntType: 'int';
FloatType: 'float';
BoolType: 'bool';
StringType: 'str';
ListType: 'list';
TableType: 'table';

// Symbols
OpenPar: '(';
ClosePar: ')';
OpenCurly: '{';
CloseCurly: '}';
OpenSquare: '[';
CloseSquare: ']';
Colon: ':';
Comma: ',';
Arrow: '->';

// Operators
Plus: '+';
Minus: '-';
Star: '*';
Slash: '/';
Mod: '%';
Equal: '==';
NotEqual: '!=';
Less: '<';
LessEqual: '<=';
Greater: '>';
GreaterEqual: '>=';
And: 'and';
Or: 'or';
Not: 'not';
Assign: '=';

// Types
fragment DIGIT: [0-9];
fragment ALPHA: [a-zA-Z];
fragment ALPHANUM: [a-zA-Z0-9];
Identifier: ALPHA ALPHANUM*;
Integer: DIGIT+;
Float: DIGIT+ '.' DIGIT+;
Bool: 'true' | 'false';
String: '"' ~["\r\n]* '"';
None: 'None';

// Ignore
Comment: '//' ~[\r\n]* -> skip;
MultiLineComment: '/*' .*? '*/' -> skip;
Whitespace: [ \t\r\n]+ -> skip;