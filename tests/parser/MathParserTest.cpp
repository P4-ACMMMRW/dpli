#include <TestingUtil.hpp>

using namespace dplgrammar;

PARSER_TEST("math.dpl") {
    std::vector<size_t> expectedNodeRules = {
        DplParser::RuleStm,
        DplParser::RuleAssignstm,
        DplParser::RuleSubscript,
        DplParser::RuleJuncexpr,
        DplParser::RuleNotexpr,
        DplParser::RuleEqulexpr,
        DplParser::RuleCompexpr,
        DplParser::RulePlusexpr,
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleTerm,
        DplParser::RuleStm,
        DplParser::RuleAssignstm,
        DplParser::RuleSubscript,
        DplParser::RuleJuncexpr,
        DplParser::RuleNotexpr,
        DplParser::RuleEqulexpr,
        DplParser::RuleCompexpr,
        DplParser::RulePlusexpr,
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleStm,
        DplParser::RuleAssignstm,
        DplParser::RuleSubscript,
        DplParser::RuleJuncexpr,
        DplParser::RuleNotexpr,
        DplParser::RuleEqulexpr,
        DplParser::RuleCompexpr,
        DplParser::RulePlusexpr,
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleStm,
        DplParser::RuleAssignstm,
        DplParser::RuleSubscript,
        DplParser::RuleJuncexpr,
        DplParser::RuleNotexpr,
        DplParser::RuleEqulexpr,
        DplParser::RuleCompexpr,
        DplParser::RulePlusexpr,
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleStm,
        DplParser::RuleJuncexpr,
        DplParser::RuleNotexpr,
        DplParser::RuleEqulexpr,
        DplParser::RuleCompexpr,
        DplParser::RulePlusexpr,
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleSubscript,
        DplParser::RuleProccall,
        DplParser::RuleArgs,
        DplParser::RuleJuncexpr,
        DplParser::RuleNotexpr,
        DplParser::RuleEqulexpr,
        DplParser::RuleCompexpr,
        DplParser::RulePlusexpr,
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleSubscript,
        DplParser::RuleStm,
        DplParser::RuleJuncexpr,
        DplParser::RuleNotexpr,
        DplParser::RuleEqulexpr,
        DplParser::RuleCompexpr,
        DplParser::RulePlusexpr,
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleSubscript,
        DplParser::RuleProccall,
        DplParser::RuleArgs,
        DplParser::RuleJuncexpr,
        DplParser::RuleNotexpr,
        DplParser::RuleEqulexpr,
        DplParser::RuleCompexpr,
        DplParser::RulePlusexpr,
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleSubscript,
        DplParser::RuleStm,
        DplParser::RuleJuncexpr,
        DplParser::RuleNotexpr,
        DplParser::RuleEqulexpr,
        DplParser::RuleCompexpr,
        DplParser::RulePlusexpr,
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleSubscript,
        DplParser::RuleProccall,
        DplParser::RuleArgs,
        DplParser::RuleJuncexpr,
        DplParser::RuleNotexpr,
        DplParser::RuleEqulexpr,
        DplParser::RuleCompexpr,
        DplParser::RulePlusexpr,
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleSubscript,
        DplParser::RuleStm,
        DplParser::RuleJuncexpr,
        DplParser::RuleNotexpr,
        DplParser::RuleEqulexpr,
        DplParser::RuleCompexpr,
        DplParser::RulePlusexpr,
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleSubscript,
        DplParser::RuleProccall,
        DplParser::RuleArgs,
        DplParser::RuleJuncexpr,
        DplParser::RuleNotexpr,
        DplParser::RuleEqulexpr,
        DplParser::RuleCompexpr,
        DplParser::RulePlusexpr,
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleSubscript
    };
    
    dplutil::TestingUtil::testParser("math.dpl", expectedNodeRules);
}