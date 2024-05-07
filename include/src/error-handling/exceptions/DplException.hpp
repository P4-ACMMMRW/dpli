#ifndef DPLEXCEPTION_HPP
#define DPLEXCEPTION_HPP

#include <string>

namespace dplsrc {
    // Base class for all exceptions
    class DplException : public std::exception {
        public:
            virtual ~DplException() = default;

            DplException(std::string msg) : msg(msg) {}
            const char *what() const noexcept override {
                return msg.c_str();
            }

        private:
            std::string msg;
    };
}

#endif