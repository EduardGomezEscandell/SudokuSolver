import sudoku as sdk

# Example program
# This example program solve the same sudoku with the simplest solver
# This solver works on simple logic, so it cannot solve all sodokus,
# but it is simple and quick.

filename = '../sudokus/1'
maximum_iterations = 20
debug_level = 3 # This decides how much information to print out

sudoku = sdk.Sudoku()
sudoku.Load(filename)
print('       GIVENS')
print(sudoku)

solver = sdk.SinglesSolver(sudoku,maximum_iterations,debug_level)
solver.Execute()