#include "nakedsinglessolver.h"

namespace SudokuSolve {

inline std::string NakedSinglesSolver::GetDescription() const
{
    return "NakedSinglesSolver: A logic-based solver that removes candidates by single-available-cell-solution";
}

bool NakedSinglesSolver::IterateOnce()
{
    double old_uncertainty = mpSudoku->GetUncertainty();

    for(int i=1; i<10; i++)
    {
        NakedSingleInRow(i);
        NakedSingleInCol(i);
        NakedSingleInBox(i);
    }

    double uncertainty = mpSudoku->GetUncertainty();

    if(uncertainty == old_uncertainty)
    {
        throw CannotProgressError(mIters);
    }

    if(uncertainty==0)
    {
        PRINT(Debug::info, "Solved!");
        return true;
    }
    std::stringstream ss;
    ss << "Step "<<mIters<<": Reduced uncertainty down to " << mpSudoku->GetUncertainty();
    PRINT(Debug::info, ss.str());
    return false;
}



void NakedSinglesSolver::NakedSingleInRow(const int row)
{
    if(!ValueWithin(row,1,9)) throw py::index_error("Tried to access invalid row");
    if(mpSudoku->mKnownRows[row-1]) return;

    std::set<int> known_values;
    for(int col = 1; col < 10; col++)
    {
        const Cell & cell = (*mpSudoku)(row, col);
        if(cell.IsSolved())
        {
            const int & value = cell.GetValue();
            known_values.insert(value);
            // Propagating knowledge backwards
            for(int ctarget=1; ctarget<col; ctarget++)
            {
                (*mpSudoku)(row, ctarget).PopCandidate(value);
            }
        } else {
            // Propagating knowledge forwards
           (*mpSudoku)(row, col).PopCandidates(known_values);
        }
    }
}

void NakedSinglesSolver::NakedSingleInCol(const int col)
{
    if(!ValueWithin(col,1,9)) throw py::index_error("Tried to access invalid column");
    if(mpSudoku->mKnownCols[col-1]) return;

    std::set<int> known_values;
    for(int row = 1; row < 10; row++)
    {
        const Cell & cell = (*mpSudoku)(row, col);
        if(cell.IsSolved())
        {
            const int & value = cell.GetValue();
            known_values.insert(value);
            // Propagating knowledge backwards
            for(int rtarget=1; rtarget<row; rtarget++)
            {
                (*mpSudoku)(rtarget, col).PopCandidate(value);
            }
        } else {
            // Propagating knowledge forwards
           (*mpSudoku)(row, col).PopCandidates(known_values);
        }
    }
}

void NakedSinglesSolver::NakedSingleInBox(int box)
{
    if(!ValueWithin(box,1,9)) throw py::index_error("Tried to access invalid box");
    if(mpSudoku->mKnownBoxes[box-1]) return;

    std::set<int> known_values;
    for(int entry = 1; entry < 10; entry++)
    {
        const Cell & cell = mpSudoku->AccessByBox(box, entry);
        if(cell.IsSolved())
        {
            const int & value = cell.GetValue();
            known_values.insert(value);
            // Propagating knowledge backwards
            for(int etarget=1; etarget<entry; etarget++)
            {
                mpSudoku->AccessByBox(box, etarget).PopCandidate(value);
            }
        } else {
            // Propagating knowledge forwards
           mpSudoku->AccessByBox(box, entry).PopCandidates(known_values);
        }
    }
}


} // namespace SudokuSolve
