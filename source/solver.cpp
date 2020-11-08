#include "solver.h"
#include "exceptions.h"
#include <pybind11/pybind11.h>

namespace SudokuSolve {

Solver::Solver(Sudoku & rSudoku, const int max_iter, const int debug_lvl) :
    mMaxIter {max_iter},
    mDebugLvl{(Debug) debug_lvl},
    mpSudoku {std::make_shared<Sudoku>(rSudoku)}
{
}

Solver::Solver(std::shared_ptr<Sudoku> & pSudoku, const int max_iter, const int debug_lvl) :
    mMaxIter {max_iter},
    mDebugLvl{(Debug) debug_lvl},
    mpSudoku {pSudoku}
{
}

void Solver::SwitchSudoku(std::shared_ptr<Sudoku> & pSudoku)
{
    mpSudoku = pSudoku;
}

void Solver::Execute()
{
    bool finished = false;
    double uncertainty = mpSudoku->GetUncertainty();
    for(mIters=0; mIters < mMaxIter && !finished; mIters++)
    {
        finished = IterateOnce();
        PRINT(Debug::full, mpSudoku->ToString());
        double new_uncertainty = mpSudoku->GetUncertainty();
        if(new_uncertainty == uncertainty)
        {
            throw CannotProgressError(mIters);
        }
        uncertainty = new_uncertainty;
    }
}

bool Solver::IterateOnce()
{
    throw SolveError("Attempting to use superclass to solve.");
}

void Solver::Finalize()
{
    if(mIters == mMaxIter-1) throw ReachedMaxIterError();

    std::stringstream ss;
    ss << "SOLUTION"<<std::endl<<mpSudoku->ToString()<<std::endl<<mIters<<" iterations employed"<<std::endl;
    PRINT(Debug::results, ss.str());

    if(mpSudoku->GetUncertainty() > 0) throw SolveError("Failed to reduce all uncertainty");
}

Sudoku & Solver::GetSudoku()
{
    return *mpSudoku;
}

std::string Solver::ToString() const
{
    std::stringstream ss;
    ss << GetDescription() <<"\nMax iter : "<<mMaxIter<<"\nDebug_lvl : "<<(int)mDebugLvl<<"\n";
    return ss.str();
}

std::string Solver::GetDescription() const
{
    return "Solver: Base class for solvers";
}

int Solver::GetIter()
{
    return mIters;
}


} // namespace SudokuSolve
