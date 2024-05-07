#ifndef DPLEXCEPTION_HPP
#define DPLEXCEPTION_HPP

#include <string>

namespace dplsrc {
    class DplException : public std::exception {
        public:
            DplException(std::string msg) : msg("Evaluation Error: " + msg) {}
            const char *what() const noexcept override {
                return msg.c_str();
            }
        private:
            std::string msg;
    };
}

#endif