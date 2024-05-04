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
     * Set the inner value
     */
    template <typename T>
    Value(const T &innerValue) : innerValue(innerValue) {}

    /**
     * Check if the value is of type T
     */
    template <typename T>
    bool is() const {
        return std::holds_alternative<T>(innerValue);
    }

    /**
     * Get the value as type T read-only
     */
    template <typename T>
    const T &get() const {
        return std::get<T>(innerValue);
    }

    /**
     * Get the value as type T mutable
     */
    template <typename T>
    T &getMut() {
        return std::get<T>(innerValue);
    }

    /**
     * @return String representation of value
     */
    std::string toString() const;

    /** 
     * @param Whether expand types of composite types
     * @return String representation of type 
     */
    std::string toTypeString(bool verbose = false) const;

    /**
     * DPL Types
     */
    using INT = long;
    using FLOAT = double;
    using BOOL = bool;
    using STR = std::string;
    using NONETYPE = std::nullptr_t;
    using LIST = std::vector<Value>;

   private:
    mutable std::variant<INT, FLOAT, STR, BOOL, LIST, NONETYPE> innerValue;
};
}  // namespace dplsrc

#endif