#ifndef SUDOKU_H
#define SUDOKU_H

#include "cell.h"
#include <pybind11/pybind11.h>

#include <vector>
#include <memory>
#include <fstream>
#include <string>
#include <sstream>

namespace SudokuSolve{

class Sudoku
{
public:
    // Constructors
    Sudoku();
    Sudoku(const Sudoku & rRHS);

    // Output
    std::string ToString();

    // Checkers
    void assertNoDuplicates();

    // Getters/setters
    Cell& operator()(const int row, const int col);
    Cell& operator[](std::tuple<int,int>);
    double GetUncertainty();

    // Manipulators
    void Load(std::string filename);
protected:
    friend class Cell;
    const int mMmaximumCandidates = 9*9*8;
    Cell mGrid[9][9];
    Cell * mBoxes[9][9];
    int mAbsUncertainty = mMmaximumCandidates;
    void BuildBoxes();
};

} // namespace SudokuSolve
#endif // SUDOKU_H
