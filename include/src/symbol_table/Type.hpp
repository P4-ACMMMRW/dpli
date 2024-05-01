#ifndef TYPE_HPP
#define TYPE_HPP

#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

namespace dplsrc {
class Type {
   public:
    /**
     * Default constructor
     */
    Type() = default;

    /**
     * Generic constructor
     */
    template <typename T>
    Type(const T &type) : innerType(type) {}

    /**
     * Check if the value is of type T
     */
    template <typename T>
    bool is() const {
        return std::holds_alternative<T>(innerType);
    }

    /**
     * Get the value as type T
     */
    template <typename T>
    const T &get() const {
        return std::get<T>(innerType);
    }

    /**
     * Prints string representation of value
     * @param verbose Whether to expand composite types or not
     */
    std::string toString(bool verbose = false) const;

    /**
     * List type
     */
    using List = std::vector<Type>;

    enum class Primitive { INT, FLOAT, STR, BOOL, NONETYPE };

   private:
    std::variant<Primitive, List> innerType;
};
}  // namespace dplsrc

#endif