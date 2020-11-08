import sudoku as sdk

# Example program
# This exampe shows how to manipulate the data

sudoku = sdk.Sudoku()
print("Created blank sudoku")

cell = sudoku[5,5] # Accessing cell at r5c5
cell.Solve(4)
print("Changed cell %s to a %d"%(cell.GetFormatedCoords(), cell.GetValue()))
print("\nStatus of the sudoku:")
print(sudoku)

new_cell = sudoku[1,1].copy() # Copies can be made
print("Let's make a copy of cell", new_cell.GetCoords())

if new_cell.IsSolved():
	print("This cell is solved, with a value of %s"%new_cell) # Solved cells print their values
else:
	print("This cell is not solved, it can still be any of: ",new_cell.GetCandidates())
	print("Let's disallow candidates one to three")
	new_cell.PopCandidates({1,2,3})
	print("Now it can still be any of: ",new_cell.GetCandidates())
	
	print("Let's say it is a 4 now")
	new_cell.PopCandidates({5,6,7,8,9}) # Cells resolve automatically when only one candidate is left
	print("See: ", new_cell)
	
	print("As you can see, modifying the copy did not modify the original:")
	print("\nStatus of the sudoku:")
	print(sudoku)

print("You can also manipulate sudokus")
sudoku2 = sudoku.copy()
for i in range(1,10):
	sudoku2[i,i].Solve(i)
print("See, they are different:")

print("\nStatus of the original sudoku:")
print(sudoku)

print("\nStatus of the copied sudoku:")
print(sudoku2)