#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "cell.h"
#include "sudoku.h"

namespace py = pybind11;

PYBIND11_MODULE(sudoku_core,m){
    py::class_<Cell>(m,"Cell")
            .def(py::init<const int, const int>())
            .def(py::init<Cell&>())
            .def("__str__",&Cell::ToString)
            .def("copy",[](const Cell & self){return Cell(self);})
            .def("IsSolved",&Cell::isSolved)
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
}
