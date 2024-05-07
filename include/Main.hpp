#ifndef MAIN_HPP
#define MAIN_HPP

#include <DplLexer.h>
#include <DplParser.h>
#include <antlr4-runtime.h>

#include <AstBuilder.hpp>
#include <argz.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>

#include "LexerErrorListener.hpp"
#include "ParserErrorListener.hpp"
#include "DplErrorStrategy.hpp"
#include "DplException.hpp"

#include "Evaluator.hpp"

#endif