#include "Main.hpp"

using namespace antlr4;
using namespace dplgrammar;

int main(int argc, char **argv) {
    if (argc < 2 || argv[1] == "-h" || argv[1] == "--help") {
        std::string usageStr = "Usage: " + std::string(argv[0]) + " <file>";
        std::cout << usageStr << '\n';
        return 0;
    }

    if (!std::filesystem::exists(argv[1])) {
        std::cerr << "File does not exist: " << argv[1] << '\n';
        exit(EXIT_FAILURE);
    }

    std::ifstream file = std::ifstream(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << argv[1] << '\n';
        exit(EXIT_FAILURE);
    }

    ANTLRInputStream input(file);
    DplLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();
    for (antlr4::Token *token : tokens.getTokens()) {
        std::cout << token->toString() << '\n';
    }

    DplParser parser(&tokens);
    tree::ParseTree* tree = parser.prog();

    std::cout << tree->toStringTree(&parser, true) << "\n\n";

    return 0;
}