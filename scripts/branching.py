import sudoku as sdk

# Example program
# This example program solve the same sudoku with the branching solver
# The branching solver has no solving capabilities, it is only a platform
# to manage the branches, so we have to chose what solver it will use.
# We chose the SinglesSolver.

filename = '../sudokus/3'

# Configuration for branching
maximum_iterations = 20
debug_level = 2

# Configuration for base solver
base_solver_config = sdk.SolverConfig("SinglesSolver",1000,0)

# Solving
sudoku = sdk.Sudoku()
sudoku.Load(filename)
print('       GIVENS')
print(sudoku)

solver = sdk.BranchingSolver(sudoku,maximum_iterations,debug_level, base_solver_config)
solver.Execute()

print('\n      SOLUTION')
print(solver.GetSudoku())