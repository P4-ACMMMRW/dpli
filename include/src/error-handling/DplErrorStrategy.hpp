#ifndef DPLERRORSTRATEGY_HPP
#define DPLERRORSTRATEGY_HPP

#include <antlr4-runtime.h>

namespace dplsrc {
    class DplErrorStrategy : public antlr4::BailErrorStrategy {
        public:
            // Same behavior but with a different message
            void reportNoViableAlternative(antlr4::Parser *recognizer, const antlr4::NoViableAltException &e) override {
                antlr4::TokenStream *tokens = recognizer->getTokenStream();
                std::string input;
                if (tokens != nullptr) {
                    if (e.getStartToken()->getType() == antlr4::Token::EOF) {
                    input = "<EOF>";
                    } else {
                    input = tokens->getText(e.getStartToken(), e.getOffendingToken());
                    }
                } else {
                    input = "<unknown input>";
                }

                std::string msg = "no viable alternative to input " + escapeWSAndQuote(input);
                recognizer->notifyErrorListeners(e.getOffendingToken(), msg, std::make_exception_ptr(e));
            }
    };
}

#endif