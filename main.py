import solvers
from sudoku import Sudoku

s = Sudoku()
s.load('data/3')
print('       GIVENS')
print(s)
s.AssertCorrect()


solver = solvers.BranchingSolver(s,1000,1)
solver.Execute()