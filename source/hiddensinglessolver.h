#ifndef HIDDENSINGLESSOLVER_H
#define HIDDENSINGLESSOLVER_H

#include "solver.h"
#include "exceptions.h"

namespace SudokuSolve {

class HiddenSinglesSolver : public Solver
{
public:
    HiddenSinglesSolver(Sudoku & rSudoku, const int max_iter, const int debug_lvl)
        : Solver(rSudoku, max_iter, debug_lvl){};
    HiddenSinglesSolver(std::shared_ptr<Sudoku> & pSudoku, const int max_iter, const int debug_lvl)
        : Solver(pSudoku, max_iter, debug_lvl){};

    HiddenSinglesSolver(Sudoku & rSudoku, const SolverConfig config)
        : HiddenSinglesSolver(rSudoku, config.max_iter, config.debug_lvl) {};
    HiddenSinglesSolver(std::shared_ptr<Sudoku> & pSudoku, const SolverConfig config)
        : HiddenSinglesSolver(pSudoku, config.max_iter, config.debug_lvl) {};

    std::string GetDescription() const override;
    bool IterateOnce() override;

protected:
    void HiddenSingleInRow(int row);
    void HiddenSingleInCol(int col);
    void HiddenSingleInBox(int box);
};

} // namespace SudokuSolve

#endif // HIDDENSINGLESSOLVER_H
