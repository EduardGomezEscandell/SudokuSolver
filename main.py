import solvers
from sudoku import Sudoku

s = Sudoku()
s.load('data/2')
print('       GIVENS')
print(s)
s.AssertCorrect()


solver = solvers.BranchingSolver(s,1000,2)
solver.Execute()