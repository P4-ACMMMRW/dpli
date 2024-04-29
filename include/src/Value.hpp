#ifndef VALUE_HPP
#define VALUE_HPP

#include <string>
#include <variant>
#include <vector>

namespace dplsrc {
class Value {
   public:
    /**
     * Default constructor
     */
    Value() = default;

    /**
     * Generic constructor
     */
    template <typename T>
    Value(const T &value) : innerValue(value) {}

    /**
     * Check if the value is of type T
     */
    template <typename T>
    bool is() const {
        return std::holds_alternative<T>(innerValue);
    }

    /**
     * Get the value as type T
     */
    template <typename T>
    const T &get() const {
        return std::get<T>(innerValue);
    }

    std::string toString() const {
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
                result.pop_back();
                result.pop_back();
            }

            result += "]";

            return result;
        }

        throw std::runtime_error("Error: unknown value type");
    }

   private:
    using List = std::vector<Value>;
    std::variant<int, double, std::string, bool, List, std::nullptr_t> innerValue;
};
}  // namespace dplsrc

#endif