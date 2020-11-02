#include "recursivesolver.h"

// Including all non-base solvers
#include "singlessolver.h"
#include "branchingsolver.h"

namespace SudokuSolve {

Solver * ChooseSolver(Sudoku & rSudoku, const SolverConfig & config)
{
    // This list should contain all non-virtual solvers
    IF_SOLVER_RETURN_NEW("SinglesSolver",   SinglesSolver);
    IF_SOLVER_RETURN_NEW("BranchingSolver", BranchingSolver);

    std::stringstream msg;
    msg << "The child " << config.name << " does not match any known solver";
    throw py::key_error(msg.str());
}

RecursiveSolver::RecursiveSolver(Sudoku & rSudoku, const int max_iter, const int debug_lvl, const SolverConfig & rChild) : Solver(rSudoku, max_iter, debug_lvl)
{
    AddChildSolver(rChild);
}


RecursiveSolver::RecursiveSolver(Sudoku & rSudoku, const int max_iter, const int debug_lvl, const std::vector<SolverConfig> & rChildren)
    : Solver(rSudoku, max_iter, debug_lvl)
{
    for(const SolverConfig & child_config : rChildren)
    {
        AddChildSolver(child_config);
    }
}

RecursiveSolver::~RecursiveSolver()
{
    for(Solver* rS : mChildSolvers)
    {
        delete rS;
    }
}

void RecursiveSolver::SwitchSudoku(Sudoku & rSudoku)
{
    mpSudoku = &rSudoku;
    for(Solver* rS : mChildSolvers)
    {
        rS->SwitchSudoku(rSudoku);
    }
}


std::string RecursiveSolver::GetDescription() const
{
    return "Base class for recursive solvers";
}


void RecursiveSolver::AddChildSolver(SolverConfig config)
{
    Solver * child = ChooseSolver(*mpSudoku, config);
    mChildSolvers.push_back(child);
}


} // namespace SudokuSolve
