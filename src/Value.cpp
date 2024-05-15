#include "Value.hpp"

using namespace dplsrc;
#include <iostream>
#include <utility>
std::string Value::toString() const {
    if (is<INT>()) {
        return std::to_string(get<long>());
    }
    if (is<FLOAT>()) {
        std::string doubleStr = std::to_string(get<double>());

        // Remove trailing zeros
        doubleStr.erase(doubleStr.find_last_not_of('0') + 1, std::string::npos);

        // If the last character is a decimal point, add a zero to make it obvious that it's a
        // floating point number
        if (doubleStr.back() == '.') {
            doubleStr.push_back('0');
        }

        return doubleStr;
    }
    if (is<STR>()) {
        return get<STR>();
    }
    if (is<BOOL>()) {
        return get<BOOL>() ? "True" : "False";
    }
    if (is<NONETYPE>()) {
        return "None";
    }
    if (is<LIST>()) {
        std::string result = "[";
        bool addedSomething = false;
        for (const std::shared_ptr<Value>& elem : *get<LIST>()) {
            if (elem->is<STR>()) {
                result += "'" + elem->toString() + "', ";
            } else {
                result += elem->toString() + ", ";
            }
            addedSomething = true;
        }

        // Remove trailing comma and space
        if (addedSomething) {
            result.pop_back();
            result.pop_back();
        }

        result += "]";

        return result;
    }
    if (is<TABLE>()) {
        std::string result = "{ ";
        bool addedSomething = false;
        for (const std::pair<const std::string, Value::COLUMN>& entry : *get<TABLE>()) {
            result += static_cast<Value>(entry.second).toString() + ", ";
            addedSomething = true;
        }

        // Remove trailing comma and space
        if (addedSomething) {
            result.pop_back();
            result.pop_back();
        }

        result += " }";

        return result;
    }
    if (is<COLUMN>()) {
        std::string result =
            static_cast<Value>("'" + get<COLUMN>()->header).toString() + "'" + ": [";
        bool addedSomething = false;
        for (const std::shared_ptr<Value>& valPtr : *get<COLUMN>()->data) {
            if (valPtr->is<STR>()) {
                result += "'" + valPtr->toString() + "', ";
            } else {
                result += valPtr->toString() + ", ";
            }
            addedSomething = true;
        }

        // Remove trailing comma and space
        if (addedSomething) {
            result.pop_back();
            result.pop_back();
        }

        result += "]";

        return result;
    }

    throw InternalException("Unknown value type");
}

std::string Value::toTypeString(bool verbose) const {
    if (is<INT>()) {
        return "int";
    }
    if (is<FLOAT>()) {
        return "float";
    }
    if (is<STR>()) {
        return "str";
    }
    if (is<BOOL>()) {
        return "bool";
    }
    if (is<NONETYPE>()) {
        return "NoneType";
    }
    if (is<LIST>()) {
        if (!verbose) { return "list";
}

        std::string listStr = "list -> [";
        Value::LIST list = get<LIST>();
        for (const std::shared_ptr<Value>& elem : *list) {
            listStr += elem->toTypeString(verbose) + ", ";
        }

        // Remove trailing comma and space
        if (list->size() > 1) {
            listStr.pop_back();
            listStr.pop_back();
        }

        listStr += "]";

        return listStr;
    }
    if (is<TABLE>()) {
        if (!verbose) { return "table";
}

        std::string tableStr = "table -> { ";
        Value::TABLE table = get<TABLE>();
        for (const std::pair<const std::string, Value::COLUMN>& entry : *table) {
            tableStr += "{ " + static_cast<Value>(entry.second).toTypeString(verbose) + ", ";
        }

        // Remove trailing comma and space
        if (table->size() > 1) {
            tableStr.pop_back();
            tableStr.pop_back();
        }

        tableStr += "} ";

        return tableStr;
    }
    if (is<COLUMN>()) {
        if (!verbose) { return "column";
}

        std::string result =
            "column -> " + static_cast<Value>(get<COLUMN>()->header).toTypeString(verbose) + ": [";

        for (const std::shared_ptr<Value>& valPtr : *get<COLUMN>()->data) {
            result += valPtr->toTypeString(verbose) + ", ";
        }

        // Remove trailing comma and space
        if (result.size() > 1) {
            result.pop_back();
            result.pop_back();
        }

        result += "]";

        return result;
    }

    throw InternalException("Unknown type cannot be converted to a string");
}

