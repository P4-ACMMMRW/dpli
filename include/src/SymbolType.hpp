#include <string>


namespace dplsrc{

enum SymbolSuperType {
    TYPE_INVALID,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STR,
    TYPE_BOOL,
    TYPE_LIST,
    TYPE_TABLE,
    TYPE_NONETYPE,
};

class SymbolType{
public:
    explicit SymbolType(SymbolSuperType superType) : superType(superType) {}

    std::string getName() const;
    bool is(SymbolSuperType superType) const;
    bool isOneOf(const std::initializer_list<SymbolSuperType> &superTypes) const;


    friend bool operator==(const SymbolType &lefthand, const SymbolType &righthand);
    friend bool operator!=(const SymbolType &lefthand, const SymbolType &righthand);


private:
    SymbolSuperType superType;
    };
}

