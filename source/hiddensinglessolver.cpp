#include "hiddensinglessolver.h"

namespace SudokuSolve {

inline std::string HiddenSinglesSolver::GetDescription() const
{
    return "HiddenSinglesSolver: A logic-based solver that removes candidates by same-house-elimination";
}

bool HiddenSinglesSolver::IterateOnce()
{
   for(int i=1; i<10; i++)
    {
        HiddenSingleInRow(i);
        HiddenSingleInCol(i);
        HiddenSingleInBox(i);
    }

    double uncertainty = mpSudoku->GetUncertainty();

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

void HiddenSinglesSolver::HiddenSingleInRow(int row)
{
    if(!ValueWithin(row,1,9)) throw py::index_error("Tried to access invalid row");
    if(mpSudoku->mKnownRows[row-1]) return;

    std::vector<std::list<int>> possible_cols_per_candidate(9);
    // Logging where each number 1-9 is a candidate
    for(int col=1; col<10; col++)
    {
        Cell & cell = (*mpSudoku)(row, col);
        for(int & candidate : cell.GetCandidates())
        {
            possible_cols_per_candidate[candidate-1].push_back(col);
        }
    }
    // Solving all cells with unique candidates
    for(int candidate=1; candidate<10; candidate++)
    {
        std::list<int> & possible_cols = possible_cols_per_candidate[candidate-1];
        if(possible_cols.size() == 1)
        {
            Cell & cell = (*mpSudoku)(row, possible_cols.front());
            if(!cell.IsSolved()) cell.Solve(candidate);
        }
    }
}


void HiddenSinglesSolver::HiddenSingleInCol(int col)
{
    if(!ValueWithin(col,1,9)) throw py::index_error("Tried to access invalid row");
    if(mpSudoku->mKnownCols[col-1]) return;

    std::vector<std::list<int>> possible_rows_per_candidate(9);
    // Logging where each number 1-9 is a candidate
    for(int row=1; row<10; row++)
    {
        Cell & cell = (*mpSudoku)(row, col);
        for(int & candidate : cell.GetCandidates())
        {
            possible_rows_per_candidate[candidate-1].push_back(row);
        }
    }
    // Solving all cells with unique candidates
    for(int candidate=1; candidate<10; candidate++)
    {
        std::list<int> & possible_rows = possible_rows_per_candidate[candidate-1];
        if(possible_rows.size() == 1)
        {
            Cell & cell = (*mpSudoku)(possible_rows.front(), col);
            if(!cell.IsSolved()) cell.Solve(candidate);
        }
    }
}


void HiddenSinglesSolver::HiddenSingleInBox(int box)
{
    if(!ValueWithin(box,1,9)) throw py::index_error("Tried to access invalid row");
    if(mpSudoku->mKnownBoxes[box-1]) return;

    std::vector<std::list<int>> possible_entries_per_candidate(9);
    // Logging where each number 1-9 is a candidate
    for(int entry=1; entry<10; entry++)
    {
        Cell & cell = mpSudoku->AccessByBox(box, entry);
        for(int & candidate : cell.GetCandidates())
        {
            possible_entries_per_candidate[candidate-1].push_back(entry);
        }
    }
    // Solving all cells with unique candidates
    for(int candidate=1; candidate<10; candidate++)
    {
        std::list<int> & possible_entries = possible_entries_per_candidate[candidate-1];
        if(possible_entries.size() == 1)
        {
            Cell & cell = mpSudoku->AccessByBox(box, possible_entries.front());
            if(!cell.IsSolved()) cell.Solve(candidate);
        }
    }
}

} //namespace SudokuSolve
