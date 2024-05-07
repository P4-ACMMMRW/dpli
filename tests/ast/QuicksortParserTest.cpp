#include <TestingUtil.hpp>

using namespace dplgrammar;

AST_TEST("quicksort.dpl") {
    std::vector<size_t> expectedNodeRules = {
       DplParser::RuleProg,
       DplParser::RuleProcdec,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplParser::RuleIfstm,
       DplParser::RuleAndexpr,
       DplParser::RuleCompexpr,
       DplLexer::Identifier,
       DplLexer::Integer,
       DplParser::RuleCompexpr,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplParser::RuleAssignstm,
       DplLexer::Identifier,
       DplParser::RuleProccall,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplParser::RuleProccall,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplParser::RulePlusexpr,
       DplParser::RuleIndex,
       DplLexer::Identifier,
       DplLexer::Integer,
       DplLexer::Integer,
       DplParser::RuleProccall,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplParser::RulePlusexpr,
       DplParser::RuleIndex,
       DplLexer::Identifier,
       DplLexer::Integer,
       DplLexer::Integer,
       DplLexer::Identifier,
       DplParser::RuleProcdec,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplParser::RuleAssignstm,
       DplLexer::Identifier,
       DplParser::RuleIndex,
       DplLexer::Identifier,
       DplParser::RuleProccall,
       DplLexer::Identifier,
       DplParser::RuleMultexpr,
       DplParser::RuleTerm,
       DplParser::RulePlusexpr,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplLexer::Integer,
       DplParser::RuleAssignstm,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplParser::RuleAssignstm,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplParser::RuleAssignstm,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplParser::RuleWhilestm,
       DplParser::RuleCompexpr,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplParser::RuleIfstm,
       DplParser::RuleCompexpr,
       DplParser::RuleIndex,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplParser::RuleProccall,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplParser::RuleAssignstm,
       DplLexer::Identifier,
       DplParser::RulePlusexpr,
       DplLexer::Identifier,
       DplLexer::Integer,
       DplParser::RuleAssignstm,
       DplLexer::Identifier,
       DplParser::RulePlusexpr,
       DplLexer::Identifier,
       DplLexer::Integer,
       DplParser::RuleElsestm,
       DplParser::RuleIfstm,
       DplParser::RuleCompexpr,
       DplParser::RuleIndex,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplParser::RuleProccall,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplParser::RuleAssignstm,
       DplLexer::Identifier,
       DplParser::RulePlusexpr,
       DplLexer::Identifier,
       DplLexer::Integer,
       DplParser::RuleElsestm,
       DplParser::RuleAssignstm,
       DplLexer::Identifier,
       DplParser::RulePlusexpr,
       DplLexer::Identifier,
       DplLexer::Integer,
       DplParser::RuleReturnstm,
       DplParser::RuleList,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplParser::RuleProcdec,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplParser::RuleAssignstm,
       DplLexer::Identifier,
       DplParser::RuleIndex,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplParser::RuleAssignstm,
       DplParser::RuleIndex,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplParser::RuleIndex,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplParser::RuleAssignstm,
       DplParser::RuleIndex,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplParser::RuleAssignstm,
       DplLexer::Identifier,
       DplParser::RuleList,
       DplLexer::Integer,
       DplLexer::Integer,
       DplLexer::Integer,
       DplLexer::Integer,
       DplLexer::Integer,
       DplLexer::Integer,
       DplLexer::Integer,
       DplLexer::Integer,
       DplLexer::Integer,
       DplLexer::Integer,
       DplLexer::Integer,
       DplParser::RuleProccall,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplLexer::Integer,
       DplParser::RulePlusexpr,
       DplParser::RuleProccall,
       DplLexer::Identifier,
       DplLexer::Identifier,
       DplLexer::Integer,
       DplParser::RuleProccall,
       DplLexer::Identifier,
       DplParser::RulePlusexpr,
       DplLexer::String,
       DplParser::RuleProccall,
       DplLexer::Identifier,
    };
    
    dplutil::TestingUtil::testAst("quicksort.dpl", expectedNodeRules);
}