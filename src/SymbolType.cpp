#include <Symbol.hpp>
#include <algorithm>
#include <cassert>

using namespace dplsrc;

bool Symbol::is(SymbolType type) const { return this->type == type; }

std::string Symbol::getType() const {}

bool Symbol::isOneOf(const std::initializer_list<SymbolType> &types) const {
    const SymbolType &type = this->type;
    return std::any_of(types.begin(), types.end(),
                       [type](int current_type) { return current_type == type; });
}

std::string Symbol::getType() const {
    if (type == TYPE_INT)
        return "int";
    else if (type == TYPE_FLOAT)
        return "float";
    else if (type == TYPE_STR)
        return "str";
    else if (type == TYPE_BOOL)
        return "bool";
    else if (type == TYPE_LIST)
        return "list";
    else if (type == TYPE_TABLE)
        return "table";
    else if (type == TYPE_NONETYPE)
        return "nonetype";
    else
        assert(false && "Unknown type");
}