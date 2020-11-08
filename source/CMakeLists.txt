cmake_minimum_required(VERSION 3.5)

project(sudoku LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(pybind11)

pybind11_add_module(sudoku SHARED
                    python_bindings.cpp
                    cell.cpp
                    sudoku.cpp
                    solver.cpp
                    nakedsinglessolver.cpp
                    hiddensinglessolver.cpp
                    singlessolver.cpp
                    recursivesolver.cpp
                    branchingsolver.cpp
                    )

target_compile_options(sudoku PRIVATE -Wall -Wextra -pedantic)
