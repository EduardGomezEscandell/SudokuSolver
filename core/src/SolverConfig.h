#ifndef SOLVERCONFIG_H
#define SOLVERCONFIG_H

#include <vector>
#include "string"

namespace SudokuSolve {

struct SolverConfig
{
    SolverConfig(int maxiter, int debuglvl) :
        max_iter(maxiter),
        debug_lvl(debuglvl)
        {};

    SolverConfig(int maxiter, int debuglvl, std::vector<SolverConfig> children_config) :
        children(children_config)
        {SolverConfig(maxiter, debuglvl);};

    SolverConfig(int maxiter, int debuglvl, SolverConfig child_config)
    {
        std::vector<SolverConfig> arg3;
        arg3.push_back(child_config);
        SolverConfig(maxiter, debuglvl, arg3);
    };

    std::string name = "Solver";
    int max_iter = 400;
    int debug_lvl = 0;
    std::vector<SolverConfig> children;
};


} // namespace SudokuSolve
#endif // SOLVERCONFIG_H