bool Value::operator==(const Value& other) const {
    if ((is<INT>() || is<FLOAT>() || is<BOOL>()) &&
        (other.is<INT>() || other.is<FLOAT>() || other.is<BOOL>())) {
        Value::FLOAT val1 = is<INT>()
                                ? get<INT>()
                                : (is<FLOAT>() ? get<FLOAT>() : static_cast<double>(get<BOOL>()));
        Value::FLOAT val2 =
            other.is<INT>()
                ? other.get<INT>()
                : (other.is<FLOAT>() ? other.get<FLOAT>() : static_cast<double>(other.get<BOOL>()));
        return val1 == val2;
    }
    if (is<STR>() && other.is<STR>()) {
        return get<STR>() == other.get<STR>();
    }
    if (is<NONETYPE>() && other.is<NONETYPE>()) {
        return true;
    }
    if (is<LIST>() && other.is<LIST>()) {
        Value::LIST list1 = get<LIST>();
        const Value::LIST& list2 = other.get<LIST>();

        if (list1->size() != list2->size()) { return false;
}

        for (size_t i = 0; i < list1->size(); ++i) {
            if (*(*list1)[i] != *(*list2)[i]) { return false;
}
        }

        return true;
    }
    if (is<COLUMN>() && other.is<COLUMN>()) {
        Value::COLUMN col1 = get<COLUMN>();
        const Value::COLUMN& col2 = other.get<COLUMN>();

        return Value(col1->data) == Value(col2->data);
    }
    if (is<TABLE>() && other.is<TABLE>()) {
        Value::TABLE table1 = get<TABLE>();
        const Value::TABLE& table2 = other.get<TABLE>();

        if (table1->size() != table2->size()) {
            return false;
        }

        for (const std::pair<const std::string, Value::COLUMN>& entry : *table1) {
            Value::COLUMN col = nullptr;
            try {
                col = table2->at(entry.first);
            } catch (const std::out_of_range& e) {
                return false;
            }

            if (Value(col) != Value(entry.second)) {
                return false;
            }
        }

        return true;
    }

    return false;
}

bool Value::operator!=(const Value& other) const { return !(*this == other); }

bool Value::operator<(const Value& other) const {
    if ((is<INT>() || is<FLOAT>() || is<BOOL>()) &&
        (other.is<INT>() || other.is<FLOAT>() || other.is<BOOL>())) {
        Value::FLOAT val1 = is<INT>()
                                ? get<INT>()
                                : (is<FLOAT>() ? get<FLOAT>() : static_cast<double>(get<BOOL>()));
        Value::FLOAT val2 =
            other.is<INT>()
                ? other.get<INT>()
                : (other.is<FLOAT>() ? other.get<FLOAT>() : static_cast<double>(other.get<BOOL>()));
        return val1 < val2;
    }
    if (is<STR>() && other.is<STR>()) {
        return get<STR>() < other.get<STR>();
    }
    if (is<NONETYPE>() && other.is<NONETYPE>()) {
        return false;
    }
    if (is<LIST>() && other.is<LIST>()) {
        Value::LIST list1 = get<LIST>();
        const Value::LIST& list2 = other.get<LIST>();

        size_t minSize = std::min(list1->size(), list2->size());

        for (size_t i = 0; i < minSize; ++i) {
            if (*(*list1)[i] != *(*list2)[i]) { return *(*list1)[i] < *(*list2)[i];
}
        }

        return list1->size() < list2->size();
    }
    if (is<COLUMN>() && other.is<COLUMN>()) {
        Value::COLUMN col1 = get<COLUMN>();
        const Value::COLUMN& col2 = other.get<COLUMN>();
        return Value(col1->data) < Value(col2->data);
    }
    if (is<TABLE>() && other.is<TABLE>()) {
        Value::TABLE table1 = get<TABLE>();
        const Value::TABLE& table2 = other.get<TABLE>();

        if (table1->size() != table2->size()) {
            return table1->size() < table2->size();
        }

        for (const std::pair<const std::string, Value::COLUMN>& entry : *table1) {
            if (entry.second != table2->at(entry.first)) {
                return entry.second < table2->at(entry.first);
            }
        }
    }

    return false;
}

