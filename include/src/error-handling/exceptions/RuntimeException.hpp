#ifndef RUNTIMEEXCEPTION_HPP
#define RUNTIMEEXCEPTION_HPP

#include "DplException.hpp"

namespace dplsrc {
// Exception class for all runtime errors
class RuntimeException : public DplException {
   public:
    RuntimeException(std::string msg) : DplException(msg) {
        this->msg = msg.insert(0, "Runtime Error: ");
    }
};
}  // namespace dplsrc

#endif