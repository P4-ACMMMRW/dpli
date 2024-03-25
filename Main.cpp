#include <Main.hpp>

using namespace antlr4;
using namespace dplgrammar;

int main(int argc, char **argv) {
    std::string description = "DPL Interpreter";
    std::string version = "0.0.1";
    std::string author = "P4-ACMMMRW";
    std::string usage = std::string{argv[0]} + " [options] <input file> [arguments]";
    argz::about about{description, version, author, usage};
    about.print_help_when_no_options = false;

    bool debug = false;
    std::string dotFile{};
    argz::options args {
        { { "debug", 'd' }, debug, "enable debug output"},
        { { "Dot", 'D' }, dotFile, "generate a DOT file for the parse tree"}
    };

    if (argc < 2) {
        argz::help(about, args);
        exit(EXIT_SUCCESS);
    }

    int fileArgIndex = 0;
    bool isOption = true;
    for (int i = 1; i < argc; ++i) {
        isOption = !std::strcmp(argv[i], "-h") || !std::strcmp(argv[i], "--help") || !std::strcmp(argv[i], "-v") || !std::strcmp(argv[i], "--version");

        if (!isOption) {
            fileArgIndex = i;
            break;
        }
    }

    // Parse all arguments except fileArgIndex and argv[0]
    try {
        argz::parse(about, args, argc, argv, fileArgIndex);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }

    // No file provided, and options have already been evaluated so exit program.
    if (!fileArgIndex) {
        exit(EXIT_SUCCESS);
    }

    // If after options comes an argument write error
    if (argv[fileArgIndex][0] == '-') {
        std::cerr << "Error: expected input file but received argument \"" << argv[fileArgIndex] << "\"\n";
        std::cout << "Usage: " << usage << '\n';
        exit(EXIT_FAILURE);
    }

    // Check if input file exists
    if (!std::filesystem::exists(argv[fileArgIndex])) {
        std::cerr << "Error: file \"" << argv[fileArgIndex] << "\" not found\n";
        exit(EXIT_FAILURE);
    }

    std::ifstream file{std::filesystem::path(argv[fileArgIndex])};
    if (!file.is_open()) {
        std::cerr << "Error: file \"" << argv[fileArgIndex] << "\" could not be opened\n";
        exit(EXIT_FAILURE);
    }

    ANTLRInputStream input(file);
    DplLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();

    DplParser parser(&tokens);
    tree::ParseTree *tree = parser.prog();

    if (debug) {
        for (antlr4::Token *token : tokens.getTokens()) {
            std::cout << token->toString() << '\n';
        }

        std::cout << tree->toStringTree(&parser, true) << "\n\n";
    }
    
    if (!dotFile.empty()) {
        generateDotFile(tree, dotFile);        
    }

    exit(EXIT_SUCCESS);
}

void generateDotFile(tree::ParseTree *root, std::string fileName) {
    std::ofstream out{std::filesystem::path(fileName)};

    std::stack<std::pair<tree::ParseTree *, std::string>> stack;
    std::string rootId = std::to_string(reinterpret_cast<std::uintptr_t>(root));

    stack.push({root, rootId});

    out << "digraph {\n";

    while (!stack.empty()) {
        std::pair<tree::ParseTree *, std::string> nodeAndParentId = stack.top();
        tree::ParseTree *node = nodeAndParentId.first;
        std::string parentId = nodeAndParentId.second;
        stack.pop();

        std::string nodeId = std::to_string(reinterpret_cast<std::uintptr_t>(node));

        // Escape quotation marks in label
        std::string label = std::regex_replace(node->getText(), std::regex("\""), "\\\"");

        out << "  " << nodeId << " [label=\"" << label << "\"];\n";
        if (!parentId.empty()) {
            out << "  " << parentId << " -> " << nodeId << ";\n";
        }

        // Push the node's children on stack
        for (std::vector<tree::ParseTree *>::reverse_iterator it = node->children.rbegin(); it != node->children.rend(); ++it) {
            stack.push({*it, nodeId});
        }
    }

    out << "}\n";
}