bool Value::operator>(const Value& other) const { return other < *this; }

bool Value::operator<=(const Value& other) const { return *this < other || *this == other; }

bool Value::operator>=(const Value& other) const { return *this > other || *this == other; }

bool Value::operator!() const {
    if (is<INT>() || is<FLOAT>()) {
        return get<INT>() == 0; // not 0 == true
    }
    if (is<BOOL>()) {
        return !get<BOOL>(); // not False == True
    }
    if (is<STR>()) {
        return get<STR>().empty(); // not "" == true
    }
    if (is<LIST>()) {
        return get<LIST>()->empty(); // not [] == true
    }

    throw InternalException("Can not use NOT on this type");
}

Value Value::operator+(const Value& other) const {
    std::string errOpWord = "add";

    const std::function<Value(Value, Value)> op = [](const Value& val1,
                                                     const Value& val2) -> Value {
        if ((val1.is<INT>() || val1.is<BOOL>()) && (val2.is<INT>() || val2.is<BOOL>())) {
            Value::INT int1 = (val1.is<INT>()) ? val1.get<INT>() : val1.get<BOOL>();
            Value::INT int2 = (val2.is<INT>()) ? val2.get<INT>() : val2.get<BOOL>();

            return Value(int1 + int2);
        }
        if (val1.isNumeric() && val2.isNumeric()) {
            Value::FLOAT float1 = (val1.is<INT>())   ? val1.get<INT>() : 
                                  ((val1.is<BOOL>()) ? val1.get<BOOL>() : val1.get<FLOAT>());
            Value::FLOAT float2 = (val2.is<INT>())   ? val2.get<INT>() : 
                                  ((val2.is<BOOL>()) ? val2.get<BOOL>() : val2.get<FLOAT>());

            return Value(float1 + float2);
        }
        if (val1.is<STR>() && val2.is<STR>()) {
            return Value(val1.get<STR>() + val2.get<STR>());
        }
        if (val1.is<LIST>() && val2.is<LIST>()) {
            Value::LIST result = std::make_shared<std::vector<std::shared_ptr<Value>>>();
            
            Value::LIST list1 = val2.get<LIST>();
            Value::LIST list2 = val1.get<LIST>();

            for (const std::shared_ptr<Value>& elem : *list1) {
                result->push_back(elem);
            }
            for (const std::shared_ptr<Value>& elem : *list2) {
                result->push_back(elem);
            }

            return Value(result);
        }            
        throw InternalException("Cannot add values of type " + val1.toTypeString() +
                                    " and " + val2.toTypeString());
       
    };
    return Value::binaryOperator(other, errOpWord, op);
}

Value Value::operator-(const Value& other) const {
    std::string errOpWord = "detract";

    const std::function<Value(Value, Value)> op = [](const Value& val1,
                                                     const Value& val2) -> Value {

        if ((val1.is<INT>() || val1.is<BOOL>()) && (val2.is<INT>() || val2.is<BOOL>())) {
            Value::INT int1 = (val1.is<INT>()) ? val1.get<INT>() : val1.get<BOOL>();
            Value::INT int2 = (val2.is<INT>()) ? val2.get<INT>() : val2.get<BOOL>();

            return Value(int1 - int2);
        }
        if (val1.isNumeric() && val2.isNumeric()) {
            Value::FLOAT float1 = (val1.is<INT>())   ? val1.get<INT>() : 
                                  ((val1.is<BOOL>()) ? val1.get<BOOL>() : val1.get<FLOAT>());
            Value::FLOAT float2 = (val2.is<INT>())   ? val2.get<INT>() : 
                                  ((val2.is<BOOL>()) ? val2.get<BOOL>() : val2.get<FLOAT>());

            return Value(float1 - float2);
        }
        throw InternalException("Cannot detract values of type " + val1.toTypeString() +
                                " and " + val2.toTypeString());
    };
    return Value::binaryOperator(other, errOpWord, op);
}

