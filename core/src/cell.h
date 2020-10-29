#ifndef CELL_H
#define CELL_H

#include <pybind11/pybind11.h>

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
    Cell();
    Cell(const int i, const int j);
    Cell(const Cell & rOther); // Copy constructor

    // Getters
    int GetValue();
    bool isSolved();
    Sudoku & GetOwner();
    Candidates GetCandidates();
    std::tuple<int, int> GetCoords();

    // Output
    std::string ToString();
    std::ostream & operator<<(std::ostream & Str);

    // Manipulators
    void GiveOwner(const int i, const int j, Sudoku & rOwner);
    void RemoveOwner();
    int PopCandidate(const int toRemove);
    void Solve(const int value);
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
