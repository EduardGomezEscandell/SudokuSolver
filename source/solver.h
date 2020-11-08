#ifndef SOLVER_H
#define SOLVER_H

#include "sudoku.h"
#include "SolverConfig.h"
#include <sstream>

#define PRINT(debuglvl,msg) if(debuglvl<=mDebugLvl) py::print(msg)
namespace py = pybind11;

namespace SudokuSolve{

enum class Debug{none, results, info, full};

class Solver
{
public:
    Solver(Sudoku & rSudoku, const int max_iter, const int debug_lvl);
    Solver(std::shared_ptr<Sudoku> & pSudoku, const int max_iter, const int debug_lvl);

    Solver(Sudoku & rSudoku, const SolverConfig config)
        : Solver(rSudoku, config.max_iter, config.debug_lvl) {};
    Solver(std::shared_ptr<Sudoku> & pSudoku, const SolverConfig config)
        : Solver(pSudoku, config.max_iter, config.debug_lvl) {};

    void Execute();

    // For subclasses
    virtual ~Solver(){}
    virtual void SwitchSudoku(std::shared_ptr<Sudoku> & pSudoku);
    virtual bool IterateOnce() = 0;

    // For pyhton interface
    virtual std::string ToString() const;
    Sudoku & GetSudoku();
    int GetIter();

protected:
    int mMaxIter = 400;
    Debug mDebugLvl = Debug::full;

    int mIters;
    std::shared_ptr<Sudoku> mpSudoku;
    std::vector<Solver *> mChildSolvers;

    void Finalize();

    // For subclasses
    virtual std::string GetDescription() const;
};


} //namespace SudokuSolve
#endif // SOLVER_H
