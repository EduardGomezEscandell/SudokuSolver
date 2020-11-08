# Python Sudoku Solver

This repository aims to create a library to solve sudokus with different algorithms. A few examples of use are found in the scripts directory. The library is written in C++ and called from Python, so as to take advantage of C++'s performance and Python's ease of use.

The goal of this repository is not to create the fastest algorithm but rather to be a playground for different concepts that interest me, so far this has been:
- Creating a Python interface to a C++ program
- Object oriented programming
- Usage of smart pointers
- Writing a CMake file

# How ...

### How to install ###
First, clone the repository. Go to the repository and in the console type `sh build.sh`. A compilation script is only provided for Linux. A new directory `build` will appear with, amongst other files, a `.so` file inside it. This is the library. A link will also be created in the `scripts` directory so you can test them. In order to be able to use it anywhere, you can add the build directory to your python path, or create a link to the library in you working directory.

### How to use ###
In order to get started, the best is to go to the `scripts` directory and check out the scripts inside it. In order to see all the classes and functions, you can go to `source/python_bindings.cpp` and see them.

### How does it work? ###
- Hidden Singles Solver: It works by looping through all houses (a house is either a row, a column or a box). In each house, it checks which spots each number can take (by reading the candidates). If any number can only be in one cell, then that cell can be solved with this number. This solver on its own can solve virtually no sudokus.

- Naked Singles Solver: It works by looping through all cells. If a cell is known, then its value is removed from the candidates of all cells in the same row, column and box. If a cell has only a candidate, then it is solved. This solver can solve some sudokus, but not many.

- Singles solver: It is the simplest recursive solver. It has the previous two as child solvers, so in each iteration of the parent solver, a single iteration of each of the previous two is performed. This solver can solve easy sudokus.

- Branching solver: Also a recursive solver. When all its children complete a full step without progress, the parent solver pushes a snapshot of the grid onto a stack and finds the cell with fewest candidates. This cell is resolved with its first candidate, then the solving continues. If this leads to any logical impossibility, the stack is popped and snapshot recovered, with the previous attempted candidate removed from the list. The branching solver cannot solve sudokus by itself, it is simply a platform to manage the stack, so it needs to use a base logic solver (such as any combination of the previous three).

### How can I create new solvers? ###
The best way is to create a class derived form the `Solver` class for a simple solver, or from `RecursiveSolver` if you want to have your solver use others. A method `IterateOnce` will have to be overridden, this is where the logic takes place. Method `GetDescription` should return a one-line description of your solver. 

Then you'll have to go to `source/python_bindings.cpp` and add it. Then, go to 
`source/recursivesolver.cpp` and add your solver to the list in the `ChooseSolver` function, if you want recursive solvers to be able to use yours. To compile, add your solver file to the list in `source/CMakeLists.txt`. Finally, you can create some tests in `tests/tests.py`.

## Potential improvements

If in the future I decide to add more functionality, some features I might consider are:
- Replacing all remaining raw pointers with smart pointers
- Parallelism
- Adding more complex logic algorithms

