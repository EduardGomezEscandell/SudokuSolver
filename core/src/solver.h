#ifndef SOLVER_H
#define SOLVER_H

#include "sudoku.h"

#include <sstream>

#define PRINT(debuglvl,msg) if(debuglvl<mDebugLvl) std::cout<<msg
namespace py = pybind11;

namespace SudokuSolve{

enum class Debug{none, results, info, full};


class Solver
{
public:
    Solver(Sudoku & rSudoku, const int max_iter, const int debug_lvl);
    void Execute();
    std::string ToString();
    Sudoku & GetSudoku();
    int GetIter();
protected:
    int mMaxIter = 400;
    Debug mDebugLvl = Debug::full;

    int mIters;
    Sudoku * mpSudoku;
    std::vector<Solver> mChildSolvers;

    void SwitchSudoku(Sudoku & rSudoku);

    virtual std::string GetDescription() const;
    virtual bool IterateOnce();
    void Finalize();

private:
};


} //namespace SudokuSolve
#endif // SOLVER_H
