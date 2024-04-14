#include <TestingUtil.hpp>

using namespace dplgrammar;

PARSER_TEST("continue.dpl") {
    std::vector<size_t> expectedNodeRules = {
        DplParser::RuleStm,
        DplParser::RuleAssignstm,
        DplParser::RuleExpr,
        DplParser::RuleLiteral,
        DplParser::RuleStm,
        DplParser::RuleLoopstm,
        DplParser::RuleExpr,
        DplParser::RuleExpr,
        DplParser::RuleBoolexpr,
        DplParser::RuleCompareopr,
        DplParser::RuleExpr,
        DplParser::RuleLiteral,
        DplParser::RuleStm,
        DplParser::RuleAssignstm,
        DplParser::RuleExpr,
        DplParser::RuleExpr,
        DplParser::RuleArthexpr,
        DplParser::RuleExpr,
        DplParser::RuleLiteral,
        DplParser::RuleStm,
        DplParser::RuleIfstm,
        DplParser::RuleExpr,
        DplParser::RuleExpr,
        DplParser::RuleArthexpr,
        DplParser::RuleExpr,
        DplParser::RuleExpr,
        DplParser::RuleLiteral,
        DplParser::RuleBoolexpr,
        DplParser::RuleCompareopr,
        DplParser::RuleExpr,
        DplParser::RuleLiteral,
        DplParser::RuleStm,
        DplParser::RuleFlowstm,
        DplParser::RuleStm,
        DplParser::RuleExpr,
        DplParser::RuleProccall,
        DplParser::RuleArgs,
        DplParser::RuleExpr
    };
    
    dplutil::TestingUtil::testParser("continue.dpl", expectedNodeRules);
}