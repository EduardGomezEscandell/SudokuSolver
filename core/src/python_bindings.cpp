#include<pybind11/pybind11.h>
#include "cell.h"
#include "sudoku.h"

namespace py = pybind11;

PYBIND11_MODULE(sudoku_core,m){
    py::class_<Cell>(m,"Cell")
            .def(py::init<const int, const int>())
            .def("GetCoords",&Cell::GetCoords)
            ;
}
