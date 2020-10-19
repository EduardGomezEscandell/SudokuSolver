from sudoku import Sudoku

s = Sudoku('data/2')
print('       GIVENS')
print(s)
s.AssertCorrect()

for i in range(15):
    if s.IsSolved():
        break
    
    for i in range(1,10):
        s.NakedSingleInRow(i)
        s.NakedSingleInCol(i)
        s.NakedSingleInBox(i)
        
        s.HiddenSingleInRow(i)
        s.HiddenSingleInCol(i)
        s.HiddenSingleInBox(i)
print('       SOLUTION')
print(s)
s.AssertCorrect()