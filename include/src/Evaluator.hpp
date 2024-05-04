#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include <DplLexer.h>

#include "AllNodeIncludes.hpp"
#include "AstVisitor.hpp"
#include "ProcedureTable.hpp"
#include "Value.hpp"
#include "VariableTable.hpp"

namespace dplsrc {
class Evaluator : public AstVisitor {
   public:
    Evaluator(bool verbose = false) : verbose(verbose) { initPtable(); }

    void visit(const std::shared_ptr<AndExprNode> &node) override;
    void visit(const std::shared_ptr<AssignNode> &node) override;
    void visit(const std::shared_ptr<ColumnNode> &node) override;
    void visit(const std::shared_ptr<DivExprNode> &node) override;
    void visit(const std::shared_ptr<ElseNode> &node) override;
    void visit(const std::shared_ptr<EqualExprNode> &node) override;
    void visit(const std::shared_ptr<ExpoExprNode> &node) override;
    void visit(const std::shared_ptr<FilterNode> &node) override;
    void visit(const std::shared_ptr<GreaterEqualExprNode> &node) override;
    void visit(const std::shared_ptr<GreaterExprNode> &node) override;
    void visit(const std::shared_ptr<HeaderIndexNode> &node) override;
    void visit(const std::shared_ptr<IfNode> &node) override;
    void visit(const std::shared_ptr<IndexNode> &node) override;
    void visit(const std::shared_ptr<IntersectionExprNode> &node) override;
    void visit(const std::shared_ptr<LeafNode> &node) override;
    void visit(const std::shared_ptr<LessEqualExprNode> &node) override;
    void visit(const std::shared_ptr<LessExprNode> &node) override;
    void visit(const std::shared_ptr<ListNode> &node) override;
    void visit(const std::shared_ptr<MinusExprNode> &node) override;
    void visit(const std::shared_ptr<MinusNode> &node) override;
    void visit(const std::shared_ptr<ModExprNode> &node) override;
    void visit(const std::shared_ptr<MultExprNode> &node) override;
    void visit(const std::shared_ptr<NotEqualExprNode> &node) override;
    void visit(const std::shared_ptr<NotNode> &node) override;
    void visit(const std::shared_ptr<OrExprNode> &node) override;
    void visit(const std::shared_ptr<ParNode> &node) override;
    void visit(const std::shared_ptr<PlusExprNode> &node) override;
    void visit(const std::shared_ptr<PlusNode> &node) override;
    void visit(const std::shared_ptr<ProcCallNode> &node) override;
    void visit(const std::shared_ptr<ProcDecNode> &node) override;
    void visit(const std::shared_ptr<ProgNode> &node) override;
    void visit(const std::shared_ptr<ReturnNode> &node) override;
    void visit(const std::shared_ptr<TableNode> &node) override;
    void visit(const std::shared_ptr<UnionExprNode> &node) override;
    void visit(const std::shared_ptr<WhileNode> &node) override;

    /**
     * @return the variable table
     */
    VariableTable getVtable() { return vtable; }

    /**
     * @return the procedure table
     */
    ProcedureTable getPtable() { return ptable; }

   private:
    VariableTable vtable = VariableTable();
    ProcedureTable ptable = ProcedureTable();
    bool verbose;

    /**
     * Initializes the procedures from the standard library of the language
     */
    void initPtable();
};

}  // namespace dplsrc

#endif
