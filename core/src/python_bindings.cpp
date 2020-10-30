#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "cell.h"
#include "sudoku.h"
#include "solver.h"
#include "singlessolver.h"

namespace py = pybind11;
namespace SudokuSolve{

PYBIND11_MODULE(sudoku_core,m){
    py::class_<Cell>(m,"Cell")
            .def(py::init<const int, const int>())
            .def(py::init<Cell&>())
            .def("__str__",&Cell::ToString)
            .def("copy",[](const Cell & self){return Cell(self);})
            .def("IsSolved",&Cell::IsSolved)
            .def("GetValue",&Cell::GetValue)
            .def("GetCoords",&Cell::GetCoords)
            .def("GetCandidates",&Cell::GetCandidates)
            .def("PopCandidate",&Cell::PopCandidate)
            .def("Solve",&Cell::Solve)
            ;

    py::class_<Sudoku>(m,"Sudoku")
            .def(py::init<>())
            .def("__str__",&Sudoku::ToString)
            .def("__getitem__",&Sudoku::operator[], py::return_value_policy::reference)
            .def("copy",[](const Sudoku & self){return Sudoku(self);})
            .def("Load",&Sudoku::Load)
            ;

    py::class_<Solver>(m, "Solver")
            .def(py::init<Sudoku&, const int, const int>())
            .def("__str__",&Solver::ToString)
            .def("Execute", &Solver::Execute)
            .def("GetSudoku",&Solver::GetSudoku)
            ;

    py::class_<SinglesSolver,Solver>(m, "SinglesSolver")
            .def(py::init<Sudoku&, const int, const int>())
            .def("IterateOnce", &SinglesSolver::IterateOnce)
            ;

}
} //namespace SudokuSolve
