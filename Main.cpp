
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
    } catch (const DplException &e) {
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
    lexer.removeErrorListeners();

    std::string filename = std::string(argv[fileArgIndex]).substr(std::string(argv[fileArgIndex]).find_last_of('/') + 1);
    std::shared_ptr<ANTLRErrorListener> lexerErrorListener = std::make_shared<LexerErrorListener>(filename);
    lexer.addErrorListener(lexerErrorListener.get());
    CommonTokenStream tokens(&lexer);

    try {
        tokens.fill();
    } catch (const dplsrc::RuntimeException &e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    DplParser parser(&tokens);
    parser.removeErrorListeners();
    std::shared_ptr<ANTLRErrorListener> parserErrorListener = std::make_shared<ParserErrorListener>(filename);
    parser.addErrorListener(parserErrorListener.get());
    std::shared_ptr<ANTLRErrorStrategy> strategy = std::make_shared<DplErrorStrategy>();
    parser.setErrorHandler(strategy);
    tree::ParseTree *tree; 
    
    try {
        tree = parser.prog();
    } catch (const ParseCancellationException &e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    AstBuilder builder{&parser, &lexer};
    builder.visit(tree);

    std::shared_ptr<AstNode> root;
    try {
        root = builder.getRoot();
    } catch (const DplException &e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    std::shared_ptr<Evaluator> evaluator;
    try {
        evaluator = std::make_shared<Evaluator>();
        root->accept(evaluator);
    } catch (const DplException &e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    if (debug) {
        // Ast print
        builder.getRoot()->print();

        // print eval
        evaluator->getVtable().print();
        evaluator->getPtable().print();
    }

    return EXIT_SUCCESS;
}