Value Value::operator*(const Value& other) const {
    std::string errOpWord = "multiply";
    const std::function<Value(Value, Value)> op = [](const Value& val1,
                                                     const Value& val2) -> Value {

        bool isVal1Int = val1.is<INT>() || val1.is<BOOL>();
        bool isVal2Int = val2.is<INT>() || val2.is<BOOL>();
        
        if (isVal1Int && isVal2Int) {
            Value::INT int1 = (val1.is<INT>()) ? val1.get<INT>() : val1.get<BOOL>();
            Value::INT int2 = (val2.is<INT>()) ? val2.get<INT>() : val2.get<BOOL>();

            return Value(int1 * int2);
        }
        if (val1.isNumeric() && val2.isNumeric()) {
            Value::FLOAT float1 = (val1.is<INT>())   ? val1.get<INT>() : 
                                  ((val1.is<BOOL>()) ? val1.get<BOOL>() : val1.get<FLOAT>());
            Value::FLOAT float2 = (val2.is<INT>())   ? val2.get<INT>() : 
                                  ((val2.is<BOOL>()) ? val2.get<BOOL>() : val2.get<FLOAT>());

            return Value(float1 * float2);
        }
        if ((isVal1Int && val2.is<STR>()) ||
            (isVal2Int && val1.is<STR>())) {
            int intVal = 0;
            std::string strVal;

            if (val1.is<INT>() || val1.is<BOOL>()) {
                intVal = (val1.is<INT>()) ? val1.get<INT>() : static_cast<long>(val1.get<BOOL>());
                strVal = val2.get<STR>();
            } else {
                intVal = (val2.get<INT>()) != 0 ? val2.get<INT>() : static_cast<long>(val2.get<BOOL>());
                strVal = val1.get<STR>();
            }

            std::string resultStr;
            for (int i = 0; i < intVal; ++i) {
                resultStr += strVal;
            }
            return Value(resultStr);
        }
        if (((val1.is<INT>() || val1.is<BOOL>()) && val2.is<LIST>()) ||
            ((val2.is<INT>() || val2.is<BOOL>()) && val1.is<LIST>())) {
            Value::LIST result = std::make_shared<std::vector<std::shared_ptr<Value>>>();
            int intVal = 0;
            Value::LIST listVal;

            if (val1.is<INT>() || val1.is<BOOL>()) {
                intVal = (val1.is<INT>()) ? val1.get<INT>() : static_cast<long>(val1.get<BOOL>());
                listVal = val2.get<LIST>();
            } else {
                intVal = (val2.get<INT>()) != 0 ? val2.get<INT>() : static_cast<long>(val2.get<BOOL>());
                listVal = val1.get<LIST>();
            }

            for (int i = 0; i < intVal; ++i) {
                for (const std::shared_ptr<Value>& elem : *listVal) {
                    result->push_back(elem);
                }
            }

            return Value(result);
        }
        throw InternalException("Cannot multiply values of type " + val1.toTypeString()+ ": " + val1.toString() +
                                " and " + val2.toTypeString() + ": " + val2.toString());
    };
    return Value::binaryOperator(other, errOpWord, op);
}

