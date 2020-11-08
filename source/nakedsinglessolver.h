#ifndef NAKEDSINGLESSOLVER_H
#define NAKEDSINGLESSOLVER_H

#include "solver.h"
#include "exceptions.h"

namespace SudokuSolve {

class NakedSinglesSolver : public Solver
{
public:
    NakedSinglesSolver(Sudoku & rSudoku, const int max_iter, const int debug_lvl)
        : Solver(rSudoku, max_iter, debug_lvl){};
    NakedSinglesSolver(std::shared_ptr<Sudoku> & pSudoku, const int max_iter, const int debug_lvl)
        : Solver(pSudoku, max_iter, debug_lvl){};

    NakedSinglesSolver(Sudoku & rSudoku, const SolverConfig config)
        : NakedSinglesSolver(rSudoku, config.max_iter, config.debug_lvl) {};
    NakedSinglesSolver(std::shared_ptr<Sudoku> & pSudoku, const SolverConfig config)
        : NakedSinglesSolver(pSudoku, config.max_iter, config.debug_lvl) {};

    std::string GetDescription() const override;
    bool IterateOnce() override;

protected:
    void NakedSingleInRow(int row);
    void NakedSingleInCol(int col);
    void NakedSingleInBox(int box);
};

} // namespace SudokuSolve

#endif // NAKEDSINGLESSOLVER_H
