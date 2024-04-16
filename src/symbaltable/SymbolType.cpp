#include <SymbolType.hpp>
#include <algorithm>
#include <cassert>

using namespace dplsrc;

bool SymbolType::is(SymbolSuperType superType) const { return this->superType == superType; }


bool SymbolType::isOneOf(const std::initializer_list<SymbolSuperType> &superTypes) const {
    const SymbolSuperType &superType = this->superType;
    return std::any_of(superTypes.begin(), superTypes.end(),
                       [&superType](int type) { return type == superType; });
}

std::string SymbolType::getName() const {
    if (superType == TYPE_INT)
        return "int";
    else if (superType == TYPE_FLOAT)
        return "float";
    else if (superType == TYPE_STR)
        return "str";
    else if (superType == TYPE_BOOL)
        return "bool";
    else if (superType == TYPE_LIST)
        return "list";
    else if (superType == TYPE_TABLE)
        return "table";
    else if (superType == TYPE_NONETYPE)
        return "nonetype";
    else
        assert(false && "Unknown type");
}