Value Value::operator/(const Value& other) const {
    std::string errOpWord = "divide";
    const std::function<Value(Value, Value)> op = [](const Value& val1,
                                                     const Value& val2) -> Value {

        if (!val1.isNumeric() || !val2.isNumeric()) {
            throw InternalException("Cannot divide values of type " +
                                val1.toTypeString() + " and " + val2.toTypeString());
        }
        if ((val2.is<INT>()   && val2.get<INT>() == 0 )  ||
            (val2.is<FLOAT>() && val2.get<FLOAT>() == 0) ||
            (val2.is<BOOL>()  && val2.get<BOOL>() == 0)) {
            throw InternalException("Cannot take remainder of values with divisor 0");
        }
        if (!val1.is<FLOAT>() && !val2.is<FLOAT>()) {
            Value::INT int1 = (val1.is<INT>()) ? val1.get<INT>() : val1.get<BOOL>();
            Value::INT int2 = (val2.is<INT>()) ? val2.get<INT>() : val2.get<BOOL>();
            
            return Value::INT(int1 / int2);
        }
        auto float1 = (val1.is<INT>())   ? val1.get<INT>()   : 
                      (val1.is<FLOAT>()) ? val1.get<FLOAT>() : val1.get<BOOL>();

        auto float2 = (val2.is<INT>())   ? val2.get<INT>()   : 
                      (val2.is<FLOAT>()) ? val2.get<FLOAT>() : val2.get<BOOL>();

        return Value(float1 / float2);
    };
    return Value::binaryOperator(other, errOpWord, op);
}

Value Value::operator%(const Value& other) const {
    std::string errOpWord = "take remainder of";
    const std::function<Value(Value, Value)> op = [](const Value& val1,
                                                     const Value& val2) -> Value {

        if (!val1.isNumeric() || !val2.isNumeric()) {
            throw InternalException("Cannot take remainder of values of type " +
                                val1.toTypeString() + " and " + val2.toTypeString());
        }
        if ((val2.is<INT>()   && val2.get<INT>() == 0)     ||
            (val2.is<FLOAT>() && val2.get<FLOAT>() == 0.0) ||
            (val2.is<BOOL>()  && val2.get<BOOL>() == false)) {
            throw InternalException("Cannot take remainder of values with divisor 0");
        }
        if (!val1.is<FLOAT>() && !val2.is<FLOAT>()) {
            Value::INT int1 = (val1.is<INT>()) ? val1.get<INT>() : val1.get<BOOL>();
            Value::INT int2 = (val2.is<INT>()) ? val2.get<INT>() : val2.get<BOOL>();
            
            return Value::INT(std::fmod(int1, int2));
        }
        auto float1 = (val1.is<INT>())   ? val1.get<INT>()   : 
                      (val1.is<FLOAT>()) ? val1.get<FLOAT>() : val1.get<BOOL>();

        auto float2 = (val2.is<INT>())   ? val2.get<INT>()   : 
                      (val2.is<FLOAT>()) ? val2.get<FLOAT>() : val2.get<BOOL>();

        return Value(std::fmod(float1, float2));
        
    };
    return Value::binaryOperator(other, errOpWord, op);
}

Value Value::pow(const Value& other) const {
    std::string errOpWord = "get exponent between";
    const std::function<Value(Value, Value)> op = [](const Value& val1,
                                                     const Value& val2) -> Value {
        if (!val1.isNumeric() && !val2.isNumeric()) {
            throw InternalException("Cannot get exponent between values of type " +
                                val1.toTypeString() + " and " + val2.toTypeString());
        }
        if (!val1.is<FLOAT>() && !val2.is<FLOAT>()) {
            Value::INT int1 = (val1.is<INT>()) ? val1.get<INT>() : val1.get<BOOL>();
            Value::INT int2 = (val2.is<INT>()) ? val2.get<INT>() : val2.get<BOOL>();
            
            return Value::INT(std::pow(int1, int2));
        }
        auto float1 = (val1.is<INT>())   ? val1.get<INT>()   : 
                      (val1.is<FLOAT>()) ? val1.get<FLOAT>() : val1.get<BOOL>();

        auto float2 = (val2.is<INT>())   ? val2.get<INT>()   : 
                      (val2.is<FLOAT>()) ? val2.get<FLOAT>() : val2.get<BOOL>();

        return Value(std::pow(float1, float2));
    };
    return Value::binaryOperator(other, errOpWord, op);
}

