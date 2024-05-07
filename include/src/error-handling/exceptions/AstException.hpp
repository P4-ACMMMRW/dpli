#ifndef ASTEXCEPTION_HPP
#define ASTEXCEPTION_HPP

#include "InternalException.hpp"

namespace dplsrc {
    class AstException : public InternalException {
        public:
            AstException(std::string msg) : InternalException(msg) {
                this->msg = msg.insert(0, "AST Error: ");
            }
    };
}

#endif