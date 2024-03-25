#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <fstream>
#include <filesystem>
#include <regex>
#include <antlr4-runtime.h>
#include <DplLexer.h>
#include <DplParser.h>
#include <tree/Trees.h>
//#include <argz.hpp>

/**
* Generate file which is used for visualizing the parse tree
*/
void generateDotFile(antlr4::tree::ParseTree* node, std::string fileName);

#endif