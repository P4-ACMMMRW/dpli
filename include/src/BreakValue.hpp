#ifndef BREAKVALUE_HPP
#define BREAKVALUE_HPP

#include <exception>

namespace dplsrc {
    // Not really a exception just abusing try/catch mechanism, and therefore does not derive from DplException
    class BreakValue : public std::exception {
            public:
                BreakValue() {}
    };
}

#endif