#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>
#include <utility>

namespace dplsrc {
class Symbol {
public:
    Symbol(std::string val) : val(std::move(val)) {}
    Symbol(std::string id, std::string val) : id(std::move(id)), val(std::move(val)) {}
    std::string getId() const { return id; }
    std::string getVal() const { return val; }

private:
    std::string id;
    std::string val;
};
}  // namespace dplsrc

#endif