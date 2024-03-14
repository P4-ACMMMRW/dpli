#include "Main.hpp"

using namespace antlr4;
using namespace dplgrammar;

int main(int argc, char **argv) {
    ANTLRInputStream input(u8"🍴 = 🍐 + \"😎\";(((x * π))) * µ + ∰; a + (x * (y ? 0 : 1) + z);");
    DplLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();
    for (auto token : tokens.getTokens()) {
        std::cout << token->toString() << '\n';
    }

    DplParser parser(&tokens);
    tree::ParseTree* tree = parser.main();

    std::cout << tree->toStringTree(&parser) << "\n\n";

    return 0;
}