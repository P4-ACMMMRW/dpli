#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include <DplLexer.h>

#include <cmath>
#include <filesystem>
#include <string>
#include <utility>

#include "AllNodeIncludes.hpp"
#include "AstVisitor.hpp"
#include "BreakValue.hpp"
#include "ContinueValue.hpp"
#include "ProcedureTable.hpp"
#include "ReturnValue.hpp"
#include "RuntimeException.hpp"
#include "Value.hpp"
#include "VariableTable.hpp"

namespace dplsrc {
class Evaluator : public AstVisitor {
   public:
    Evaluator(bool verbose = false) : verbose(verbose) { initStdlib(); }

    void visit(const std::shared_ptr<AndExprNode> &node) override;
    void visit(const std::shared_ptr<AssignNode> &node) override;
    void visit(const std::shared_ptr<BreakNode> &node) override;
    void visit(const std::shared_ptr<ColumnNode> &node) override;
    void visit(const std::shared_ptr<ContinueNode> &node) override;
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
    void initStdlib();

    /**
     * Makes a deep copy of a list using DFS
     * @param list the list to copy
     * @return the copied list
     */
    Value::LIST copyList(const Value::LIST &list);

    /**
     * Makes a deep copy of a table using DFS
     * @param table the table to copy
     * @return the copied table
     */
    Value::TABLE copyTable(const Value::TABLE &table);

    /**
     * Executes body of loop taking into account the possibility of break and continue
     * @return true if break encountered, else false.
     */
    bool loopBody(std::vector<std::shared_ptr<AstNode>> bodyNodes);

    /**
     * @return true if i'th row of leftTable and j'th row of rightTable intersect (is the same).
     */
    static bool rowsIntersect(const Value::TABLE &leftTable, const Value::TABLE &rightTable,
                              size_t i, size_t j);

    /**
     * Adds the content of the i'th row of the table parameter to the sudo table cols.
     */
    static void addDataToCols(
        const Value::TABLE &table,
        std::vector<std::shared_ptr<std::vector<std::shared_ptr<dplsrc::Value>>>> &cols, size_t i);

    /**
     * Add union of columns to a table,
     * if the first column doesn't exist a corresponding amount of None is addded to the table.
     */
    static void addColUnionToTable(Value::TABLE &table,
                                   const std::shared_ptr<dplsrc::Value::COL_STRUCT> &col1,
                                   const std::shared_ptr<dplsrc::Value::COL_STRUCT> &col2,
                                   const Value::STR &header);

    /**
     * Adds null Values to a Value::List
     */
    static void addNullValuesToList(
        const std::shared_ptr<std::vector<std::shared_ptr<dplsrc::Value>>> &list, size_t size);

    /**
     * Adds a list of values to another list of values
     */
    static void addListToList(
        const std::shared_ptr<std::vector<std::shared_ptr<dplsrc::Value>>> &srcList,
        const std::shared_ptr<std::vector<std::shared_ptr<dplsrc::Value>>> &dstList);

    /**
     * Inserts a new column into the given table
     */
    static void insertColInTable(const Value::TABLE &table, const std::string &header,
                                 Value::LIST list);

    /**
     * @param leftTable
     * @param rightTable
     * @return true if the tables have the same columns
     */
    static bool isSameColumns(const Value::TABLE &leftTable, const Value::TABLE &rightTable);

    /**
     * @param leftTable
     * @param rightTable
     * @return a coloumn corresponding to the header in the given table, if no hit nullptr.
     */
    static Value::COLUMN getColumnByHeader(const Value::TABLE &table, const std::string &header);
};

}  // namespace dplsrc

#endif