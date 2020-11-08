#include "singlessolver.h"
#include "exceptions.h"

namespace py = pybind11;

namespace SudokuSolve {

inline std::string SinglesSolver::GetDescription() const
{
    return "SinglesSolver: A logic-based solver that removes candidates by same-house-elimination and single-available-cell-solution";
}

bool SinglesSolver::IterateOnce()
{
    for(Solver * child : mChildSolvers)
    {
        bool no_uncertainty = child->IterateOnce();

        if(no_uncertainty)
        {
            PRINT(Debug::info, "Solved!");
            return true;
        }
    }

    std::stringstream ss;
    ss << "Step "<<mIters<<": Reduced uncertainty down to " << mpSudoku->GetUncertainty();
    PRINT(Debug::info, ss.str());
    return false;
}

} //namespace SudokuSolve
