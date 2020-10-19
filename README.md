# Python Sudoku Logic Solver

This program solves Sudokus following logic instead of trial and error. Not all sudokus can be solved in this manner but this can help reduce the number of blanks before using a brute-force algorithm.

It works by looping around and doing the same two tasks: finding hidden and naked singles in each house. I am following the nomenclature as explained in http://hodoku.sourceforge.net/en/techniques.php.

## Goals

The goal of this repository is not to create the fastest algorithm but rather to be a playground for different concepts that interest me.


## Future work

In the future I wish to add more functionality. Some ideas are:
- Adding more complex logic algorithms
- Adding a brute-force algorithm
- Translating the code to C++ while leaving a Python API
- Parallelism
