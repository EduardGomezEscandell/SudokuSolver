#ifndef BRANCHINGSOLVER_H
#define BRANCHINGSOLVER_H

#include <list>
#include "recursivesolver.h"

namespace SudokuSolve {

class BranchingSolver : public RecursiveSolver
{
public:
    BranchingSolver(Sudoku & rSudoku, const int max_iter, const int debug_lvl, const std::vector<SolverConfig> & rChildren);
    BranchingSolver(Sudoku & rSudoku, const SolverConfig config) : BranchingSolver(rSudoku, config.max_iter, config.debug_lvl, config.children) {};
    bool IterateOnce() override;
protected:
    std::string GetDescription() const override;
};

} //namespace SudokuSolve

#endif // BRANCHINGSOLVER_H
