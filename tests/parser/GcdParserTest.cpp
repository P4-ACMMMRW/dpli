#include <TestingUtil.hpp>

using namespace dplgrammar;

PARSER_TEST("gcd.dpl") {
    std::vector<int> expectedNodeRules = {
        DplParser::RuleProcdec,
        DplParser::RuleParams,
        DplParser::RuleStm,
        DplParser::RuleStm,
        DplParser::RuleCtrlstm,
        DplParser::RuleExpr,
        DplParser::RuleExpr,
        DplParser::RuleBoolexpr,
        DplParser::RuleCompareopr,
        DplParser::RuleExpr,
        DplParser::RuleLiteral,
        DplParser::RuleStm,
        DplParser::RuleStm,
        DplParser::RuleFlowstm,
        DplParser::RuleStm,
        DplParser::RuleExpr,
        DplParser::RuleStm,
        DplParser::RuleFlowstm,
        DplParser::RuleStm,
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
    
    util::TestingUtil::testParser("gcd.dpl", expectedNodeRules);
}