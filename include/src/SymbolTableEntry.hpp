#include <string>

#include "Symbol.hpp"

namespace dplsrc {
class ASTNode;

class SymbolTableEntry {
   public:
    SymbolTableEntry(std::string name, Symbol type, ASTNode *declNode)
        : name(std::move(name)), type(std::move(type)), declNode(declNode) {}

    const std::string name;
    Symbol type = Symbol(TYPE_INVALID);
    ASTNode *declNode;
};
}  // namespace dplsrc