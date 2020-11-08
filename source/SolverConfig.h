#ifndef SOLVERCONFIG_H
#define SOLVERCONFIG_H

#include <vector>
#include "string"

namespace SudokuSolve {

/* Initializer:
 * SolverConfig(
 *    1. - Name [OPTIONAL]
 *    2. - max_iter: maximum number of iterations
 *    3. - debug_lvl: frequency of printing
 *
 *                 child: single child solver Config
 *    4.- EITHER <
 *                 children: vector of children Configs
*/


struct SolverConfig
{
    // Basic initializer
    SolverConfig(int maxiter, int debuglvl) :
        max_iter(maxiter),
        debug_lvl(debuglvl)
        {};

    SolverConfig(std::string rName, int maxiter, int debuglvl) :
        SolverConfig(maxiter, debuglvl)
        {name = rName;};

    // Initializer with children
    SolverConfig(int maxiter, int debuglvl, std::vector<SolverConfig> children_config) :
        children(children_config)
        {SolverConfig(maxiter, debuglvl);};

    SolverConfig(std::string rName, int maxiter, int debuglvl, std::vector<SolverConfig> children_config) :
        SolverConfig(maxiter, debuglvl, children_config)
        {name = rName;};

    // Initializer with single child
    SolverConfig(int maxiter, int debuglvl, SolverConfig child_config)
    {
        std::vector<SolverConfig> arg3;
        arg3.push_back(child_config);
        SolverConfig(maxiter, debuglvl, arg3);
    };

    SolverConfig(std::string rName, int maxiter, int debuglvl, SolverConfig child_config):
        SolverConfig(maxiter, debuglvl, child_config)
        {name = rName;};

    // Parameters
    std::string name = "";
    int max_iter = 400;
    int debug_lvl = 0;
    std::vector<SolverConfig> children;
};


} // namespace SudokuSolve
#endif // SOLVERCONFIG_H
