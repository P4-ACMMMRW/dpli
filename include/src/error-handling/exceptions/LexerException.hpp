#ifndef LEXEREXCEPTION_HPP
#define LEXEREXCEPTION_HPP

#include "RuntimeException.hpp"

namespace dplsrc {
class LexerException : public RuntimeException {
   public:
    LexerException(std::string msg) : RuntimeException(msg) {
        this->msg = msg.insert(0, "Lexer Error: ");
    }
};
}  // namespace dplsrc

#endif