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
    } else if (is<TABLE>()) {
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
    } else if (is<COLUMN>()) {
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

    throw InternalException("Error: unknown value type");
}

std::string Value::toTypeString(bool verbose) const {
    if (is<INT>()) {
        return "int";
    } else if (is<FLOAT>()) {
        return "float";
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
    } else if (is<TABLE>()) {
        if (!verbose) return "table";

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
    } else if (is<COLUMN>()) {
        if (!verbose) return "column";

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

    throw InternalException("unknown type cannot be converted to a string");
}

bool Value::operator==(const Value& other) const {
    if ((is<INT>() || is<FLOAT>() || is<BOOL>()) &&
        (other.is<INT>() || other.is<FLOAT>() || other.is<BOOL>())) {
        Value::FLOAT val1 = is<INT>() ? get<INT>() : (is<FLOAT>() ? get<FLOAT>() : get<BOOL>());
        Value::FLOAT val2 = other.is<INT>()
                                ? other.get<INT>()
                                : (other.is<FLOAT>() ? other.get<FLOAT>() : other.get<BOOL>());
        return val1 == val2;
    } else if (is<STR>() && other.is<STR>()) {
        return get<STR>() == other.get<STR>();
    } else if (is<NONETYPE>() && other.is<NONETYPE>()) {
        return true;
    } else if (is<LIST>() && other.is<LIST>()) {
        Value::LIST list1 = get<LIST>();
        Value::LIST list2 = other.get<LIST>();

        if (list1->size() != list2->size()) return false;

        for (size_t i = 0; i < list1->size(); ++i) {
            if (*(*list1)[i] != *(*list2)[i]) return false;
        }

        return true;
    } else if (is<COLUMN>() && other.is<COLUMN>()) {
        Value::COLUMN col1 = get<COLUMN>();
        Value::COLUMN col2 = other.get<COLUMN>();

        return Value(col1->data) == Value(col2->data);
    } else if (is<TABLE>() && other.is<TABLE>()) {
        Value::TABLE table1 = get<TABLE>();
        Value::TABLE table2 = other.get<TABLE>();

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
        Value::FLOAT val1 = is<INT>() ? get<INT>() : (is<FLOAT>() ? get<FLOAT>() : get<BOOL>());
        Value::FLOAT val2 = other.is<INT>()
                                ? other.get<INT>()
                                : (other.is<FLOAT>() ? other.get<FLOAT>() : other.get<BOOL>());
        return val1 < val2;
    } else if (is<STR>() && other.is<STR>()) {
        return get<STR>() < other.get<STR>();
    } else if (is<NONETYPE>() && other.is<NONETYPE>()) {
        return false;
    } else if (is<LIST>() && other.is<LIST>()) {
        Value::LIST list1 = get<LIST>();
        Value::LIST list2 = other.get<LIST>();

        size_t minSize = std::min(list1->size(), list2->size());

        for (size_t i = 0; i < minSize; ++i) {
            if (*(*list1)[i] != *(*list2)[i]) return *(*list1)[i] < *(*list2)[i];
        }

        return list1->size() < list2->size();
    } else if (is<COLUMN>() && other.is<COLUMN>()) {
        Value::COLUMN col1 = get<COLUMN>();
        Value::COLUMN col2 = other.get<COLUMN>();
        return Value(col1->data) < Value(col2->data);
    } else if (is<TABLE>() && other.is<TABLE>()) {
        Value::TABLE table1 = get<TABLE>();
        Value::TABLE table2 = other.get<TABLE>();

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


Value Value::operator+(const Value& other) const {
    std::string errOpWord = "add";

    const std::function<Value(Value, Value)> op = [this](Value val1, Value val2) -> Value {
        if (val1.is<INT>() && val2.is<INT>()) {
            return Value(val1.get<INT>() + val2.get<INT>());
        } else if ((val1.is<INT>() || val1.is<FLOAT>()) &&
                   (val2.is<INT>() || val2.is<FLOAT>())) {
                
            return Value(((val1.is<INT>()) ? val1.get<INT>() : val1.get<FLOAT>()) + 
                         ((val2.is<INT>()) ? val2.get<INT>() : val2.get<FLOAT>()));
        } else if (val1.is<STR>() && val2.is<STR>()) {
            return Value(val1.get<STR>() + val2.get<STR>());
        } else if (val1.is<LIST>() && val2.is<LIST>()) {
            return Value(val1.get<LIST>()) + Value(val2.get<LIST>());
        } else {
            throw InternalException("Error: cannot add values of type " + val1.toTypeString() + 
                                    " and " + val2.toTypeString());
        }
    };
    return Value::binaryOperator(other, errOpWord, op);
}

Value Value::operator-(const Value& other) const {
    std::string errOpWord = "detract";

    const std::function<Value(Value, Value)> op = [this](Value val1, Value val2) -> Value {

        if (val1.is<INT>() && val2.is<INT>()) {
            return Value(val1.get<INT>() - val2.get<INT>());
        } else if ((val1.is<INT>() || val1.is<FLOAT>()) &&
            (val2.is<INT>() || val2.is<FLOAT>())) {

            return Value(((val1.is<INT>()) ? val1.get<INT>() : val1.get<FLOAT>()) - 
                         ((val2.is<INT>()) ? val2.get<INT>() : val2.get<FLOAT>()));
        } else if (val1.is<LIST>() && val2.is<LIST>()) {
            return Value(val1.get<LIST>()) - Value(val2.get<LIST>());
        } else {
            throw InternalException("Error: cannot detract values of type " + val1.toTypeString() + 
                                    " and " + val2.toTypeString());
        }
    };
    return Value::binaryOperator(other, errOpWord, op);
}

Value Value::operator*(const Value& other) const {
    std::string errOpWord = "multiply";
    const std::function<Value(Value, Value)> op = [this](Value val1, Value val2) -> Value {
        if (val1.is<INT>() && val2.is<INT>()) {
            return Value(val1.get<INT>() * val2.get<INT>());
        } else if ((val1.is<INT>() || val1.is<FLOAT>()) &&
            (val2.is<INT>() || val2.is<FLOAT>())) {

            return Value(((val1.is<INT>()) ? val1.get<INT>() : val1.get<FLOAT>()) * 
                         ((val2.is<INT>()) ? val2.get<INT>() : val2.get<FLOAT>()));
        }  else if (val1.is<LIST>() && val2.is<LIST>()) {
            return Value(val1.get<LIST>()) * Value(val2.get<LIST>());
        } else if (((val1.is<INT>() || val1.is<BOOL>())   && val2.is<STR>()) || 
                   ((val2.is<INT>() || val2.is<BOOL>()) && val1.is<STR>())) {
            int intVal;
            std::string strVal;

            if (val1.is<INT>() || val1.is<BOOL>()) {
                intVal = (val1.is<INT>()) ? val1.get<INT>() : val1.get<BOOL>();
                strVal = val2.get<STR>();
            } else {
                intVal = (val2.get<INT>()) ? val2.get<INT>() : val2.get<BOOL>();
                strVal = val1.get<STR>();
            }

            std::string resultStr = "";
            for (int i = 0; i < intVal; ++i) {
                resultStr += strVal;
            }
            return Value(resultStr);
        } else if (((val1.is<INT>() || val1.is<BOOL>()) && val2.is<LIST>()) || 
                   ((val2.is<INT>() || val2.is<BOOL>()) && val1.is<LIST>())) {
            Value::LIST result = std::make_shared<std::vector<std::shared_ptr<Value>>>();
            int intVal;
            Value::LIST listVal;

            if (val1.is<INT>() || val1.is<BOOL>()) {
                intVal = (val1.is<INT>()) ? val1.get<INT>() : val1.get<BOOL>();
                listVal = val2.get<LIST>();
            } else {
                intVal = (val2.get<INT>()) ? val2.get<INT>() : val2.get<BOOL>();
                listVal = val1.get<LIST>();
            }

            for (int i = 0; i < intVal; ++i) {
                for (const std::shared_ptr<Value>& elem : *listVal) {
                    result->push_back(elem);
                }
            }
            
            return Value(result);
        } else {
            throw InternalException("Error: cannot multiply values of type " + val1.toTypeString() + 
                                    " and " + val2.toTypeString());
        }
    };
    return Value::binaryOperator(other, errOpWord, op);
}

Value Value::operator/(const Value& other) const {
    std::string errOpWord = "divide";
    const std::function<Value(Value, Value)> op = [this](Value val1, Value val2) -> Value {
        if ((val1.is<INT>() || val1.is<FLOAT>()) &&
            (val2.is<INT>() || val2.is<FLOAT>())) {

            return Value(((val1.is<INT>()) ? val1.get<INT>() : val1.get<FLOAT>()) / 
                         ((val2.is<INT>()) ? val2.get<INT>() : val2.get<FLOAT>()));
        } else if (val1.is<LIST>() && val2.is<LIST>()) {
            return Value(val1.get<LIST>()) / Value(val2.get<LIST>());
        } else {
            throw InternalException("Error: cannot divide values of type " + val1.toTypeString() + 
                                    " and " + val2.toTypeString());
        }
    };
    return Value::binaryOperator(other, errOpWord, op);
}

Value Value::operator%(const Value& other) const {
    std::string errOpWord = "take remainder of";
    const std::function<Value(Value, Value)> op = [this](Value val1, Value val2) -> Value {
        if ((val1.is<INT>() || val1.is<FLOAT>()) &&
            (val2.is<INT>() || val2.is<FLOAT>())) {

            return Value(std::fmod(((val1.is<INT>()) ? val1.get<INT>() : val1.get<FLOAT>()), 
                                   ((val2.is<INT>()) ? val2.get<INT>() : val2.get<FLOAT>())));

        } else if (val1.is<LIST>() && val2.is<LIST>()) {
            return Value(val1.get<LIST>()) % Value(val2.get<LIST>());
        } else {
            throw InternalException("Error: cannot take remainder of values of type " + val1.toTypeString() + 
                                    " and " + val2.toTypeString());
        }
    };
    return Value::binaryOperator(other, errOpWord, op);
}

Value Value::pow(const Value& other) const {
    std::string errOpWord = "get exponent between";
    const std::function<Value(Value, Value)> op = [this](Value val1, Value val2) -> Value {
        
        if ((val1.is<INT>() || val1.is<FLOAT>()) &&
            (val2.is<INT>() || val2.is<FLOAT>())) {

            return Value(std::pow(((val1.is<INT>()) ? val1.get<INT>() : val1.get<FLOAT>()),
                                  ((val2.is<INT>()) ? val2.get<INT>() : val2.get<FLOAT>())));
        } else if (val1.is<LIST>() && val2.is<LIST>()) {
            return Value(val1.get<LIST>()).pow(Value(val2.get<LIST>()));
        } else {
            throw InternalException("Error: cannot get exponent between values of type " + val1.toTypeString() + 
                                    " and " + val2.toTypeString());
        }
    };
    return Value::binaryOperator(other, errOpWord, op);
}


Value Value::binaryOperator(const Value& other, 
                            std::string errOpWord, 
                            const std::function<Value(Value, Value)>& op) const {

    if ((is<INT>() || is<BOOL>()) && (other.is<INT>() || other.is<BOOL>())) {

        Value::INT val1 = other.is<INT>() ? other.get<INT>() : other.get<BOOL>();
        Value::INT val2 = is<INT>() ? get<INT>() : get<BOOL>();

        return op(Value(val1),  Value(val2));
    } else if ((is<FLOAT>()       || is<INT>()       || is<BOOL>()) &&
               (other.is<FLOAT>() || other.is<INT>() || other.is<BOOL>())) {

        Value::FLOAT val1 = other.is<FLOAT>()
                                ? other.get<FLOAT>()
                                : (other.is<INT>() ? other.get<INT>() : other.get<BOOL>());
        Value::FLOAT val2 = is<FLOAT>() ? get<FLOAT>() : (is<INT>() ? get<INT>() : get<BOOL>());

        return op(Value(val1), Value(val2));
    } else if (is<STR>() && other.is<STR>()) {
        return op(Value(other.get<STR>()), Value(get<STR>()));
    } else if (is<NONETYPE>() && other.is<NONETYPE>()) {
        return Value(nullptr); // might need to throw error
    } else if (is<LIST>() && other.is<LIST>()) {
        Value::LIST list1 = other.get<LIST>();
        Value::LIST list2 = get<LIST>();

        if (list1->size() != list2->size()) {
            throw InternalException("Error: cannot " + errOpWord + " lists of different sizes");
        };

        Value::LIST result = std::make_shared<std::vector<std::shared_ptr<Value>>>();
        for (size_t i = 0; i < list1->size(); ++i) {
            result->push_back(std::make_shared<Value>(op(Value(*(*list1)[i]), Value(*(*list2)[i]))));
        }
        return Value(result);

    } else if (is<COLUMN>() && other.is<COLUMN>()) {
        Value::COLUMN col1 = get<COLUMN>();
        Value::COLUMN col2 = other.get<COLUMN>();

        return op(Value(col1->data), Value(col2->data));
    } else if (is<TABLE>() && other.is<TABLE>()) {
        Value::TABLE resultTable = std::make_shared<std::map<std::string, Value::COLUMN>>();
        Value::TABLE table1 = other.get<TABLE>();
        Value::TABLE table2 = get<TABLE>();

        if (table1->size() != table2->size()) {
            throw InternalException("Error: cannot " + errOpWord + " tables of different sizes\n " 
                                    + std::to_string(table1->size()) + " != " + std::to_string(table2->size()));
        }

        for (const std::pair<const std::string, Value::COLUMN>& entry : *table1) {
            auto result = op(Value(entry.second), Value(table2->at(entry.first)));
            if (result.is<LIST>()) {
                auto list = result.get<LIST>();
                Value::insertColInTable(resultTable, entry.first, list);
            }
        }
        return Value(resultTable);
    } else if (((is<INT>()       || is<BOOL>())       && other.is<STR>()) || 
               ((other.is<INT>() || other.is<BOOL>()) && is<STR>())) {

        return op(Value(other), Value(*this)); 
    } else if (((is<INT>()       || is<BOOL>())       && other.is<LIST>()) || 
               ((other.is<INT>() || other.is<BOOL>()) && is<LIST>())) {
        return op(Value(other), Value(*this)); 
    }
    throw InternalException("Error: cannot " + errOpWord  + 
                            " values of type " + toTypeString() + 
                            " and " + other.toTypeString());
}

Value::COLUMN Value::getColumnByHeader(Value::TABLE table, const std::string& header) const {
    for (const auto& entry : *table) {
        if (entry.first == header) {
            return entry.second;
        }
    }
    return nullptr; // Return null if no column with the given header is found
}

bool Value::isSameColumns(Value::TABLE leftTable, Value::TABLE rightTable) const {
    for (size_t i = 0; i < leftTable->size(); ++i) {
        const auto& tempEntryLeft = std::next(leftTable->begin(), i); 
        if (getColumnByHeader(rightTable, tempEntryLeft->first) == nullptr) return false;
    }
    return true;
}

void Value::insertColInTable(Value::TABLE table, std::string header, Value::LIST list) const {
    Value::COLUMN col = std::make_shared<Value::COL_STRUCT>();
    col->header = header;
    col->data = list; 
    col->parent = table;
    table->insert({header, col});
}

