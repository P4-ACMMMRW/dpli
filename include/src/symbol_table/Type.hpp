#ifndef TYPE_HPP
#define TYPE_HPP

#include <ostream>

namespace dplsrc {
enum Type {
    INT,
    FLOAT,
    STR,
    LIST,
    BOOL,
    TABLE,
    NONETYPE,
};
// Overload << operator so we can print the enum string for debugging
std::ostream& operator<<(std::ostream& os, const Type& type);
}  // namespace dplsrc

#endif