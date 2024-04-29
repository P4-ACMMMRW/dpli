#ifndef PROCID_HPP
#define PROCID_HPP

namespace dplsrc {
    class ProcId {
        public:
            /**
             * @param name the name of the procedure
             * @param arity the arity of the procedure
            */
            ProcId(std::string name, int arity) : name(std::move(name)), arity(arity) {}

            /**
             * @return the id of the procedure
            */
            std::string getId() const { return name + "_" + std::to_string(arity); }

        private:
            std::string name;
            int arity;
    };
}

#endif