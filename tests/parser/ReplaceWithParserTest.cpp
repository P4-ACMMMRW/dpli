#include <TestingUtil.hpp>

using namespace dplgrammar;

PARSER_TEST("replace_with.dpl") {
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
        DplParser::RuleTable,
        DplParser::RuleColumn,
        DplParser::RuleList,
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
        DplParser::RuleColumn,
        DplParser::RuleList,
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
        DplParser::RuleColumn,
        DplParser::RuleList,
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
        DplParser::RuleSubscript,
        DplParser::RuleHeaderindex,
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
        DplParser::RuleFiltering,
        DplParser::RuleUnaryexpr,
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
        DplParser::RuleStm,
        DplParser::RuleAssignstm,
        DplParser::RuleSubscript,
        DplParser::RuleHeaderindex,
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
        DplParser::RuleHeaderindex,
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
        DplParser::RuleSubscript,
        DplParser::RuleHeaderindex,
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
        DplParser::RuleSubscript,
        DplParser::RuleHeaderindex,
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
        DplParser::RuleFiltering,
        DplParser::RuleUnaryexpr,
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
        DplParser::RuleHeaderindex,
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
    
    dplutil::TestingUtil::testParser("replace_with.dpl", expectedNodeRules);
}