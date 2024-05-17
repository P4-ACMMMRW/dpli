#include "TestingUtil.hpp"

using namespace dplgrammar;

PARSER_TEST("quicksort.dpl") {
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
        DplParser::RulePlusexpr,
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleNumber,
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
        DplParser::RulePlusexpr,
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleSubscript,
        DplParser::RuleBlock,
        DplParser::RuleStms,
        DplParser::RuleStm,
        DplParser::RuleAssignstm,
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
        DplParser::RuleIndex,
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
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleNumber,
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
        DplParser::RuleIndex,
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
        DplParser::RuleSubscript,
        DplParser::RuleProcdec,
        DplParser::RuleParams,
        DplParser::RuleBlock,
        DplParser::RuleStms,
        DplParser::RuleStm,
        DplParser::RuleAssignstm,
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
        DplParser::RuleIndex,
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
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleSubscript,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleNumber,
        DplParser::RuleStm,
        DplParser::RuleAssignstm,
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
        DplParser::RuleStm,
        DplParser::RuleAssignstm,
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
        DplParser::RuleStm,
        DplParser::RuleAssignstm,
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
        DplParser::RuleStm,
        DplParser::RuleWhilestm,
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
        DplParser::RulePlusexpr,
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleSubscript,
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
        DplParser::RuleIndex,
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
        DplParser::RulePlusexpr,
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleSubscript,
        DplParser::RuleBlock,
        DplParser::RuleStms,
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
        DplParser::RuleStm,
        DplParser::RuleAssignstm,
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
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleNumber,
        DplParser::RuleStm,
        DplParser::RuleAssignstm,
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
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleNumber,
        DplParser::RuleElsestm,
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
        DplParser::RuleIndex,
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
        DplParser::RulePlusexpr,
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleSubscript,
        DplParser::RuleBlock,
        DplParser::RuleStms,
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
        DplParser::RuleStm,
        DplParser::RuleAssignstm,
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
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleNumber,
        DplParser::RuleElsestm,
        DplParser::RuleBlock,
        DplParser::RuleStms,
        DplParser::RuleStm,
        DplParser::RuleAssignstm,
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
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleNumber,
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
        DplParser::RuleList,
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
        DplParser::RuleProcdec,
        DplParser::RuleParams,
        DplParser::RuleBlock,
        DplParser::RuleStms,
        DplParser::RuleStm,
        DplParser::RuleAssignstm,
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
        DplParser::RuleIndex,
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
        DplParser::RuleAssignstm,
        DplParser::RuleSubscript,
        DplParser::RuleIndex,
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
        DplParser::RuleIndex,
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
        DplParser::RuleAssignstm,
        DplParser::RuleSubscript,
        DplParser::RuleIndex,
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
        DplParser::RuleStm,
        DplParser::RuleAssignstm,
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
        DplParser::RuleList,
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
        DplParser::RuleNumber,
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
        DplParser::RuleTablexpr,
        DplParser::RuleMultexpr,
        DplParser::RulePolaexpr,
        DplParser::RuleExpoexpr,
        DplParser::RuleTerm,
        DplParser::RuleNumber,
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
    };
    
    dplutil::TestingUtil::testParser("quicksort.dpl", expectedNodeRules);
}