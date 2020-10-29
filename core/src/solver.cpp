#include "solver.h"
#include <pybind11/pybind11.h>

namespace SudokuSolve {

Solver::Solver(Sudoku & rSudoku, const int max_iter, const Debug debug_lvl)
{
    mpSudoku = &rSudoku;
    mMaxIter = max_iter;
    mDebugLvl = debug_lvl;
}

Solver::Solver(Sudoku & rSudoku, const int max_iter, const int debug_lvl)
{
    Debug debug = (Debug) debug_lvl;
    Solver(rSudoku, max_iter, debug);
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
    return false;
}

void Solver::Finalize()
{
    if(mIters == mMaxIter-1) throw py::stop_iteration();

    PRINT(Debug::none,"SOLUTION"<<std::endl<<mpSudoku->ToString()<<std::endl<<mIters<<" iterations employed"<<std::endl);
}

const Sudoku & Solver::GetSudoku()
{
    return *mpSudoku;
}

std::string Solver::ToString()
{
    std::stringstream ss;
    ss << GetDescription() <<"\nMax iter : "<<mMaxIter<<"\nDebug_lvl : "<<(int)mDebugLvl<<"\n"<<*mpSudoku<<"";
    return ss.str();
}

std::string Solver::GetDescription() const
{
    return "Base class for solvers";
}


} // namespace SudokuSolve
