#ifndef MAIN_HPP
#define MAIN_HPP

#include <DplLexer.h>
#include <DplParser.h>
#include <antlr4-runtime.h>

#include <argz.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>

/**
 * Generate file which is used for visualizing the parse tree
 */
void generateDotFile(antlr4::tree::ParseTree *node, const std::string &fileName);

#endif