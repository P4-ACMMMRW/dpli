#include "TestingUtil.hpp"

using namespace dplgrammar;

PARSER_TEST("gcd.dpl") {
    std::vector<size_t> expectedNodeRules = {
        DplParser::RuleProcdec,
        DplParser::RuleParams,
        DplParser::RuleBlock,
        DplParser::RuleStms,
        DplParser::RuleStm,
        DplParser::RuleIfstm,
        DplParser::RuleOrexpr,
        DplParser::RuleAndexpr,
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
        DplParser::RuleCompexpr,
        DplParser::RulePlusexpr,
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleNumber,
        DplParser::RuleBlock,
        DplParser::RuleStms,
        DplParser::RuleStm,
        DplParser::RuleReturnstm,
        DplParser::RuleOrexpr,
        DplParser::RuleAndexpr,
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
        DplParser::RuleReturnstm,
        DplParser::RuleOrexpr,
        DplParser::RuleAndexpr,
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
        DplParser::RuleOrexpr,
        DplParser::RuleAndexpr,
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
        DplParser::RuleOrexpr,
        DplParser::RuleAndexpr,
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
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleSubscript,
        DplParser::RuleStm,
        DplParser::RuleOrexpr,
        DplParser::RuleAndexpr,
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
        DplParser::RuleOrexpr,
        DplParser::RuleAndexpr,
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
        DplParser::RuleOrexpr,
        DplParser::RuleAndexpr,
        DplParser::RuleNotexpr,
        DplParser::RuleEqulexpr,
        DplParser::RuleCompexpr,
        DplParser::RulePlusexpr,
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleNumber,
        DplParser::RuleOrexpr,
        DplParser::RuleAndexpr,
        DplParser::RuleNotexpr,
        DplParser::RuleEqulexpr,
        DplParser::RuleCompexpr,
        DplParser::RulePlusexpr,
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleNumber
    };
    
    dplutil::TestingUtil::testParser("gcd.dpl", expectedNodeRules);
}