Value Value::operator-() const {
    if (is<INT>()) {
        return Value(-get<INT>());
    }
    if (is<FLOAT>()) {
        return Value(-get<FLOAT>());
    }
    if (is<BOOL>()) {
        return Value(-Value::INT(get<BOOL>()));
    }
    if (is<COLUMN>()) {
        Value::COLUMN col = get<COLUMN>();
        Value::LIST result = std::make_shared<std::vector<std::shared_ptr<Value>>>();
        for (const std::shared_ptr<Value>& elem : *col->data) {
            result->push_back(std::make_shared<Value>(-(*elem)));
        }
        return Value(result);
    }

    throw InternalException("Cannot negate value of type " + toTypeString());
}

Value Value::operator&&(const Value& other) const {
    std::string errOpWord = "perform logical AND between";
    const std::function<Value(Value, Value)> op = [](const Value& val1,
                                                     const Value& val2) -> Value {

    
        if (!((val1.isNumeric() || val1.is<STR>() || val1.is<LIST>()) &&
            (val2.isNumeric() || val2.is<STR>() || val2.is<LIST>()))) {
            throw InternalException("Cannot perform logical AND between values of type " +
                                     val1.toTypeString() + " and " + val2.toTypeString());
        }

        if (val1.is<LIST>() && val1.get<LIST>()->empty()) {
            return val1.get<LIST>(); 
        } 
        if ((val1.is<INT>() && val1.get<INT>() == 0 )||
            (val1.is<FLOAT>() && val1.get<FLOAT>() == 0.0)) {
            return Value((val1.is<INT>() ? 0 : 0.0));
        }
        if (val1.is<STR>() && val1.get<STR>() == "") {
            return Value("");
        }
        if (val1.is<BOOL>() && val1.get<BOOL>() == false) {
            return Value(false);
        }
        
        return (val2.is<LIST>())  ? Value(val2.get<LIST>()) : 
                (val2.is<BOOL>())  ? Value(val2.get<BOOL>()) :
                (val2.is<INT>())   ? Value(val2.get<INT>()) : 
                (val2.is<FLOAT>()) ? Value(val2.get<FLOAT>()) : Value(val2.get<STR>());
    };
    return Value::binaryOperator(other, errOpWord, op);
}

Value Value::operator||(const Value& other) const {
    std::string errOpWord = "perform logical AND between";
    const std::function<Value(Value, Value)> op = [](const Value& val1,
                                                     const Value& val2) -> Value {

        if (!((val1.isNumeric() || val1.is<STR>() || val1.is<LIST>()) &&
            (val2.isNumeric() || val2.is<STR>() || val2.is<LIST>()))) {
            
            throw InternalException("Cannot perform logical OR between values of type " +
                                     val1.toTypeString() + " and " + val2.toTypeString());
        }

        if (val1.is<LIST>() && !val1.get<LIST>()->empty()) {
            return val1.get<LIST>(); 
        } 
        if ((val1.is<INT>()   && val1.get<INT>() != 0) ||
            (val1.is<FLOAT>() && val1.get<FLOAT>() != 0.0)) {
            return Value((val1.is<INT>() ? val1.get<INT>() : val1.get<FLOAT>()));
        }
        if (val1.is<STR>() && !val1.get<STR>().empty()) {
            return Value(val1.get<STR>());
        }
        if (val1.is<BOOL>() && val1.get<BOOL>() == true) {
            return Value(true);
        }
        
        return (val2.is<LIST>())  ? Value(val2.get<LIST>()) : 
                (val2.is<BOOL>())  ? Value(val2.get<BOOL>()) :
                (val2.is<INT>())   ? Value(val2.get<INT>()) : 
                (val2.is<FLOAT>()) ? Value(val2.get<FLOAT>()) : Value(val2.get<STR>());
    };
    return Value::binaryOperator(other, errOpWord, op);
}

