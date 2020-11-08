#ifndef SINGLESSOLVER_H
#define SINGLESSOLVER_H

#include "recursivesolver.h"
#include "solver.h"

#include <pybind11/pybind11.h>
#include <algorithm>
#include <set>

namespace SudokuSolve {

class SinglesSolver : public RecursiveSolver
{
public:
    SinglesSolver(Sudoku & rSudoku, const int max_iter, const int debug_lvl)
        : RecursiveSolver(rSudoku, max_iter, debug_lvl,  {SolverConfig("HiddenSinglesSolver", 1, 0), SolverConfig("NakedSinglesSolver", 1, 0)})
        {};
    SinglesSolver(std::shared_ptr<Sudoku> & pSudoku, const int max_iter, const int debug_lvl)
        : RecursiveSolver(pSudoku, max_iter, debug_lvl, {SolverConfig("HiddenSinglesSolver", 1, 0), SolverConfig("NakedSinglesSolver", 1, 0)})
        {};

    SinglesSolver(Sudoku & rSudoku, const SolverConfig config)
        : SinglesSolver(rSudoku, config.max_iter, config.debug_lvl) {};
    SinglesSolver(std::shared_ptr<Sudoku> & pSudoku, const SolverConfig config)
        : SinglesSolver(pSudoku, config.max_iter, config.debug_lvl) {};

    std::string GetDescription() const override;
    bool IterateOnce() override;
protected:
    void LinkSolvers();
};

} // namespace SudokuSolve

#endif // SINGLESSOLVER_H
