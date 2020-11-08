#!/usr/bin/python
import unittest
import sudoku as sdk
from support import GetPath, LoadSolution, LoadSudoku

class TestSudoku(unittest.TestCase):
    def test_cell(self):
        value = 3
        c = sdk.Cell(2,2)
        c.Solve(value)
        v = c.GetValue()
        self.assertEqual(value,v)

    def test_cell_copy(self):
        value1 = 3
        value2 = 5
        c1 = sdk.Cell(2,2)
        c2 = c1.copy()
        c1.Solve(value1)
        c2.Solve(value2)
        self.assertEqual(c1.GetValue(), value1)
        self.assertEqual(c2.GetValue(), value2)

    def test_sudoku_load(self):
        s0 = sdk.Sudoku()
        filename = GetPath('../sudokus/1')
        correct = LoadSudoku(filename)
        # Loading
        s0.Load(filename)
        # Testing copying
        s=s0.copy()

        for r in range(1,10):
            for c in range(1,10):
                cell = s[r,c]
                try:
                    if cell.IsSolved():
                        self.assertEqual(correct[r-1][c-1], cell.GetValue())
                    else:
                        self.assertEqual(correct[r-1][c-1], 0)
                except:
                    raise AssertionError("Failure at r%dc%d"%cell.GetCoords())

    def test_Solver_init(self):
        s = sdk.Sudoku()
        dlvl = 0
        miter = 20
        filename = GetPath('../sudokus/1')
        s.Load(filename)
        solver = sdk.SinglesSolver(s, miter, dlvl)
        msg = str(solver)
        self.assertIn(str(miter),msg)
        self.assertIn(str(dlvl),msg)

    def test_HiddenSinglesSolver(self):
        s = sdk.Sudoku()
        dlvl = 0
        miter = 3
        filename = GetPath('../sudokus/1')
        s.Load(filename)
        print(s)
        solver = sdk.HiddenSinglesSolver(s, miter, dlvl)
        solver.IterateOnce()
        s = solver.GetSudoku()
        self.assertEqual(s[5,5].GetValue(), 8)


    def test_NakedSinglesSolver(self):
        s = sdk.Sudoku()
        dlvl = 0
        miter = 3
        filename = GetPath('../sudokus/1')
        s.Load(filename)
        solver = sdk.NakedSinglesSolver(s, miter, dlvl)
        solver.Execute()
        s = solver.GetSudoku()
        self.assertEqual(str(s), '7 2 3  · 4 ·  1 5 9  \n6 1 ·  3 9 2  4 7 8  \n8 · ·  · 1 5  6 3 2  \n\n3 7 ·  6 5 4  9 2 1  \n1 9 4  2 8 7  3 6 5  \n2 5 6  9 3 1  8 4 7  \n\n5 6 1  4 7 9  2 8 3  \n4 8 7  1 2 3  5 9 6  \n9 3 2  5 6 8  7 1 4  \n')

    def test_SinglesSolver(self):
        s = sdk.Sudoku()
        dlvl = 0
        miter = 3
        filename = GetPath('../sudokus/1')
        correct = LoadSolution(filename)
        s.Load(filename)
        solver = sdk.SinglesSolver(s, miter, dlvl)
        solver.Execute()
        s = solver.GetSudoku()
        for r in range(1,10):
            for c in range(1,10):
                self.assertEqual(correct[r-1][c-1], s[r,c].GetValue())

    def test_BranchingSolver(self):
        filename = GetPath('../sudokus/3')
        dlvl = 0
        miter = 12
        config = sdk.SolverConfig("SinglesSolver",10,0)

        s = sdk.Sudoku()
        s.Load(filename)
        correct = LoadSolution(filename)

        solver = sdk.BranchingSolver(s, miter, dlvl, config)
        solver.Execute()

        s = solver.GetSudoku()
        for r in range(1,10):
            for c in range(1,10):
                self.assertEqual(correct[r-1][c-1], s[r,c].GetValue())

# Execution

if __name__ == '__main__':
    unittest.main()