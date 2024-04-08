#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>

enum SymbolType {
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
            Symbol(std::string val) : val(val) {}
            Symbol(std::string id, std::string val) : id(id), val(val) {}
            std::string getId() const { return id; }
            std::string getVal() const { return val; }
            
            Symbol(SymbolType type) : type(type) {}
            std::string getType() const;
            bool is(SymbolType type) const;
            
        
        private:
            std::string id;
            std::string val;
            SymbolType type;
    };
}

#endif