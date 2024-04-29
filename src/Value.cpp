#include "Value.hpp"

using namespace dplsrc;

std::string Value::toString() const {
    if (is<int>()) {
        return std::to_string(get<int>());
    } else if (is<double>()) {
        return std::to_string(get<double>());
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
