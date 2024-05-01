#include "Type.hpp"

using namespace dplsrc;

std::string Type::toString(bool verbose) const {
    if (is<Primitive>()) {
        switch (get<Primitive>()) {
            case Primitive::INT:
                return "int";
            case Primitive::FLOAT:
                return "float";
            case Primitive::STR:
                return "str";
            case Primitive::BOOL:
                return "bool";
            case Primitive::NONETYPE:
                return "NoneType";
        }
    } else if (is<List>()) {
        if (!verbose) {
            return "list";
        }

        std::string result = "list -> [";
        const List& listType = get<List>();
        for (size_t i = 0; i < listType.size(); ++i) {
            result += listType[i].toString() + ", ";
        }

        if (listType.size() > 1) {
            result.pop_back();
            result.pop_back();
        }

        result += "]";
        return result;
    }

    throw std::runtime_error("Error: unknown type cannot be converted to string");
}