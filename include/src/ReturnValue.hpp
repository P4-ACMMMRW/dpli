#ifndef RETURNVALUE_HPP
#define RETURNVALUE_HPP

#include <exception>
#include "Value.hpp"

namespace dplsrc {
    // Not really a exception just abusing try/catch mechanism, and therefore does not derive from DplException
    class ReturnValue : public std::exception {
            public:
                ReturnValue(Value val) : val(val) {}
                Value getVal() const { return val; }
            private:
                Value val;
    };
}

#endif