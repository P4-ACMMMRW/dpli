
#include <Main.hpp>

using namespace antlr4;
using namespace dplgrammar;
using namespace dplsrc;

int main(int argc, char **argv) {
    std::string description = "DPL Interpreter";
    std::string version = "0.0.1";
    std::string author = "P4-ACMMMRW";
    std::string usage = std::string(argv[0]) + " [options] <input-file> [options]";
    argz::about about{description, version, author, usage};
    about.print_help_when_no_options = false;

    bool debug = false;
    bool interpretFromCli = false;
    argz::options options{{{"debug", 'd'}, debug, "enable debug output"},
                          {{"cli", 'c'}, interpretFromCli, "interpret from command line"}};

    if (argc < 2) {
        argz::help(about, options);
        return EXIT_SUCCESS;
    }

    int fileArgIndex = 0;
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] != '-') {
            fileArgIndex = i;
            break;
        }
    }

    // Parse all arguments except fileArgIndex and argv[0]
    try {
        argz::parse(about, options, argc, argv, fileArgIndex);
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    ANTLRInputStream input;

    if (!interpretFromCli) {
        // No source code provided, and options have already been evaluated so exit
        // program.
        if (fileArgIndex == 0) {
            return EXIT_SUCCESS;
        }

        // Check if input file exists
        if (!std::filesystem::exists(argv[fileArgIndex])) {
            std::cerr << "Error: file \"" << argv[fileArgIndex] << "\" not found\n";
            return EXIT_FAILURE;
        }

        std::ifstream file{std::filesystem::path(argv[fileArgIndex])};
        if (!file.is_open()) {
            std::cerr << "Error: file \"" << argv[fileArgIndex] << "\" could not be opened\n";
            return EXIT_FAILURE;
        }

        input = ANTLRInputStream(file);
    } else {
        std::cout << "> ";
        std::string source;
        std::getline(std::cin, source);

        input = ANTLRInputStream(source);
    }

    DplLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();

    DplParser parser(&tokens);
    tree::ParseTree *tree = parser.prog();

    AstBuilder builder{&parser, &lexer};
    builder.visit(tree);
    std::shared_ptr<AstNode> root = builder.getRoot();
    std::shared_ptr<Evaluator> evaluator = std::make_shared<Evaluator>();
    root->accept(evaluator);

    if (debug) {
        // std::cout << tree->toStringTree(&parser, true) << "\n\n";

        // Ast print
        builder.getRoot()->print();

        // Visitor
        // std::shared_ptr<AstTestVisitor> visitor = std::make_shared<AstTestVisitor>();
        // root->accept(visitor);

        // print eval
        evaluator->getVtable().print();
    }

    return EXIT_SUCCESS;
}
