#include "cell.h"
#include "sudoku.h"

namespace py = pybind11;

namespace SudokuSolve {

Cell::Cell(const int i, const int j)
{
    mRow = i;
    mCol = j;
    mSolved = false;
    mValue = 0;
    mCandidates = {1,2,3,4,5,6,7,8,9};
}

Cell::Cell(const Cell & rOther)
{
    mRow = rOther.mRow;
    mCol = rOther.mCol;
    mSolved = rOther.mSolved;
    mCandidates = rOther.mCandidates;
}

void Cell::GiveOwner(const int i, const int j, Sudoku &rOwner)
{
    mRow = i;
    mCol = j;
    mpOwner = &rOwner;
}

Sudoku & Cell::GetOwner()
{
    return *mpOwner;
}

void Cell::RemoveOwner()
{
    mpOwner = nullptr;
    mRow = mCol = 0;
}

std::tuple<int, int> Cell::GetCoords()  const
{
    return std::tie(mRow, mCol);
}

template<typename Container>
inline int Cell::PopCandidates(const Container & rContainer)
{
    for(int value : rContainer) mCandidates.remove(value);
    // TODO: Throw NoCandidatesError exception
}


bool Cell::PopCandidate(const int toRemove)
{
    std::size_t len = mCandidates.size();
    mCandidates.remove(toRemove);
    return len!=mCandidates.size();
    // TODO: Throw NoCandidatesError exception
}

Candidates Cell::GetCandidates() const
{
    Candidates ret = mCandidates;
    return ret;
}

void Cell::Solve(const int value)
{
    if(!ValueWithin(value,1,9)) py::value_error("A Sudoku entry must be between 1 and 9");
    mSolved = true;
    mValue = value;
    mCandidates.clear();
    mCandidates = {value};
    if(mpOwner != nullptr)
    {
        mpOwner->mAbsUncertainty--;
    }
}

int Cell::GetValue() const
{
    if(mSolved){
        return mValue;
    } else {
        throw "This cell is not solved";
    }
}

std::ostream & operator<<(std::ostream & Str, const Cell & cell)
{
  if(cell.IsSolved()){
    Str<<cell.GetValue();
  } else {
    Str<<"·";
  }
  return Str;
}

std::string Cell::ToString() const
{
    return mSolved ? std::to_string(mValue) : "·";
}

bool Cell::IsSolved() const
{
    return mSolved;
}

}
