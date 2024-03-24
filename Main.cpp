#include <Main.hpp>

using namespace antlr4;
using namespace dplgrammar;

std::string escapeDotString(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (c == '"') {
            result += "\\\"";
        } else {
            result += c;
        }
    }
    return result;
}

/*
   Generate file which is used for visualizing the parse tree
*/
void generateDotFile(tree::ParseTree* node, const std::string& parentId, std::ofstream& out) {
    std::string nodeId = std::to_string(reinterpret_cast<std::uintptr_t>(node));

    // Use the text of the node as the label
    std::string label = escapeDotString(node->getText());

    out << "  " << nodeId << " [label=\"" << label << "\"];\n";
    if (!parentId.empty()) {
        out << "  " << parentId << " -> " << nodeId << ";\n";
    }
    for (size_t i = 0; i < node->children.size(); ++i) {
        generateDotFile(node->children[i], nodeId, out);
    }
}

int main(int argc, char **argv) {
    std::string description = "DPL Interpreter";
    std::string version = "0.0.1";
    std::string author = "P4-ACMMMRW";
    std::string usage = std::string(argv[0]) + " <input file> [options]";
    argz::about about{ description, version, author, usage };
    about.print_help_when_no_options = false;

    bool verbose = false;
    bool debug = false;
    std::string dotFile{};
    argz::options opts {
        { { "verbose", 'v'}, verbose, "enable verbose output"},
        { { "debug", 'd' }, debug, "enable debug output"},
        { { "Dot", 'D' }, dotFile, "generate a DOT file for the parse tree"}
    };

    if (argc < 2) {
        argz::help(about, opts);
        exit(EXIT_FAILURE);
    }

    if (argv[1][0] == '-' ) {
        std::cerr << "Usage: " << usage << '\n';
        exit(EXIT_FAILURE);
    }

    if (std::filesystem::exists(argv[1])) {
        std::cerr << "Error: file \"" << argv[1] << "\" not found\n";
        exit(EXIT_FAILURE);
    }

    std::ifstream file = std::ifstream(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: file \"" << argv[1] << "\" could not be opened\n";
        exit(EXIT_FAILURE);
    }

    try {
        argz::parse(about, opts, argc - 1, argv + 1);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }

    ANTLRInputStream input(file);
    DplLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();

    DplParser parser(&tokens);
    tree::ParseTree* tree = parser.prog();

    if (debug) {
        for (antlr4::Token *token : tokens.getTokens()) {
            std::cout << token->toString() << '\n';
        }

        std::cout << tree->toStringTree(&parser, true) << "\n\n";
    }
    
    if (!dotFile.empty()) {
        std::ofstream out(dotFile);
        out << "digraph {\n";
        generateDotFile(tree, "", out);
        out << "}\n";
    }

    return 0;
}