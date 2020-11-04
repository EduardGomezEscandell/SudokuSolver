#include "recursivesolver.h"

// Including all non-base solvers
#include "singlessolver.h"
#include "branchingsolver.h"

namespace SudokuSolve {

Solver * ChooseSolver(std::shared_ptr<Sudoku> pSudoku, const SolverConfig & config)
{
    if(config.name.size() == 0)
    {
        throw py::value_error("Child solvers require their name to be inputed in the SolverConfig object");
    }

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

RecursiveSolver::RecursiveSolver(std::shared_ptr<Sudoku> & pSudoku, const int max_iter, const int debug_lvl, const SolverConfig & rChild) : Solver(pSudoku, max_iter, debug_lvl)
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

RecursiveSolver::RecursiveSolver(std::shared_ptr<Sudoku> & pSudoku, const int max_iter, const int debug_lvl, const std::vector<SolverConfig> & rChildren)
    : Solver(pSudoku, max_iter, debug_lvl)
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

std::string RecursiveSolver::ToString() const
{
    std::stringstream ss;
    ss << Solver::ToString() << "\nChild solvers:\n";
    for(Solver * solver : mChildSolvers)
    {
        ss << "--------------------------\n";
        ss << solver->ToString();
    }
    ss << "--------------------------\n";
    return ss.str();
}

void RecursiveSolver::SwitchSudoku(std::shared_ptr<Sudoku> & pSudoku)
{
    mpSudoku = pSudoku;
    for(Solver* rS : mChildSolvers)
    {
        rS->SwitchSudoku(pSudoku);
    }
}


std::string RecursiveSolver::GetDescription() const
{
    return "Base class for recursive solvers";
}


void RecursiveSolver::AddChildSolver(SolverConfig config)
{
    Solver * child = ChooseSolver(mpSudoku, config);
    mChildSolvers.push_back(child);
}


} // namespace SudokuSolve
