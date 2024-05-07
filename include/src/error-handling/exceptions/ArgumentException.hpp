#ifndef ARGUMENTEXCEPTION_HPP
#define ARGUMENTEXCEPTION_HPP

#include <string>

#include "RuntimeException.hpp"

namespace dplsrc {
    // Exception class for invalid arguments
    class ArgumentException : public RuntimeException {
        public:
            ArgumentException(std::string msg) : RuntimeException(msg) {
                this->msg = msg.insert(0, "Argument Error: ");
            }
    };
}

#endif