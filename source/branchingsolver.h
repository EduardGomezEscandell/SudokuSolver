#ifndef BRANCHINGSOLVER_H
#define BRANCHINGSOLVER_H

#include <list>
#include <memory>

#include "recursivesolver.h"
#include "exceptions.h"

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace SudokuSolve {

enum Status {solved,progressed,pushed,popped};

class BranchingSolver : public RecursiveSolver
{
public:
    BranchingSolver(Sudoku & rSudoku, const int max_iter, const int debug_lvl, const SolverConfig & rChild)
        : RecursiveSolver(rSudoku, max_iter, debug_lvl, rChild) {};
    BranchingSolver(std::shared_ptr<Sudoku> & pSudoku, const int max_iter, const int debug_lvl, const SolverConfig & rChild)
        : RecursiveSolver(pSudoku, max_iter, debug_lvl, rChild) {};

    BranchingSolver(Sudoku & rSudoku, const int max_iter, const int debug_lvl, const std::vector<SolverConfig> & rChildren)
        : RecursiveSolver(rSudoku, max_iter, debug_lvl, rChildren) {};
    BranchingSolver(std::shared_ptr<Sudoku> & pSudoku, const int max_iter, const int debug_lvl, const std::vector<SolverConfig> & rChildren)
        : RecursiveSolver(pSudoku, max_iter, debug_lvl, rChildren) {};

    BranchingSolver(Sudoku & rSudoku, const SolverConfig config)
        : BranchingSolver(rSudoku, config.max_iter, config.debug_lvl, config.children) {};
    BranchingSolver(std::shared_ptr<Sudoku> & pSudoku, const SolverConfig config)
        : BranchingSolver(pSudoku, config.max_iter, config.debug_lvl, config.children) {};

    bool IterateOnce() override;

protected:
    std::vector<std::shared_ptr<Sudoku>> mStack = {};

    std::string GetDescription() const override;

    void PrintStatus(const Status status);
    void PrintStatus(const Status status, const Cell * cell);

    void RevertBranch();
    Cell & TakeBranch();

};

} //namespace SudokuSolve

#endif // BRANCHINGSOLVER_H
