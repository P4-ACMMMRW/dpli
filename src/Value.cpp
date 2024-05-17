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
        if (!verbose) {
            return "list";
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
        if (!verbose) {
            return "table";
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
        if (!verbose) {
            return "column";
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

        if (list1->size() != list2->size()) {
            return false;
        }

        for (size_t i = 0; i < list1->size(); ++i) {
            if (*(*list1)[i] != *(*list2)[i]) {
                return false;
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
            if (*(*list1)[i] != *(*list2)[i]) {
                return *(*list1)[i] < *(*list2)[i];
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
    if (is<INT>()) {
        return get<INT>() == 0;  // not 0 == true
    }
    if (is<FLOAT>()) {
        return get<FLOAT>() == 0.0;  // not 0.0 == true
    }
    if (is<BOOL>()) {
        return !get<BOOL>();  // not False == True
    }
    if (is<STR>()) {
        return get<STR>().empty();  // not "" == true
    }
    if (is<LIST>()) {
        return get<LIST>()->empty();  // not [] == true
    }

    throw RuntimeException("Can not use NOT on this type");
}

Value Value::operator+(const Value& other) const {
    const Value val1 = *this;
    const Value val2 = other;

    if ((val1.is<INT>() || val1.is<BOOL>()) && (val2.is<INT>() || val2.is<BOOL>())) {
        Value::INT int1 = (val1.is<INT>()) ? val1.get<INT>() : val1.get<BOOL>();
        Value::INT int2 = (val2.is<INT>()) ? val2.get<INT>() : val2.get<BOOL>();

        return Value(int1 + int2);
    }
    if (val1.isNumeric() && val2.isNumeric()) {
        Value::FLOAT float1 = (val1.is<INT>())
                                  ? val1.get<INT>()
                                  : ((val1.is<BOOL>()) ? val1.get<BOOL>() : val1.get<FLOAT>());
        Value::FLOAT float2 = (val2.is<INT>())
                                  ? val2.get<INT>()
                                  : ((val2.is<BOOL>()) ? val2.get<BOOL>() : val2.get<FLOAT>());

        return Value(float1 + float2);
    }
    if (val1.is<STR>() && val2.is<STR>()) {
        return Value(val1.get<STR>() + val2.get<STR>());
    }
    if (val1.is<LIST>() && val2.is<LIST>()) {
        Value::LIST result = std::make_shared<std::vector<std::shared_ptr<Value>>>();

        Value::LIST list1 = val1.get<LIST>();
        Value::LIST list2 = val2.get<LIST>();

        for (const std::shared_ptr<Value>& elem : *list1) {
            result->push_back(elem);
        }
        for (const std::shared_ptr<Value>& elem : *list2) {
            result->push_back(elem);
        }

        return Value(result);
    }
    Value colResult = colOperations(val1, val2, [](Value val1, Value val2) { return val1 + val2; });
    if (colResult != Value(nullptr)) {
        return colResult;
    }
    throw RuntimeException("Cannot add values of type " + val1.toTypeString() + " and " +
                           val2.toTypeString());
}

Value Value::operator-(const Value& other) const {
    const Value val1 = *this;
    const Value val2 = other;

    if ((val1.is<INT>() || val1.is<BOOL>()) && (val2.is<INT>() || val2.is<BOOL>())) {
        Value::INT int1 = (val1.is<INT>()) ? val1.get<INT>() : val1.get<BOOL>();
        Value::INT int2 = (val2.is<INT>()) ? val2.get<INT>() : val2.get<BOOL>();

        return Value(int1 - int2);
    }
    if (val1.isNumeric() && val2.isNumeric()) {
        Value::FLOAT float1 = (val1.is<INT>())
                                  ? val1.get<INT>()
                                  : ((val1.is<BOOL>()) ? val1.get<BOOL>() : val1.get<FLOAT>());
        Value::FLOAT float2 = (val2.is<INT>())
                                  ? val2.get<INT>()
                                  : ((val2.is<BOOL>()) ? val2.get<BOOL>() : val2.get<FLOAT>());

        return Value(float1 - float2);
    }
    Value colResult = colOperations(val1, val2, [](Value val1, Value val2) { return val1 - val2; });
    if (colResult != Value(nullptr)) {
        return colResult;
    }
    throw RuntimeException("Cannot detract values of type " + val1.toTypeString() + " and " +
                           val2.toTypeString());
}

Value Value::operator*(const Value& other) const {
    const Value val1 = *this;
    const Value val2 = other;

    bool isVal1Int = val1.is<INT>() || val1.is<BOOL>();
    bool isVal2Int = val2.is<INT>() || val2.is<BOOL>();

    if (isVal1Int && isVal2Int) {
        Value::INT int1 = (val1.is<INT>()) ? val1.get<INT>() : val1.get<BOOL>();
        Value::INT int2 = (val2.is<INT>()) ? val2.get<INT>() : val2.get<BOOL>();

        return Value(int1 * int2);
    }
    if (val1.isNumeric() && val2.isNumeric()) {
        Value::FLOAT float1 = (val1.is<INT>())
                                  ? val1.get<INT>()
                                  : ((val1.is<BOOL>()) ? val1.get<BOOL>() : val1.get<FLOAT>());
        Value::FLOAT float2 = (val2.is<INT>())
                                  ? val2.get<INT>()
                                  : ((val2.is<BOOL>()) ? val2.get<BOOL>() : val2.get<FLOAT>());

        return Value(float1 * float2);
    }
    if ((isVal1Int && val2.is<STR>()) || (isVal2Int && val1.is<STR>())) {
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
    Value colResult = colOperations(val1, val2, [](Value val1, Value val2) { return val1 * val2; });
    if (colResult != Value(nullptr)) {
        return colResult;
    }
    throw RuntimeException("Cannot multiply values of type " + val1.toTypeString() + ": " +
                           val1.toString() + " and " + val2.toTypeString() + ": " +
                           val2.toString());
}

Value Value::operator/(const Value& other) const {
    const Value val1 = *this;
    const Value val2 = other;

    if ((val2.is<INT>() && val2.get<INT>() == 0) ||
        (val2.is<FLOAT>() && val2.get<FLOAT>() == 0.0) ||
        (val2.is<BOOL>() && val2.get<BOOL>() == false)) {
        throw RuntimeException("Cannot divide values with divisor 0");
    }
    if ((val1.is<INT>() || val1.is<BOOL>()) && (val2.is<INT>() || val2.is<BOOL>())) {
        Value::INT int1 = (val1.is<INT>()) ? val1.get<INT>() : val1.get<BOOL>();
        Value::INT int2 = (val2.is<INT>()) ? val2.get<INT>() : val2.get<BOOL>();

        return Value::INT(int1 / int2);
    }
    if (val1.isNumeric() && val2.isNumeric()) {
        Value::FLOAT float1 = (val1.is<INT>())
                                  ? val1.get<INT>()
                                  : ((val1.is<BOOL>()) ? val1.get<BOOL>() : val1.get<FLOAT>());
        Value::FLOAT float2 = (val2.is<INT>())
                                  ? val2.get<INT>()
                                  : ((val2.is<BOOL>()) ? val2.get<BOOL>() : val2.get<FLOAT>());

        return Value(float1 / float2);
    }
    Value colResult = colOperations(val1, val2, [](Value val1, Value val2) { return val1 % val2; });
    if (colResult != Value(nullptr)) {
        return colResult;
    }

    throw RuntimeException("Cannot divide values of type " + val1.toTypeString() + " and " +
                           val2.toTypeString());
}

Value Value::operator%(const Value& other) const {
    const Value val1 = *this;
    const Value val2 = other;

    if ((val2.is<INT>() && val2.get<INT>() == 0) ||
        (val2.is<FLOAT>() && val2.get<FLOAT>() == 0.0) ||
        (val2.is<BOOL>() && val2.get<BOOL>() == false)) {
        throw RuntimeException("Cannot take remainder of values with divisor 0");
    }
    if ((val1.is<INT>() || val1.is<BOOL>()) && (val2.is<INT>() || val2.is<BOOL>())) {
        Value::INT int1 = (val1.is<INT>()) ? val1.get<INT>() : val1.get<BOOL>();
        Value::INT int2 = (val2.is<INT>()) ? val2.get<INT>() : val2.get<BOOL>();

        return Value::INT(int1 % int2);
    }
    if (val1.isNumeric() && val2.isNumeric()) {
        Value::FLOAT float1 = (val1.is<INT>())
                                  ? val1.get<INT>()
                                  : ((val1.is<BOOL>()) ? val1.get<BOOL>() : val1.get<FLOAT>());
        Value::FLOAT float2 = (val2.is<INT>())
                                  ? val2.get<INT>()
                                  : ((val2.is<BOOL>()) ? val2.get<BOOL>() : val2.get<FLOAT>());

        return Value(std::fmod(float1, float2));
    }
    Value colResult = colOperations(val1, val2, [](Value val1, Value val2) { return val1 % val2; });
    if (colResult != nullptr) {
        return colResult;
    }
    throw RuntimeException("Cannot get remainder between values of type " + val1.toTypeString() +
                           " and " + val2.toTypeString());
}

Value Value::pow(const Value& other) const {
    const Value val1 = *this;
    const Value val2 = other;

    if ((val1.is<INT>() || val1.is<BOOL>()) && (val2.is<INT>() || val2.is<BOOL>())) {
        Value::INT int1 = (val1.is<INT>()) ? val1.get<INT>() : val1.get<BOOL>();
        Value::INT int2 = (val2.is<INT>()) ? val2.get<INT>() : val2.get<BOOL>();

        return Value::INT(std::pow(int1, int2));
    }
    if (val1.isNumeric() && val2.isNumeric()) {
        Value::FLOAT float1 = (val1.is<INT>())
                                  ? val1.get<INT>()
                                  : ((val1.is<BOOL>()) ? val1.get<BOOL>() : val1.get<FLOAT>());
        Value::FLOAT float2 = (val2.is<INT>())
                                  ? val2.get<INT>()
                                  : ((val2.is<BOOL>()) ? val2.get<BOOL>() : val2.get<FLOAT>());

        return Value(std::pow(float1, float2));
    }
    Value colResult =
        colOperations(val1, val2, [](Value val1, Value val2) { return val1.pow(val2); });
    if (colResult != Value(nullptr)) {
        return colResult;
    }
    throw RuntimeException("Cannot get exponent between values of type " + val1.toTypeString() +
                           " and " + val2.toTypeString());
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

    throw RuntimeException("Cannot negate value of type " + toTypeString());
}

Value Value::operator&&(const Value& other) const {
    const Value val1 = *this;
    const Value val2 = other;

    if (!val1.getBoolValue()) {
        return val1;
    }

    return val2;
}

Value Value::operator||(const Value& other) const {
    const Value val1 = *this;
    const Value val2 = other;

    if (val1.getBoolValue()) {
        return val1;
    }

    return val2;
}

Value Value::colOperations(const Value val1, const Value val2,
                           const std::function<Value(Value, Value)>& op) const {
    if (val1.is<COLUMN>() && val2.is<COLUMN>()) {
        const Value::LIST& list1 = val1.get<COLUMN>()->data;
        const Value::LIST& list2 = val2.get<COLUMN>()->data;

        if (list1->size() != list2->size()) {
            throw RuntimeException("Cannot perform operation on Columns of different sizes");
        };

        Value::LIST result = std::make_shared<std::vector<std::shared_ptr<Value>>>();
        for (size_t i = 0; i < list1->size(); ++i) {
            result->push_back(
                std::make_shared<Value>(op(Value(*(*list1)[i]), Value(*(*list2)[i]))));
        }
        return Value(result);
    }
    if ((val1.is<COLUMN>() && (val2.isNumeric() || val2.is<STR>()))) {
        const Value::LIST& list1 = val1.get<COLUMN>()->data;
        Value::LIST result = std::make_shared<std::vector<std::shared_ptr<Value>>>();
        for (const std::shared_ptr<Value>& elem : *list1) {
            result->push_back(std::make_shared<Value>(op((*elem), val2)));
        }
        return Value(result);
    }
    if ((val2.is<COLUMN>() && (val1.isNumeric() || val1.is<STR>()))) {
        const Value::LIST& list1 = val2.get<COLUMN>()->data;
        Value::LIST result = std::make_shared<std::vector<std::shared_ptr<Value>>>();
        for (const std::shared_ptr<Value>& elem : *list1) {
            result->push_back(std::make_shared<Value>(op(val1, (*elem))));
        }
        return Value(result);
    }

    return Value(nullptr);
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

bool Value::getBoolValue() const {
    if (is<BOOL>()) {
        return get<BOOL>();
    }
    if (is<INT>()) {
        return get<INT>() != 0;
    }
    if (is<FLOAT>()) {
        return get<FLOAT>() != 0.0;
    }
    if (is<STR>()) {
        return !get<STR>().empty();
    }
    if (is<LIST>()) {
        return !get<LIST>()->empty();
    }
    if (is<COLUMN>()) {
        return !get<COLUMN>()->data->empty();
    }
    if (is<TABLE>()) {
        return !get<TABLE>()->empty();
    }
    return false;
}