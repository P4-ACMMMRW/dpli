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

#include "InternalException.hpp"

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
    bool isNumeric() const {
        return is<Value::FLOAT>() || is<Value::INT>() || is<Value::BOOL>();
    }

     /**
     * @return the double representation of the  numeric Value, if not Numeric 0.0.
     */
    double getNumericValue() const;


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
    bool operator==(const Value& other) const;
    bool operator!=(const Value& other) const;
    bool operator<(const Value& other) const;
    bool operator>(const Value& other) const;
    bool operator<=(const Value& other) const;
    bool operator>=(const Value& other) const;

    // Arthmetic
    Value operator+(const Value& other) const;
    Value operator-(const Value& other) const;
    Value operator*(const Value& other) const;
    Value operator/(const Value& other) const;
    Value operator%(const Value& other) const;
    Value pow(const Value& other) const;

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
     * @param leftTable
     * @param rightTable
     * @return true if the tables have the same columns
     */
    static bool isSameColumns(const Value::TABLE& leftTable, const Value::TABLE& rightTable);

    /**
     * @param leftTable
     * @param rightTable
     * @return a coloumn corresponding to the header in the given table, if no hit nullptr.
     */
    static Value::COLUMN getColumnByHeader(const Value::TABLE& table, const std::string& header);

    /**
     * Inserts a new column into the given table
     */
    static void insertColInTable(const Value::TABLE& table, const std::string& header,
                                 Value::LIST list);

    /**
     * @return Value resulting from a binary operator on this and other
     */
    Value binaryOperator(const Value& other, const std::string& errOpWord,
                         const std::function<Value(Value, Value)>& op) const;
};
}  // namespace dplsrc

#endif