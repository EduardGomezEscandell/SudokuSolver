#include "cell.h"

Cell::Cell(const int i, const int j)
{
    mRow = i;
    mCol = j;
    mSolved = false;
    mValue = 0;
    mCandidates = {1,2,3,4,5,6,7,8,9};
}

Cell::Cell(Cell & rOther)
{
    mRow = rOther.mRow;
    mCol = rOther.mCol;
    mSolved = rOther.mSolved;
    mCandidates = rOther.mCandidates;
}

std::tuple<int, int> Cell::GetCoords()
{
    return std::tie(mRow, mCol);
}

int Cell::PopCandidate(const int toRemove)
{
    std::size_t len = mCandidates.size();
    mCandidates.remove(toRemove);
    return len==mCandidates.size() ? 0 : toRemove;
    // TODO: Throw NoCandidatesError exception
}

Candidates Cell::GetCandidates()
{
    Candidates ret = mCandidates;
    return ret;
}

void Cell::Solve(const int value)
{
    mSolved = true;
    mValue = value;
    mCandidates.clear();
    mCandidates = {value};
}

int Cell::GetValue()
{
    if(mSolved){
        return mValue;
    } else {
        throw "This cell is not solved";
    }
}

std::ostream & Cell::operator<<(std::ostream & Str) {
  if(mSolved){
    Str<<mValue;
  } else {
    Str<<"·";
  }
    // print something from v to str, e.g: Str << v.getX();
  return Str;
}

std::string Cell::ToString()
{
    return mSolved ? std::to_string(mValue) : "·";
}
