#include "Main.hpp"

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

    // Print the parse tree
    std::cout << tree->toStringTree(&parser, true) << "\n\n";

    // Write the parse tree to a DOT file
    if (argc >= 3) {
        std::ofstream out(argv[2]);
        out << "digraph {\n";
        generateDotFile(tree, "", out);
        out << "}\n";
        out.close();
    }

    return 0;
}