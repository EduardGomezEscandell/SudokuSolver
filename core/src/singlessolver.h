#ifndef SINGLESSOLVER_H
#define SINGLESSOLVER_H

#include "solver.h"

#include <pybind11/pybind11.h>
#include <algorithm>
#include <set>

namespace SudokuSolve {

#define FALSE9 {false, false, false, false, false, false, false, false, false}

class SinglesSolver : public Solver
{
public:
    SinglesSolver(Sudoku & rSudoku, const int max_iter, const int debug_lvl) : Solver(rSudoku, max_iter, debug_lvl){};
    SinglesSolver(Sudoku & rSudoku, const SolverConfig config) : SinglesSolver(rSudoku, config.max_iter, config.debug_lvl) {};
    std::string GetDescription() const override;
    bool IterateOnce() override;
protected:
    bool mKnownRows [9] = FALSE9;
    bool mKnownCols [9] = FALSE9;
    bool mKnownBoxes [9] = FALSE9;

    void NakedSingleInRow(int row);
    void NakedSingleInCol(int col);
    void NakedSingleInBox(int box);

    void HiddenSingleInRow(int row);
    void HiddenSingleInCol(int col);
    void HiddenSingleInBox(int box);
};

} // namespace SudokuSolve

#endif // SINGLESSOLVER_H
