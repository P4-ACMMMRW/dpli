#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>

namespace dplsrc {
    class Symbol {
        public:
            Symbol(std::string val) : val(val) {}
            Symbol(std::string id, std::string val) : id(id), val(val) {}
            std::string getId() const { return id; }
            std::string getVal() const { return val; }
        
        private:
            std::string id;
            std::string val;
    };
}

#endif