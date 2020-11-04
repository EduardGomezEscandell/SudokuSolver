#!/usr/bin/python
import unittest
import sudoku_core as sdk
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
        filename = GetPath('data/1')
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
        dlvl = 4
        miter = 20
        filename = GetPath('data/1')
        s.Load(filename)
        solver = sdk.SinglesSolver(s, miter, dlvl)
        msg = str(solver)
        self.assertIn(str(miter),msg)
        self.assertIn(str(dlvl),msg)
        
    def test_SinglesSolver(self):
        s = sdk.Sudoku()
        dlvl = 1
        miter = 10
        filename = GetPath('data/1')
        correct = LoadSolution(filename)
        s.Load(filename)
        solver = sdk.SinglesSolver(s, miter, dlvl)
        solver.Execute()
        s = solver.GetSudoku()
        for r in range(1,10):
            for c in range(1,10):
                self.assertEqual(correct[r-1][c-1], s[r,c].GetValue())
    
    def test_BranchingSolver(self):
        s = sdk.Sudoku()
        dlvl = 1
        miter = 10
        filename = GetPath('data/3')
        correct = LoadSolution(filename)
        s.Load(filename)
        config = sdk.SolverConfig("SinglesSolver",0,5)
        solver = sdk.BranchingSolver(s, miter, dlvl, config)
        solver.Execute()
        for r in range(1,10):
            for c in range(1,10):
                self.assertEqual(correct[r-1][c-1], solver.GetSudoku()[r,c].GetValue())
    
# Execution

if __name__ == '__main__':
    unittest.main()

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
