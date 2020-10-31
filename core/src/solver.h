#ifndef SOLVER_H
#define SOLVER_H

#include "sudoku.h"

#include <sstream>

#define PRINT(debuglvl,msg) if(debuglvl<mDebugLvl) std::cout<<msg
namespace py = pybind11;

namespace SudokuSolve{

enum class Debug{none, results, info, full};

struct SolverConfig
{
    std::string name = "Solver";
    int max_iter = 400;
    int debug_lvl = 0;
    std::vector<SolverConfig> children;
};


class Solver
{
public:
    Solver(Sudoku & rSudoku, const int max_iter, const int debug_lvl);
    Solver(Sudoku & rSudoku, const SolverConfig config) : Solver(rSudoku, config.max_iter, config.debug_lvl) {};
    void Execute();

    // For subclasses
    virtual ~Solver(){}
    virtual void SwitchSudoku(Sudoku & rSudoku);

    // For pyhton interface
    std::string ToString();
    Sudoku & GetSudoku();
    int GetIter();

protected:
    int mMaxIter = 400;
    Debug mDebugLvl = Debug::full;

    int mIters;
    Sudoku * mpSudoku;
    std::vector<Solver *> mChildSolvers;

    void Finalize();

    // For subclasses
    virtual std::string GetDescription() const;
    virtual bool IterateOnce() = 0;

private:
};


} //namespace SudokuSolve
#endif // SOLVER_H
