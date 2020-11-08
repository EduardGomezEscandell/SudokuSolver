#ifndef SUDOKU_H
#define SUDOKU_H

#include "cell.h"
#include "common.h"
#include <pybind11/pybind11.h>

#include <vector>
#include <memory>
#include <fstream>
#include <string>
#include <sstream>

namespace py = pybind11;

namespace SudokuSolve{

// Machine-generated code
#define BLANK_GRID  {                                                                                   \
        {Cell(1,1),Cell(1,2),Cell(1,3),Cell(1,4),Cell(1,5),Cell(1,6),Cell(1,7),Cell(1,8),Cell(1,9)},    \
        {Cell(2,1),Cell(2,2),Cell(2,3),Cell(2,4),Cell(2,5),Cell(2,6),Cell(2,7),Cell(2,8),Cell(2,9)},    \
        {Cell(3,1),Cell(3,2),Cell(3,3),Cell(3,4),Cell(3,5),Cell(3,6),Cell(3,7),Cell(3,8),Cell(3,9)},    \
        {Cell(4,1),Cell(4,2),Cell(4,3),Cell(4,4),Cell(4,5),Cell(4,6),Cell(4,7),Cell(4,8),Cell(4,9)},    \
        {Cell(5,1),Cell(5,2),Cell(5,3),Cell(5,4),Cell(5,5),Cell(5,6),Cell(5,7),Cell(5,8),Cell(5,9)},    \
        {Cell(6,1),Cell(6,2),Cell(6,3),Cell(6,4),Cell(6,5),Cell(6,6),Cell(6,7),Cell(6,8),Cell(6,9)},    \
        {Cell(7,1),Cell(7,2),Cell(7,3),Cell(7,4),Cell(7,5),Cell(7,6),Cell(7,7),Cell(7,8),Cell(7,9)},    \
        {Cell(8,1),Cell(8,2),Cell(8,3),Cell(8,4),Cell(8,5),Cell(8,6),Cell(8,7),Cell(8,8),Cell(8,9)},    \
        {Cell(9,1),Cell(9,2),Cell(9,3),Cell(9,4),Cell(9,5),Cell(9,6),Cell(9,7),Cell(9,8),Cell(9,9)}     \
}

class Sudoku
{
public:
    // Constructors
    Sudoku();
    Sudoku(const Sudoku & rRHS);

    // Output
    std::string ToString()  const;

    // Checkers
    void assertNoDuplicates() const;

    // Getters/setters
    Cell& operator()(const int row, const int col);
    Cell& operator[](std::tuple<int,int>);
    double GetUncertainty() const;
    Cell & AccessByBox(const int boxId, const int entry);
    Cell * CellWithFewestCandidates();

    // Manipulators
    void Load(std::string filename);

    // Helpers
    bool mKnownRows [9] = {false, false, false, false, false, false, false, false, false};
    bool mKnownCols [9] = {false, false, false, false, false, false, false, false, false};
    bool mKnownBoxes [9]= {false, false, false, false, false, false, false, false, false};

protected:
    friend class Cell;

    Cell mGrid[9][9] = BLANK_GRID;
    Cell * mBoxes[9][9];
    static const int mMmaximumCandidates = 9*9*8;
    int mAbsUncertainty = mMmaximumCandidates;

    void BuildBoxes();
};

} // namespace SudokuSolve
#endif // SUDOKU_H
