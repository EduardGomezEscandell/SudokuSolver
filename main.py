import sudoku_core as sdk

# Example program
# This example program solve the same sudoku with two diffferent solvers
#

filename = 'sudokus/3'

s = sdk.Sudoku()
s.Load(filename)
print('       GIVENS')
print(s)


# Trying to solve it with a logical algorithm
print('Trying the logic algorithm\n')
solver = sdk.SinglesSolver(s,1000,2)
try:
    solver.Execute()
    print(solver.GetSudoku())
except Exception as e:
    print('')
    print(e)
    
# # Trying to solve with a branching algorithm
print('Trying the branching algorithm\n')
s = s.copy()
print('-'*80)
config = sdk.SolverConfig("SinglesSolver",1000,0)
solver = sdk.BranchingSolver(s,20,2,config)
try:
    solver.Execute()
    print(solver.GetSudoku())
except Exception as e:
    print('')
    print(e)