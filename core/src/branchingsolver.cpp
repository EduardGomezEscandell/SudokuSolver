#include "branchingsolver.h"

namespace SudokuSolve {


BranchingSolver::BranchingSolver(Sudoku & rSudoku, const int max_iter, const int debug_lvl, const std::vector<SolverConfig> & rSolvers)
    : RecursiveSolver(rSudoku, max_iter, debug_lvl, rSolvers)
{
}

bool BranchingSolver::IterateOnce()
{

}


} //namespace SudokuSolve
