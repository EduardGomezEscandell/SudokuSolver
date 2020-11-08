#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "cell.h"
#include "sudoku.h"

#include "SolverConfig.h"
#include "solver.h"
#include "recursivesolver.h"

#include "singlessolver.h"
#include "branchingsolver.h"

#include "exceptions.h"

namespace py = pybind11;
namespace SudokuSolve{

PYBIND11_MODULE(sudoku,m){
    py::class_<Cell>(m,"Cell")
            .def(py::init<const int, const int>())
            .def(py::init<Cell&>())
            .def("__str__",&Cell::ToString)
            .def("copy",[](const Cell & self){return Cell(self);})
            .def("IsSolved",&Cell::IsSolved)
            .def("GetValue",&Cell::GetValue)
            .def("GetCoords",&Cell::GetCoords)
            .def("GetFormatedCoords",&Cell::GetFormatedCoords)
            .def("GetCandidates",&Cell::GetCandidates)
            .def("PopCandidate",&Cell::PopCandidate)
            .def("PopCandidates",&Cell::PopCandidates)
            .def("Solve",&Cell::Solve)
            ;

    py::class_<Sudoku>(m,"Sudoku")
            .def(py::init<>())
            .def("__str__",&Sudoku::ToString)
            .def("__getitem__",&Sudoku::operator[], py::return_value_policy::reference)
            .def("AccessByBox",&Sudoku::AccessByBox)
            .def("copy",[](const Sudoku & self){return Sudoku(self);})
            .def("Load",&Sudoku::Load)
            .def("GetUncertainty",&Sudoku::GetUncertainty)
            ;


    py::class_<SolverConfig>(m,"SolverConfig")
            .def(py::init<int, int>())
            .def(py::init<std::string &,int, int>())
            .def(py::init<int, int, std::vector<SolverConfig>>())
            .def(py::init<std::string &, int, int, std::vector<SolverConfig>>())
            .def(py::init<int, int, SolverConfig>())
            .def(py::init<std::string, int, int, SolverConfig>())
            ;

    // Base solvers

    py::class_<Solver>(m, "Solver")
            .def("__str__",  &Solver::ToString)
            .def("Execute",  &Solver::Execute)
            .def("GetSudoku",&Solver::GetSudoku)
            .def("GetIter",  &Solver::GetIter)
            ;

    py::class_<RecursiveSolver, Solver>(m,"RecursiveSolver")
            ;

    // Functional solvers

    py::class_<SinglesSolver,Solver>(m, "SinglesSolver")
            .def(py::init<Sudoku&, SolverConfig>())
            .def(py::init<Sudoku&, const int, const int>())
            .def("IterateOnce", &SinglesSolver::IterateOnce)
            ;

    py::class_<BranchingSolver, RecursiveSolver, Solver>(m,"BranchingSolver")
            .def(py::init<Sudoku&, SolverConfig>())
            .def(py::init<Sudoku&, int, int, SolverConfig>())
            .def(py::init<Sudoku&, int, int, std::vector<SolverConfig>>())
            ;

}
} //namespace SudokuSolve
