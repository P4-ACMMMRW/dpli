#include "Type.hpp"

namespace dplsrc {
std::ostream& operator<<(std::ostream& os, const Type& type) {
    switch (type) {
        case Type::UNKNOWN:
            os << "UNKNOWN";
            break;
        case Type::INT:
            os << "INT";
            break;
        case Type::FLOAT:
            os << "FLOAT";
            break;
        case Type::STR:
            os << "STR";
            break;
        case Type::LIST:
            os << "LIST";
            break;
        case Type::BOOL:
            os << "BOOL";
            break;
        case Type::TABLE:
            os << "TABLE";
            break;
        case Type::NONETYPE:
            os << "NONETYPE";
            break;
    }

    return os;
}
}  // namespace dplsrc