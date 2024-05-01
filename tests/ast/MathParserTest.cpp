#include <TestingUtil.hpp>

using namespace dplgrammar;

AST_TEST("math.dpl") {
    std::vector<size_t> expectedNodeRules = {
        DplParser::RuleProg,
        DplParser::RuleAssignstm,
        DplLexer::Identifier,
        DplParser::RuleExpoexpr,
        DplLexer::Integer,
        DplLexer::Integer,
        DplParser::RuleAssignstm,
        DplLexer::Identifier,
        DplParser::RuleMultexpr,
        DplLexer::Integer,
        DplLexer::Integer,
        DplParser::RuleAssignstm,
        DplLexer::Identifier,
        DplParser::RuleMultexpr,
        DplLexer::Integer,
        DplLexer::Integer,
        DplParser::RuleAssignstm,
        DplLexer::Identifier,
        DplParser::RuleMultexpr,
        DplLexer::Integer,
        DplLexer::Integer,
        DplParser::RuleProccall,
        DplLexer::Identifier,
        DplLexer::Identifier,
        DplParser::RuleProccall,
        DplLexer::Identifier,
        DplLexer::Identifier,
        DplParser::RuleProccall,
        DplLexer::Identifier,
        DplLexer::Identifier,
        DplParser::RuleProccall,
        DplLexer::Identifier,
        DplLexer::Identifier,
    };
    
    dplutil::TestingUtil::testAst("math.dpl", expectedNodeRules);
}