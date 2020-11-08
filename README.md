# Python Sudoku Solver

This program solves Sudokus following logic first, and when out of options, branching (a.k.a. brute force). A few examples of use are found in the scripts directory. The heavy lifting is written in C++ and it can be accessed via Python.

# How ...

### How to install ###
First, clone the repository. Go to the repository and in the console type `sh build.sh`. A compilation script is only provided for Linux. A new directory `build` will appear with, amongst other files, a `.so` file inside it. This is the library. A link will also be created in the `scripts` directory so you can test them. In order to be able to use it anywhere, you can add the build directory to your python path, or create a link to the library in you working directory.

#### How to use ####
In order to get started, the best is to go to the `scripts` directory and check out the scripts inside it. In order to see all the classes and functions, you can go to `source/python_bindings.cpp` and see them.

### How does it work? ###
- Singles solver: It works by looping around and doing the same two tasks: finding hidden and naked singles in each house. I am following the nomenclature as explained in http://hodoku.sourceforge.net/en/techniques.php.

- Branching solver: When it completes a full step without progress, it pushes a snapshot onto a stack and fills the cell with fewest candidates. Then it goes back to the logic algortihm. If this leads to any logical impossibility, the stack is popped and snapshot recovered, with the previous attempted candidate removed from the list. The branching solver cannot solve sudokus by itself, it is simply a platform to manage the stack, so it needs to use a base logic solver (such as the singles solver).

### How can I create new solvers? ###
The best way is to create a class derived form the `Solver` class for a simple solver, or from `RecursiveSolver` if you want to have your solver use others. A method `IterateOnce` will have to be overridden, this is where the logic takes place. Method `GetDescription` should return a one-line description of your solver. 

Then you'll have to go to `source/python_bindings.cpp` and add it. Then, go to 
`source/recursivesolver.cpp` and add your solver to the list in the `ChooseSolver` function, if you want recursive solvers to be able to use yours. Finally, you can create some tests in `tests/tests.py`.

## Goals

The goal of this repository is not to create the fastest algorithm but rather to be a playground for different concepts that interest me, so far this has been:
- Creating a Python interface to a C++ program
- Object Oriented programming
- Usage of smart pointers
- Writing a CMake file

## Future work

In the future I wish to add more functionality. Some ideas are:
- Writting some documentation
- Replacing all remaining raw pointers with smart pointers
- Parallelism
- Adding more complex logic algorithms

