cmake_minimum_required(VERSION 3.5)

project(sudoku_core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(pybind11)

pybind11_add_module(sudoku_core SHARED
                    python_bindings.cpp
                    solver.cpp
                    cell.cpp
                    sudoku.cpp
                    singlessolver.cpp
                    )
