
#include <Main.hpp>

using namespace antlr4;
using namespace dplgrammar;

int main(int argc, char **argv) {
    std::string description = "DPL Interpreter";
    std::string version = "0.0.1";
    std::string author = "P4-ACMMMRW";
    std::string usage = std::string(argv[0]) + " [options] <input file> [arguments]";
    argz::about about{description, version, author, usage};
    about.print_help_when_no_options = false;

    bool debug = false;
    argz::options options{{{"debug", 'd'}, debug, "enable debug output"}};

    if (argc < 2) {
        argz::help(about, options);
        return EXIT_SUCCESS;
    }

    int fileArgIndex = 0;
    bool isOption = true;
    for (int i = 1; i < argc; ++i) {
        isOption = std::strcmp(argv[i], "-h") == 0 || std::strcmp(argv[i], "--help") == 0 ||
                   std::strcmp(argv[i], "-v") == 0 || std::strcmp(argv[i], "--version") == 0;

        if (!isOption) {
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

    // No file provided, and options have already been evaluated so exit
    // program.
    if (fileArgIndex == 0) {
        return EXIT_SUCCESS;
    }

    // If after options comes an argument write error
    if (argv[fileArgIndex][0] == '-') {
        std::cerr << "Error: expected input file but received argument \"" << argv[fileArgIndex]
                  << "\"\n";
        std::cout << "Usage: " << usage << '\n';
        return EXIT_FAILURE;
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

    ANTLRInputStream input(file);
    DplLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();

    DplParser parser(&tokens);
    tree::ParseTree *tree = parser.prog();

    if (debug) {
         std::cout << tree->toStringTree(&parser, true) << "\n\n";

        // Ast print
        //AstBuilder builder{&parser, &lexer};
        //builder.visit(tree);
        //builder.getRoot()->print();
//
        //// Visitor
        //std::shared_ptr<AstNode> root = builder.getRoot();
        //std::shared_ptr<AstTestVisitor> visitor = std::make_shared<AstTestVisitor>();
        //root->accept(visitor);
    }

    return EXIT_SUCCESS;
}
