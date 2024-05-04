#include "Value.hpp"

using namespace dplsrc;
#include <iostream>
std::string Value::toString() const {
    if (is<INT>()) {
        return std::to_string(get<long>());
    } else if (is<FLOAT>()) {
        std::string doubleStr = std::to_string(get<double>());

        // Remove trailing zeros
        doubleStr.erase(doubleStr.find_last_not_of('0') + 1, std::string::npos);

        // If the last character is a decimal point, add a zero to make it obvious that it's a
        // floating point number
        if (doubleStr.back() == '.') {
            doubleStr.push_back('0');
        }

        return doubleStr;
    } else if (is<STR>()) {
        return get<STR>();
    } else if (is<BOOL>()) {
        return get<BOOL>() ? "True" : "False";
    } else if (is<NONETYPE>()) {
        return "None";
    } else if (is<LIST>()) {
        std::string result = "[";

        for (const Value &elem : get<LIST>()) {
            result += elem.toString() + ", ";
        }

        // Remove trailing comma and space
        if (result.size() > 1) {
            result.erase(result.size() - 2);
        }

        result += "]";

        return result;
    }

    throw std::runtime_error("Error: unknown value type");
}

std::string Value::toTypeString(bool verbose) const {
    if (is<INT>()) {
        return "int";
    } else if (is<FLOAT>()) {
        return "double";
    } else if (is<STR>()) {
        return "str";
    } else if (is<BOOL>()) {
        return "bool";
    } else if (is<NONETYPE>()) {
        return "NoneType";
    } else if (is<LIST>()) {
        if (!verbose) return "list";

        std::string listStr = "list -> [";
        Value::LIST list = get<LIST>();
        for (Value val : list) {
            listStr += val.toTypeString(true) + ", ";
        }

        if (list.size() > 1) {
            listStr.pop_back();
            listStr.pop_back();
        }

        listStr += "]";

        return listStr;
    }

    throw std::runtime_error("Error: unknown type cannot be converted to a string");
}