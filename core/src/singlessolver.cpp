#include "singlessolver.h"
#include "exceptions.h"

namespace py = pybind11;

namespace SudokuSolve {

inline std::string SinglesSolver::GetDescription() const
{
    return "A logic-based solver that removes candidates by same-house-elimination and single-available-cell-solution";
}

bool SinglesSolver::IterateOnce()
{
    double old_uncertainty = mpSudoku->GetUncertainty();

    for(int i=1; i<10; i++)
    {
        NakedSingleInRow(i);
        NakedSingleInCol(i);
        NakedSingleInBox(i);
    }

    for(int i=1; i<10; i++)
    {
        HiddenSingleInRow(i);
        HiddenSingleInCol(i);
        HiddenSingleInBox(i);
    }

    double uncertainty = mpSudoku->GetUncertainty();
    return uncertainty == 0;
    if(uncertainty == old_uncertainty) throw CannotProgressError(mIters);
}


void SinglesSolver::NakedSingleInRow(const int row)
{
    if(!ValueWithin(row,1,9)) throw py::index_error("Tried to access invalid row");
    if(mKnownRows[row-1]) return;

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
    //mKnownRows[row-1] = (known_values.size() == 9);
}

void SinglesSolver::NakedSingleInCol(const int col)
{
    if(!ValueWithin(col,1,9)) throw py::index_error("Tried to access invalid column");
    if(mKnownCols[col-1]) return;

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
    //mKnownCols[col-1] = (known_values.size() == 9);
}

void SinglesSolver::NakedSingleInBox(int box)
{
    if(!ValueWithin(box,1,9)) throw py::index_error("Tried to access invalid box");
    if(mKnownBoxes[box-1]) return;

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
    //mKnownBoxes[box-1] = (known_values.size() == 9);
}

void SinglesSolver::HiddenSingleInRow(int row)
{
    if(!ValueWithin(row,1,9)) throw py::index_error("Tried to access invalid row");
    if(mKnownRows[row-1]) return;

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


void SinglesSolver::HiddenSingleInCol(int col)
{
    if(!ValueWithin(col,1,9)) throw py::index_error("Tried to access invalid row");
    if(mKnownCols[col-1]) return;

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


void SinglesSolver::HiddenSingleInBox(int box)
{
    if(!ValueWithin(box,1,9)) throw py::index_error("Tried to access invalid row");
    if(mKnownBoxes[box-1]) return;

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
