#include <Symbol.hpp>

using namespace dplsrc;

bool Symbol::is(SymbolType type) const { return this->type == type; }

std::string Symbol::getType() const {}
