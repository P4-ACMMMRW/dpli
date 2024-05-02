#include "Value.hpp"

using namespace dplsrc;

std::string Value::toString() const {
    if (is<long>()) {
        return std::to_string(get<long>());
    } else if (is<double>()) {
        std::string doubleStr = std::to_string(get<double>());

        // Remove trailing zeros
        doubleStr.erase(doubleStr.find_last_not_of('0') + 1, std::string::npos);

        // If the last character is a decimal point, add a zero to make it obvious that it's a
        // floating point number
        if (doubleStr.back() == '.') {
            doubleStr.push_back('0');
        }

        return doubleStr;
    } else if (is<std::string>()) {
        return get<std::string>();
    } else if (is<bool>()) {
        return get<bool>() ? "True" : "False";
    } else if (is<std::nullptr_t>()) {
        return "None";
    } else if (is<List>()) {
        std::string result = "[";

        for (const Value &elem : get<List>()) {
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
