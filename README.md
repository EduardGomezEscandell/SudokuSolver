Python Sudoku Logic Solver

This program solves Sudokus following logic instead of trial and error. Not all sudokus can be solved in this manner but this can help reduce the number of blanks before using a guessing algorithm.

It works by looping around and doing the same two functions: finding hidden and naked singles in each row, column and block. See http://hodoku.sourceforge.net/en/tech_singles.php for nomenclature.

In the future I wish to add more functionality. Some ideas are:
- Adding more complex logic algorithms
- Adding a guessing algorithm
- Translating the code to C++ while leaving a Python API
- Parallelism