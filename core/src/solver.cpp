#include "solver.h"
#include "exceptions.h"
#include <pybind11/pybind11.h>

namespace SudokuSolve {

Solver::Solver(Sudoku & rSudoku, const int max_iter, const int debug_lvl) :
    mMaxIter {max_iter},
    mDebugLvl{(Debug) debug_lvl},
    mpSudoku {&rSudoku}
{
}

void Solver::SwitchSudoku(Sudoku & rSudoku)
{
    mpSudoku = &rSudoku;
    for(Solver & rS : mChildSolvers)
    {
        rS.SwitchSudoku(rSudoku);
    }
}

void Solver::Execute()
{
    bool finished = false;
    for(mIters=0; mIters < mMaxIter && !finished; mIters++)
    {
        finished = IterateOnce();
    }
}

bool Solver::IterateOnce()
{
    throw SolveError("Attempting to use superclass to solve.");
}

void Solver::Finalize()
{
    if(mIters == mMaxIter-1) throw ReachedMaxIterError();

    PRINT(Debug::none,"SOLUTION"<<std::endl<<mpSudoku->ToString()<<std::endl<<mIters<<" iterations employed"<<std::endl);

    if(mpSudoku->GetUncertainty() > 0) throw SolveError("Failed to reduce all uncertainty");
}

Sudoku & Solver::GetSudoku()
{
    return *mpSudoku;
}

std::string Solver::ToString()
{
    std::stringstream ss;
    ss << GetDescription() <<"\nMax iter : "<<mMaxIter<<"\nDebug_lvl : "<<(int)mDebugLvl<<"\n"<<mpSudoku->ToString()<<"";
    return ss.str();
}

std::string Solver::GetDescription() const
{
    return "Base class for solvers";
}


} // namespace SudokuSolve
