#ifndef LEXERERRORLISTENER_HPP
#define LEXERERRORLISTENER_HPP

#include <antlr4-runtime.h>

#include "LexerException.hpp"

namespace dplsrc {
class LexerErrorListener : public antlr4::BaseErrorListener {
   public:
    LexerErrorListener(std::string filename) : filename(filename) {}
    void syntaxError([[maybe_unused]] antlr4::Recognizer *recognizer,
                     [[maybe_unused]] antlr4::Token *offendingSymbol, size_t line,
                     size_t charPositionInLine, const std::string &msg,
                     [[maybe_unused]] std::exception_ptr e) override {
        // Not the best way to get the invalid token but unsure where in antlr this method is called
        // from in the lexer
        std::string invalidToken = msg.substr(msg.find_first_of('\''), msg.find_last_of('\''));
        std::string exceptionMsg = "invalid token " + invalidToken + " in " + filename + " (" +
                                   std::to_string(line) + ":" + std::to_string(charPositionInLine) +
                                   ")";
        // antlr does not really make a nice way to stop the lexer from continuing to run
        // so we throw an exception
        throw LexerException(exceptionMsg);
    }

   private:
    std::string filename;
};
}  // namespace dplsrc

#endif