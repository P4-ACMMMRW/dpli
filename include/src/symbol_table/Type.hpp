#ifndef TYPE_HPP
#define TYPE_HPP

#include <unordered_map>
#include <ostream>

namespace dplsrc {
enum Type {
        UNKNOWN,
        INT,
        FLOAT,
        STR,
        LIST,
        BOOL,
        TABLE,
        NONETYPE,
};

// Overload << operator so we can print the enum string for debugging
std::ostream& operator<<(std::ostream& os, Type type);
}


#endif