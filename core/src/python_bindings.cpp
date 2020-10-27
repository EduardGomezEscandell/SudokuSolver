#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "cell.h"
#include "sudoku.h"

namespace py = pybind11;

PYBIND11_MODULE(sudoku_core,m){
    py::class_<Cell>(m,"Cell")
            .def(py::init<const int, const int>())
            .def(py::init<Cell&>())
            .def("GetValue",&Cell::GetValue)
            .def("GetCoords",&Cell::GetCoords)
            .def("GetCandidates",&Cell::GetCandidates)
            .def("PopCandidate",&Cell::PopCandidate)
            .def("Solve",&Cell::Solve)
            .def("__str__",&Cell::ToString)
            ;

            ;
}
