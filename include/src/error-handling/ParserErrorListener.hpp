#ifndef PARSERERRORLISTENER_HPP
#define PARSERERRORLISTENER_HPP

#include <antlr4-runtime.h>

namespace dplsrc {
class ParserErrorListener : public antlr4::BaseErrorListener {
   public:
    ParserErrorListener(std::string filename) : filename(filename) {}
    void syntaxError([[maybe_unused]] antlr4::Recognizer *recognizer,
                     [[maybe_unused]] antlr4::Token *offendingSymbol, size_t line,
                     size_t charPositionInLine, const std::string &msg,
                     [[maybe_unused]] std::exception_ptr e) override {
        std::cerr << "Parser Error: " << msg << " in " << filename << " (" << line << ":"
                  << charPositionInLine << ")\n";
    }

   private:
    std::string filename;
};
}  // namespace dplsrc

#endif