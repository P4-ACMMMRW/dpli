#include <TestingUtil.hpp>

using namespace dplgrammar;

AST_TEST("gcd.dpl") {
    std::vector<size_t> expectedNodeRules = {
        DplParser::RuleProg,
        DplParser::RuleProcdec,
        DplLexer::Identifier,
        DplLexer::Identifier,
        DplParser::RuleIfstm,
        DplParser::RuleEqulexpr,
        DplLexer::Identifier,
        DplLexer::Integer,
        DplParser::RuleReturnstm,
        DplLexer::Identifier,
        DplParser::RuleReturnstm,
        DplParser::RuleProccall,
        DplLexer::Identifier,
        DplLexer::Identifier,
        DplParser::RuleMultexpr,
        DplLexer::Identifier,
        DplLexer::Identifier,
        DplParser::RuleProccall,
        DplLexer::Identifier,
        DplParser::RuleProccall,
        DplLexer::Identifier,
        DplLexer::Integer,
        DplLexer::Integer
    };
    
    dplutil::TestingUtil::testAst("gcd.dpl", expectedNodeRules);
}