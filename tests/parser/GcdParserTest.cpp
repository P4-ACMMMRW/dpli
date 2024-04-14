#include <TestingUtil.hpp>

using namespace dplgrammar;

PARSER_TEST("gcd.dpl") {
    std::vector<size_t> expectedNodeRules = {
        DplParser::RuleProcdec,
        DplParser::RuleParams,
        DplParser::RuleStm,
        DplParser::RuleIfstm,
        DplParser::RuleExpr,
        DplParser::RuleExpr,
        DplParser::RuleBoolexpr,
        DplParser::RuleCompareopr,
        DplParser::RuleExpr,
        DplParser::RuleLiteral,
        DplParser::RuleStm,
        DplParser::RuleFlowstm,
        DplParser::RuleExpr,
        DplParser::RuleStm,
        DplParser::RuleFlowstm,
        DplParser::RuleExpr,
        DplParser::RuleProccall,
        DplParser::RuleArgs,
        DplParser::RuleExpr,
        DplParser::RuleExpr,
        DplParser::RuleExpr,
        DplParser::RuleArthexpr,
        DplParser::RuleExpr,
        DplParser::RuleStm,
        DplParser::RuleExpr,
        DplParser::RuleProccall,
        DplParser::RuleArgs,
        DplParser::RuleExpr,
        DplParser::RuleProccall,
        DplParser::RuleArgs,
        DplParser::RuleExpr,
        DplParser::RuleLiteral,
        DplParser::RuleExpr,
        DplParser::RuleLiteral
    };
    
    dplutil::TestingUtil::testParser("gcd.dpl", expectedNodeRules);
}