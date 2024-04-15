#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>
#include <utility>

enum SymbolType {
    TYPE_INVALID,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STR,
    TYPE_BOOL,
    TYPE_LIST,
    TYPE_TABLE,
    TYPE_NONETYPE,
};

namespace dplsrc {
class Symbol {
   public:
    Symbol(std::string val) : val(std::move(val)) {}
    Symbol(std::string id, std::string val) : id(std::move(id)), val(std::move(val)) {}
    std::string getId() const { return id; }
    std::string getVal() const { return val; }

    explicit Symbol(SymbolType type) : type(type) {}
    std::string getType() const;
    bool is(SymbolType type) const;
    bool isOneOf(const std::initializer_list<SymbolType> &types) const;
    void setEvaluatedSymbolType(const SymbolType &type) { this->type = type; }

   private:
    std::string id;
    std::string val;
    SymbolType type;
};
}  // namespace dplsrc

#endif