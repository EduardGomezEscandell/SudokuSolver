import solvers
import errors
from sudoku import Sudoku

s = Sudoku()
s.load('data/3')
print('       GIVENS')
print(s)
s.AssertCorrect()

print('Trying the logic algorithm')
solver = solvers.SinglesSolver(s,maxiter=1000,debug_lvl=1)
try:
    solver.Execute()
except errors.CannotProgressError as e:
    print(e)
    print('Trying the branching algorithm')
    solver = solvers.BranchingSolver(s,maxiter=1000,debug_lvl=1)
    solver.Execute()
solver.Verify()