#ifndef INTERNALEXCEPTION_HPP
#define INTERNALEXCEPTION_HPP

#include "DplException.hpp"

namespace dplsrc {
    // Exception class for internal errors in the interpreter
    class InternalException : public DplException {
        public:
            InternalException(std::string msg) : DplException(msg) {
                this->msg = msg.insert(0, "Internal Error: ");
            }
    };
}

#endif