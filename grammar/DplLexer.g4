lexer grammar DplLexer;

tokens {
    Indent,
    Dedent
}

@lexer::members {
    void addDentTokens(bool isEOF = false) {
        if (indentLevels.empty()) {
            indentLevels.push(0);
        }

        int indent = _input->LA(1) == EOF ? 0 : getIndentation();

        if (indent > indentLevels.top()) {
            std::cout << "add indent\n";
            indentLevels.push(indent);
        } else if (indent < indentLevels.top()) {
            while (indent < indentLevels.top()) {
                indentLevels.pop();
                std::cout << "add dedent\n";
            }

        }    
    }

    int getIndentation() {
        int length = 0;
        int i = 1;

        // Increment by 1 if space or 8 if tab
        while (_input->LA(i) == ' ' || _input->LA(i) == '\t') {
            length += _input->LA(i) == ' ' ? 1 : 8;
            ++i;
        }

        std::cout << "length: " << length << '\n';

        return length;
    }
}

@lexer::declarations {
    std::stack<int> indentLevels;
}

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

// Symbols
OpenPar: '(';
ClosePar: ')';
OpenCurly: '{';
CloseCurly: '}';
OpenSquare: '[';
CloseSquare: ']';
Colon: ':';
Comma: ',';

// Operators
Exponent: '**';
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
Bool: 'True' | 'False';
String: '"' ~["\r\n]* '"';
None: 'None';

// Comments
Comment: '#' ~[\r\n]* -> skip;
MultiLineComment: '/*' .*? '*/' -> skip;

Newline: '\r'? '\n' { addDentTokens(); } -> skip;
Space: [ \t] -> skip;