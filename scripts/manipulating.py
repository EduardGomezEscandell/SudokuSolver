import sudoku as sdk

# Example program
# This exampe shows how to manipulate the data

filename = '../sudokus/1'
sudoku = sdk.Sudoku()
print("Created blank sudoku")

cell = sudoku[5,5] # Accessing cell at r5c5
cell.Solve(5)
print("Changed cell %s to a %d"%(cell.GetFormatedCoords(), cell.GetValue()))
print(sudoku)

new_cell = sudoku[1,1].copy() # Copies can be made

if new_cell.IsSolved():
	print("This cell is solved, with a value of %s"%cell) # Solved cells print their values
else:
	print("This cell is not solved, it can still be any of: ",cell.GetCandidates())
	new_cell.PopCandidate(5)
	print("Now it can still be any of: ",cell.GetCandidates())
