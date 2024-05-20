#ifndef VALUE_HPP
#define VALUE_HPP

#include <cmath>
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>
#include <iostream>
#include <utility>

#include "InternalException.hpp"
#include "RuntimeException.hpp"

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
    Value(const T& innerValue) : innerValue(innerValue) {}

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
    const T& get() const {
        return std::get<T>(innerValue);
    }

    /**
     * Get the value as type T mutable
     */
    template <typename T>
    T& getMut() {
        return std::get<T>(innerValue);
    }

    /**
     * @return true if the value is a number
     */
    bool isNumeric() const { return is<Value::FLOAT>() || is<Value::INT>() || is<Value::BOOL>(); }

    /**
     * @return the double representation of the  numeric Value, if not Numeric 0.0.
     */
    double getNumericValue() const;

    /**
     * @return True under the following conditions:
     *         - if val is numeric and is not 0.0,
     *         - if val is a string and is not empty,
     *         - if val is a list and is not empty,
     *         - if val is column and is not empty,
     *         - if val is a table and is not empty,
     */
    bool getBoolValue() const;

    /**
     * @return String representation of value
     */
    std::string toString() const;

    /**
     * @param Whether expand types of composite types
     * @return String representation of type
     */
    std::string toTypeString(bool verbose = false) const;

    // Operator overloadings
    // Bools
    // Binary
    bool operator==(const Value& other) const;
    bool operator!=(const Value& other) const;
    bool operator<(const Value& other) const;
    bool operator>(const Value& other) const;
    bool operator<=(const Value& other) const;
    bool operator>=(const Value& other) const;

    // Unary
    bool operator!() const;

    // Arthmetic
    // Binary
    Value operator+(const Value& other) const;
    Value operator-(const Value& other) const;
    Value operator*(const Value& other) const;
    Value operator/(const Value& other) const;
    Value operator%(const Value& other) const;
    Value pow(const Value& other) const;

    // Unary
    Value operator-() const;

    // Logical
    Value operator&&(const Value& other) const;
    Value operator||(const Value& other) const;

    /**
     * DPL Types
     */
    using INT = long;
    using FLOAT = double;
    using BOOL = bool;
    using STR = std::string;
    using NONETYPE = std::nullptr_t;
    using LIST = std::shared_ptr<std::vector<std::shared_ptr<Value>>>;
    struct COL_STRUCT;
    using COLUMN = std::shared_ptr<COL_STRUCT>;
    using TABLE = std::shared_ptr<std::map<STR, COLUMN>>;
    struct COL_STRUCT {
        TABLE parent;
        STR header;
        LIST data;
    };

   private:
    mutable std::variant<INT, FLOAT, STR, BOOL, NONETYPE, LIST, TABLE, COLUMN> innerValue;

    /**
     * @return the result of the operation on the columns, if not a valid column operation None
     * (Value(nullptr)) is returned.
     */
    static Value colOperations(const Value& val1, const Value& val2,
                               const std::function<Value(Value, Value)>& op);
};
}  // namespace dplsrc

#endif