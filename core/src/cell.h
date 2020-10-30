#ifndef CELL_H
#define CELL_H

#include <pybind11/pybind11.h>
#include "common.h"

#include <iostream>
#include <string>
#include <tuple>
#include <list>

typedef std::list<int> Candidates;

namespace SudokuSolve{

class Sudoku;

class Cell
{
public:
    // Constructors
    Cell(const int i, const int j);
    Cell(const Cell & rOther); // Copy constructor

    // Getters
    int GetValue() const;
    bool IsSolved() const;
    Sudoku & GetOwner();
    Candidates GetCandidates() const;
    std::tuple<int, int> GetCoords() const;

    // Output
    std::string ToString() const;

    // Manipulators
    void GiveOwner(const int i, const int j, Sudoku & rOwner);
    void RemoveOwner();
    void Solve(const int value);
    bool PopCandidate(const int toRemove);

    template<typename Container>
    int PopCandidates(const Container & rContainer);

protected:
    int mRow;
    int mCol;
    int mValue;
    bool mSolved;
    Candidates mCandidates;
    Sudoku * mpOwner = nullptr;
};
std::ostream & operator<<(std::ostream & Str,  const Cell & cell);

} // namespace SudokuSolve

#endif // CELL_H
