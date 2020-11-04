# Python Sudoku Solver

This program solves Sudokus following logic first, and when out of options, branching (a.k.a. brute force). An example of use is found in 'main.py'. The heavy lifting is written in C++ and it can be accessed via Python.

#### Singles solver ####
It works by looping around and doing the same two tasks: finding hidden and naked singles in each house. I am following the nomenclature as explained in http://hodoku.sourceforge.net/en/techniques.php.

#### Branching solver ####
When it completes a full step without progress, it pushes a snapshot onto a stack and fills the cell with fewest candidates. Then it goes back to the logic algortihm. If this leads to any locical impossibility, the stack is popped and snapshot recovered, with the previous attempted candidate removed from the list.

## Goals

The goal of this repository is not to create the fastest algorithm but rather to be a playground for different concepts that interest me.


## Future work

In the future I wish to add more functionality. Some ideas are:
- Writting some documentation
- Replacing all remaining raw pointers with smart pointers
- Parallel exploration of branches.
- Adding more complex logic algorithms

