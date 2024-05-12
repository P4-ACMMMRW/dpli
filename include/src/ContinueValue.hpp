#ifndef CONTINUEVALUE_HPP
#define CONTINUEVALUE_HPP

#include <exception>

namespace dplsrc {
// Not really a exception just abusing try/catch mechanism, and therefore does not derive from
// DplException
class ContinueValue : public std::exception {
   public:
    ContinueValue() {}
};
}  // namespace dplsrc

#endif