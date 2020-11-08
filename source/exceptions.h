#ifndef SUDOKU_EXCEPTIONS_H
#define SUDOKU_EXCEPTIONS_H

#include <exception>
#include <string>
#include <sstream>

#include "cell.h"

namespace SudokuSolve {

/*
 *          GLOBAL ERRORS
 */

class SolveError : public std::exception
{
public:
    SolveError(){};
    SolveError(std::string msg) : mMessage(msg) {};
    const char * what () const throw () {return &(mMessage[0]);}
protected:
    std::string mMessage = "There was an error during solving";
};


class ReachedMaxIterError : public SolveError
{
public:
    ReachedMaxIterError() : SolveError("Ran out of iterations") {};
};

class CannotProgressError : public SolveError
{
public:
    CannotProgressError(int iter) : SolveError() {
        std::stringstream ss;
        ss << "Failed to progress after iteration " << iter;
        mMessage = ss.str();
    }
};

/*
 *          CELL LEVEL ERRORS
 */

class CellLevelError : public std::exception
{
public:
    CellLevelError(const Cell & cell) : mCell(cell) {write_message();}
    const char * what () const throw () {return &(mMessage[0]);}
    const Cell mCell;
protected:
    virtual void write_message()
    {
        std::stringstream ss;
        ss << "There was an error in cell " << mCell.GetFormatedCoords();
        mMessage = ss.str();
    }
    std::string mMessage;
};

class NoCandidatesError : public CellLevelError
{
public:
    NoCandidatesError(const Cell & cell): CellLevelError(cell) {write_message();}
protected:
    void write_message() override
    {
        std::stringstream ss;
        ss << "Cell " << mCell.GetFormatedCoords() << " ran out of candidates";
        mMessage = ss.str();
    }
};

class DuplicateEntryError : public CellLevelError
{
public:
    DuplicateEntryError(const Cell & cell): CellLevelError(cell) {write_message();}
protected:
    void write_message() override
    {
        std::stringstream ss;
        ss << "Cell " << mCell.GetFormatedCoords() << " has an entry that exists elsewhere in its house";
        mMessage = ss.str();
    }
};

class VerificationError : public CellLevelError
{
public:
    VerificationError(Cell & cell): CellLevelError(cell) {write_message();}
protected:
    void write_message() override
    {
        std::stringstream ss;
        ss << "Cell " << mCell.GetFormatedCoords() << " does not match the provided solution";
        mMessage = ss.str();
    }
};

} //namespace SudokuSolve
#endif // SUDOKU_EXCEPTIONS_H