Value Value::binaryOperator(const Value& other, const std::string& errOpWord,
                            const std::function<Value(Value, Value)>& op) const {
    if ((is<INT>() || is<BOOL>()) && (other.is<INT>() || other.is<BOOL>())) {
        Value::INT val1 = other.is<INT>() ? other.get<INT>() : static_cast<long>(other.get<BOOL>());
        Value::INT val2 = is<INT>() ? get<INT>() : static_cast<long>(get<BOOL>());

        return op(Value(val1), Value(val2));
    }
    if ((is<FLOAT>() || is<INT>() || is<BOOL>()) &&
        (other.is<FLOAT>() || other.is<INT>() || other.is<BOOL>())) {
        Value::FLOAT val1 = other.is<FLOAT>()
                                ? other.get<FLOAT>()
                                : (other.is<INT>() ? other.get<INT>() : static_cast<long>(other.get<BOOL>()));
        Value::FLOAT val2 = is<FLOAT>() ? get<FLOAT>() : (is<INT>() ? get<INT>() : static_cast<long>(get<BOOL>()));

        return op(Value(val1), Value(val2));
    }
    if (is<STR>() && other.is<STR>()) {
        return op(Value(other.get<STR>()), Value(get<STR>()));
    }
    if (is<LIST>() && other.is<LIST>()) {
        const Value::LIST& list1 = other.get<LIST>();
        const Value::LIST& list2 = get<LIST>();
        return op(list1, list2);
    }
    if (is<COLUMN>() && other.is<COLUMN>()) {
        const Value::LIST& list1 = other.get<COLUMN>()->data;
        const Value::LIST& list2 = get<COLUMN>()->data;

        if (list1->size() != list2->size()) {
            throw InternalException("Cannot " + errOpWord + " lists of different sizes");
        };

        Value::LIST result = std::make_shared<std::vector<std::shared_ptr<Value>>>();
        for (size_t i = 0; i < list1->size(); ++i) {
            result->push_back(
                std::make_shared<Value>(op(Value(*(*list1)[i]), Value(*(*list2)[i]))));
        }
        return Value(result);
    }
    if ((is<STR>()       && (other.isNumeric() || other.is<STR>())) ||
        (other.is<STR>() && (isNumeric()       || is<STR>()))) {
        
        return Value(op(*this, other));
    }
    if (is<LIST>() && other.isNumeric() ||
        other.is<LIST>() && isNumeric()) {
            
        return Value(op(*this, other));
    }
    if ((is<COLUMN>()       && (other.isNumeric() || other.is<STR>())) ||
        (other.is<COLUMN>() && (isNumeric()       || is<STR>()))) {
        const Value::LIST& list1 = get<COLUMN>()->data;
        Value::LIST result = std::make_shared<std::vector<std::shared_ptr<Value>>>();
        for (const std::shared_ptr<Value>& elem : *list1) {
            result->push_back(std::make_shared<Value>(op(Value(*elem), other)));
        }
        return Value(result);
    }
    throw InternalException("Cannot " + errOpWord + " values of type " + toTypeString() +
                            " and " + other.toTypeString());
}

Value::COLUMN Value::getColumnByHeader(const Value::TABLE& table, const std::string& header) {
    for (const auto& entry : *table) {
        if (entry.first == header) {
            return entry.second;
        }
    }
    return nullptr;  // Return null if no column with the given header is found
}

bool Value::isSameColumns(const Value::TABLE& leftTable, const Value::TABLE& rightTable) {
    for (size_t i = 0; i < leftTable->size(); ++i) {
        const auto& tempEntryLeft = std::next(leftTable->begin(), i);
        if (getColumnByHeader(rightTable, tempEntryLeft->first) == nullptr) {
            return false;
        }
    }
    return true;
}

void Value::insertColInTable(const Value::TABLE& table, const std::string& header,
                             Value::LIST list) {
    Value::COLUMN col = std::make_shared<Value::COL_STRUCT>();
    col->header = header;
    col->data = std::move(list);
    col->parent = table;
    table->insert({header, col});
}

double Value::getNumericValue() const {
    if (is<BOOL>()) {
        return static_cast<double>(get<BOOL>());
    }
    if (is<INT>()) {
        return static_cast<double>(get<INT>());
    } 
    if (is<FLOAT>()) {
        return get<FLOAT>();
    } 
    return 0.0;
}
