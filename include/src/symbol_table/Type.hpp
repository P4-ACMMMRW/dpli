#ifndef TYPE_HPP
#define TYPE_HPP

#include <ostream>

namespace dplsrc {
/**
 * Strong enum class to represent the type of a variable
 */
enum class Type {
    INT,
    FLOAT,
    STR,
    LIST,
    BOOL,
    TABLE,
    NONETYPE,
};

class TypeUtil {
   public:
    static std::string typeToString(Type type);
};

// String to bool
bool stob(const std::string& input) { return input != "False"; }

// Overload << operator so we can print the enum string for debugging
std::ostream& operator<<(std::ostream& os, const Type& type);
}  // namespace dplsrc

#endif