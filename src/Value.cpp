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

        for (const Value &elem : *get<LIST>()) {
            result += elem.toString() + ", ";
        }

        // Remove trailing comma and space
        if (result.size() > 1) {
            result.pop_back();
            result.pop_back();
        }

        result += "]";

        return result;
    } else if (is<TABLE>()) {
        std::string result = "{ ";

        for (const std::pair<const std::string, Value::COLUMN> &entry : *get<TABLE>()) {
            result += entry.first + ": " + static_cast<Value>(entry.second).toString() + ", ";
        }

        // Remove trailing comma and space
        if (result.size() > 1) {
            result.pop_back();
            result.pop_back();
        }

        result += " }";

        return result;
    } else if (is<COLUMN>()) {
        std::string result = static_cast<Value>(get<COLUMN>()->header).toString() + ": [";

        for (const std::shared_ptr<Value>& valPtr : get<COLUMN>()->data) {
            result += valPtr->toString() + ", ";
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

std::string Value::toTypeString(bool verbose) const {
    if (is<INT>()) {
        return "int";
    } else if (is<FLOAT>()) {
        return "double";
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
        for (Value val : *list) {
            listStr += val.toTypeString(verbose) + ", ";
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
        for (const std::pair<const std::string, Value::COLUMN> &entry : *table) {
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

        std::string result = "column -> " + static_cast<Value>(get<COLUMN>()->header).toTypeString(verbose) +
               ": [";

        for (const std::shared_ptr<Value>& valPtr : get<COLUMN>()->data) {
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

    throw std::runtime_error("Error: unknown type cannot be converted to a string");
}

bool Value::operator==(const Value& other) const {
    if (is<INT>() && other.is<INT>()) {
        return get<INT>() == other.get<INT>();
    } else if (is<FLOAT>() && other.is<FLOAT>()) {
        return get<FLOAT>() == other.get<FLOAT>();
    } else if (is<STR>() && other.is<STR>()) {
        return get<STR>() == other.get<STR>();
    } else if (is<BOOL>() && other.is<BOOL>()) {
        return get<BOOL>() == other.get<BOOL>();
    } else if (is<NONETYPE>() && other.is<NONETYPE>()) {
        return true;
    } else if (is<LIST>() && other.is<LIST>()) {
        return *get<LIST>() == *other.get<LIST>();
    } else if (is<TABLE>() && other.is<TABLE>()) {
        return *get<TABLE>() == *other.get<TABLE>();
    } else if (is<COLUMN>() && other.is<COLUMN>()) {
        return get<COLUMN>()->data == other.get<COLUMN>()->data;
    }

    return false;
}