lexer grammar DplLexer;

tokens {
    Indent,
    Dedent
}

@lexer::header {
    #include <queue>
}

@lexer::members {
    /**
    * Starts by pushing 0 onto the stack.
    * Calculate the indentation of the current line if EOF is set to 0 to add remaining dedent tokens
    * If current lines indentation > top of the stack, push it onto the stack and add an indent token
    * Else if the current lines indentation is < top of the stack, pop the stack and add dedent tokens until indentation >= top of the stack. 
    */
    void addDentTokens() {
        if (indentLevels.empty()) {
            indentLevels.push(0);
        }

        int indent = _input->LA(1) == EOF ? 0 : getIndentation();

        if (indent > indentLevels.top()) {
            indentLevels.push(indent);
            pendingTokens.push(_factory->create({ this, _input }, Indent, "Indent", channel, tokenStartCharIndex, getCharIndex() - 1, tokenStartLine, tokenStartCharPositionInLine));
        } else if (indent < indentLevels.top()) {
            while (indent < indentLevels.top()) {
                indentLevels.pop();
                pendingTokens.push(_factory->create({ this, _input }, Dedent, "Dedent", channel, tokenStartCharIndex, getCharIndex() - 1, tokenStartLine, tokenStartCharPositionInLine));
            }
        }
    }

    /**
    * Returns the next token in the queue if not empty
    * Otherwise, get next token from lexer and add it to the queue
    * If the queue is still empty, return the token otherwise return the next token in the queue
    */
    std::unique_ptr<antlr4::Token> nextToken() override {
        if (pendingTokens.empty()) {
            std::unique_ptr<antlr4::Token> next = antlr4::Lexer::nextToken();
            if (pendingTokens.empty()) {
                return next;
            }

            pendingTokens.push(std::move(next));
        }

        std::unique_ptr<antlr4::Token> token = std::move(pendingTokens.front());
        pendingTokens.pop();

        return token;
    }
}

@lexer::declarations {
    std::stack<int> indentLevels;
    std::queue<std::unique_ptr<antlr4::Token>> pendingTokens;

    /**
    * Calculate indentation of current line
    */
    int getIndentation() {
        int length = 0;
        int i = 1;

        // Increment by 1 if space or 8 if tab
        while (_input->LA(i) == ' ' || _input->LA(i) == '\t') {
            length += _input->LA(i) == ' ' ? 1 : 8;
            ++i;
        }

        return length;
    }
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