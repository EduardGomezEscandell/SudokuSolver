import solvers
from sudoku import Sudoku

# Example program
# This example program solve the same sudoku with two diffferent solvers
#

filename = 'data/3'

s = Sudoku()
s.load(filename)
print('       GIVENS')
print(s)
s.AssertCorrect()

# Trying to solve it with a logical algorithm
print('Trying the logic algorithm\n')
solver = solvers.SinglesSolver(s,maxiter=1000,debug_lvl=2)
try:
    solver.Execute()
    solver.Verify()
except Exception as e:
    print('')
    print(e)
    
# # Trying to solve with a branching algorithm
s = Sudoku()
s.load(filename)
print('-'*80)
print('Trying the branching algorithm\n')
solver = solvers.BranchingSolver(s,maxiter=1000,debug_lvl=2,Info={'SinglesSolver':{'maxiter':1000,'debug_lvl':0}})
try:
    solver.Execute()
    solver.Verify()
except Exception as e:
    print('')
    print(e)