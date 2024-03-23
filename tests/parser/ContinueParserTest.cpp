#include <TestingUtil.hpp>

using namespace dplgrammar;

PARSER_TEST("continue.dpl") {
    std::vector<int> expectedNodeRules = {
        DplParser::RuleProg,
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
        DplParser::RuleStm,
        DplParser::RuleAssignstm,
        DplParser::RuleExpr,
        DplParser::RuleExpr,
        DplParser::RuleArthexpr,
        DplParser::RuleExpr,
        DplParser::RuleLiteral,
        DplParser::RuleStm,
        DplParser::RuleCtrlstm,
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
        DplParser::RuleStm,
        DplParser::RuleFlowstm,
        DplParser::RuleStm,
        DplParser::RuleExpr,
        DplParser::RuleStm,
        DplParser::RuleExpr,
        DplParser::RuleExpr,
    };
    
    util::TestingUtil::testParser("continue.dpl", expectedNodeRules);
}