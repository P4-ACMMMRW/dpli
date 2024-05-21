#ifndef PARSEREXCEPTION_HPP
#define PARSEREXCEPTION_HPP

#include "RuntimeException.hpp"

namespace dplsrc {
class ParserException : public RuntimeException {
   public:
    ParserException(std::string msg) : RuntimeException(msg) {
        this->msg = msg.insert(0, "Parser Error: ");
    }
};
}  // namespace dplsrc

#endif