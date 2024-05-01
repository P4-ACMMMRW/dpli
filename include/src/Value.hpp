#ifndef VALUE_HPP
#define VALUE_HPP

#include <stdexcept>
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

    /**
     * Prints string representation of value
     */
    std::string toString() const;

    /**
     * List value type
     */
    using List = std::vector<Value>;

   private:
    std::variant<int, double, std::string, bool, List, std::nullptr_t> innerValue;
};
}  // namespace dplsrc

#endif