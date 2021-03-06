#ifndef CELL_H
#define CELL_H

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
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
    std::tuple<int, int> GetCoords();

    // Output
    std::string ToString() const;
    std::string GetFormatedCoords() const;

    // Manipulators
    void GiveOwner(const int i, const int j, Sudoku & rOwner);
    void RemoveOwner();
    void Solve(const int value);
    void PopCandidate(const int toRemove);
    void PopCandidates(std::set<int> & rContainer);

protected:
    int mRow;
    int mCol;
    int mValue;
    bool mSolved;
    Candidates mCandidates;
    Sudoku * mpOwner = nullptr;
};

} // namespace SudokuSolve

#endif // CELL_H
