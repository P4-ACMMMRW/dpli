#ifndef DPLEXCEPTION_HPP
#define DPLEXCEPTION_HPP

#include <string>
#include <utility>

namespace dplsrc {
// Base class for all exceptions
class DplException : public std::exception {
   public:
    ~DplException() override = default;

    DplException(std::string msg) : msg(std::move(msg)) {}
    const char *what() const noexcept override { return msg.c_str(); }

   protected:
    std::string msg;
};
}  // namespace dplsrc

#endif