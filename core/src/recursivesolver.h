#ifndef RECURSIVESOLVER_H
#define RECURSIVESOLVER_H

#define IF_SOLVER_RETURN_NEW(solvername, solver) if(config.name == solvername) return new solver(pSudoku, config)

#include "sudoku.h"
#include "solver.h"
#include "common.h"

#include<pybind11/pybind11.h>

namespace py = pybind11;

namespace SudokuSolve {

class RecursiveSolver : public Solver
{
public:
    RecursiveSolver(Sudoku & rSudoku, const int max_iter, const int debug_lvl, const SolverConfig & rChild);
    RecursiveSolver(std::shared_ptr<Sudoku> & pSudoku, const int max_iter, const int debug_lvl, const SolverConfig & rChild);

    RecursiveSolver(Sudoku & rSudoku, const int max_iter, const int debug_lvl, const std::vector<SolverConfig> & rChildren);
    RecursiveSolver(std::shared_ptr<Sudoku> & pSudoku, const int max_iter, const int debug_lvl, const std::vector<SolverConfig> & rChildren);

    RecursiveSolver(Sudoku & rSudoku, const SolverConfig config)
        : RecursiveSolver(rSudoku, config.max_iter, config.debug_lvl, config.children) {};
    RecursiveSolver(std::shared_ptr<Sudoku> & pSudoku, const SolverConfig config)
        : RecursiveSolver(pSudoku, config.max_iter, config.debug_lvl, config.children) {};

    virtual ~RecursiveSolver();
    virtual bool IterateOnce() override = 0;
    std::string ToString() const override;
    void SwitchSudoku(std::shared_ptr<Sudoku> & pSudoku) override;
protected:
    std::string GetDescription() const override;
    void AddChildSolver(SolverConfig config);
};

} // namespace SudokuSolve
#endif // RECURSIVESOLVER_H
