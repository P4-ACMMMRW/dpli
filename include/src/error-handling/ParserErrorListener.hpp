#ifndef PARSERERRORLISTENER_HPP
#define PARSERERRORLISTENER_HPP

#include <antlr4-runtime.h>

#include "ParserException.hpp"

namespace dplsrc {
class ParserErrorListener : public antlr4::BaseErrorListener {
   public:
    ParserErrorListener(std::string filename) : filename(filename) {}
    void syntaxError([[maybe_unused]] antlr4::Recognizer *recognizer,
                     [[maybe_unused]] antlr4::Token *offendingSymbol, size_t line,
                     size_t charPositionInLine, const std::string &msg,
                     [[maybe_unused]] std::exception_ptr e) override {
        std::string exceptionMsg = msg + " in " + filename + " (" + std::to_string(line) + ":" +
                                   std::to_string(charPositionInLine) + ")";
        throw ParserException(exceptionMsg);
    }

   private:
    std::string filename;
};
}  // namespace dplsrc

#endif