#include "Type.hpp"

using namespace dplsrc;

std::ostream& dplsrc::operator<<(std::ostream& os, const Type& type) {
    switch (type) {
        case Type::INT:
            os << "int";
            break;
        case Type::FLOAT:
            os << "float";
            break;
        case Type::STR:
            os << "str";
            break;
        case Type::LIST:
            os << "list";
            break;
        case Type::BOOL:
            os << "bool";
            break;
        case Type::TABLE:
            os << "table";
            break;
        case Type::NONETYPE:
            os << "NoneType";
            break;
    }

    return os;
}

std::string TypeUtil::typeToString(Type type) {
    switch (type) {
        case Type::INT:
            return "int";
        case Type::FLOAT:
            return "float";
        case Type::STR:
            return "str";
        case Type::LIST:
            return "list";
        case Type::BOOL:
            return "bool";
        case Type::TABLE:
            return "table";
        case Type::NONETYPE:
            return "NoneType";
        default:
            return "";
    }
}