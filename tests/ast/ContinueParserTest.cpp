#include <TestingUtil.hpp>

using namespace dplgrammar;

AST_TEST("continue.dpl") {
    std::vector<size_t> expectedNodeRules = {
        DplParser::RuleProg,
        DplParser::RuleAssignstm,
        DplLexer::Identifier,
        DplLexer::Integer,
        DplParser::RuleWhilestm,
        DplParser::RuleCompexpr,
        DplLexer::Identifier,
        DplLexer::Integer,
        DplParser::RuleAssignstm,
        DplLexer::Identifier,
        DplParser::RulePlusexpr,
        DplLexer::Identifier,
        DplLexer::Integer,
        DplParser::RuleIfstm,
        DplParser::RuleEqulexpr,
        DplParser::RuleMultexpr,
        DplLexer::Identifier,
        DplLexer::Integer,
        DplLexer::Integer,
        DplLexer::Continue,
        DplParser::RuleProccall,
        DplLexer::Identifier,
        DplLexer::Identifier
    };
    dplutil::TestingUtil::testAst("continue.dpl", expectedNodeRules);
}