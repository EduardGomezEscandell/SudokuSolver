import sudoku as sdk

# Example program
# This example program does exactly the same as branching.py, but differently.
# In the other one, solver SinglesSolver is called. Here, instead, we call SinglesSolver's
# children directly. We can see how a recursive solver can have multiple children.

filename = '../sudokus/3'

# Configuration for branching
maximum_iterations = 100
debug_level = 2

# Configuration for base solver
base_solver_config = [sdk.SolverConfig("HiddenSinglesSolver",1000,0), sdk.SolverConfig("NakedSinglesSolver",1000,0)]

# Solving
sudoku = sdk.Sudoku()
sudoku.Load(filename)
print('       GIVENS')
print(sudoku)

solver = sdk.BranchingSolver(sudoku,maximum_iterations,debug_level, base_solver_config)
solver.Execute()

print('\n      SOLUTION')
print(solver.GetSudoku())