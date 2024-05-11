#include <TestingUtil.hpp>

using namespace dplgrammar;

AST_TEST("break.dpl") {
    std::vector<size_t> expectedNodeRules = {
        DplParser::RuleProg,
        DplParser::RuleAssignstm,
        DplLexer::Identifier,
        DplLexer::Integer,
        DplParser::RuleWhilestm,
        DplLexer::Bool,
        DplParser::RuleAssignstm,
        DplLexer::Identifier,
        DplParser::RulePlusexpr,
        DplLexer::Identifier,
        DplLexer::Integer,
        DplParser::RuleIfstm,
        DplParser::RuleEqulexpr,
        DplLexer::Identifier,
        DplLexer::Integer,
        DplLexer::Break,
        DplParser::RuleProccall,
        DplLexer::Identifier,
        DplLexer::String
    };
    dplutil::TestingUtil::testAst("break.dpl", expectedNodeRules);
}