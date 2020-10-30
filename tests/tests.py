#!/usr/bin/python
import unittest
import os
import sudoku_core as sdk


def GetPath(filename):
    thisfile = os.path.abspath(__file__)
    dirpath = '/'.join(thisfile.split('/')[:-1])
    return dirpath + '/' + filename


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
        s0.Load(filename)
        values=[[0]*9 for i in range(9)]
        s=s0.copy() # Testing copy
        with open(filename + '.sdk', "r") as f:
            i = 0
            for line in f:
                if "Begin Sudoku" in line:
                    break
            for line in f:
                if "End Sudoku" in line:
                    break
                j = 0
                for c in line:
                    if c=='\n':
                        break
                    values[i][j] = int(c)
                    j += 1
                i += 1
        
        for r in range(1,10):
            for c in range(1,10):
                cell = s[r,c]
                try:
                    if cell.IsSolved():
                        self.assertEqual(values[r-1][c-1], cell.GetValue())
                    else:
                        self.assertEqual(values[r-1][c-1], 0)
                except:
                    raise AssertionError("Failure at r%dc%d"%cell.GetCoords())

    def test_Solver_init(self):
        s = sdk.Sudoku()
        dlvl = 1
        miter = 20
        filename = GetPath('data/1')
        s.Load(filename)
        solver = sdk.Solver(s, miter, dlvl)
        msg = str(solver)
        print(msg)
        self.assertIn("Base class for solvers",msg)
        self.assertIn(str(miter),msg)
        self.assertIn(str(dlvl),msg)
        
    def test_Solver_solve(self):
        print('')
        s = sdk.Sudoku()
        dlvl = 1
        miter = 200
        filename = GetPath('data/1')
        correct = [[0]*9 for i in range(9)]
        with open(filename + '.sdk') as f:
            for line in f:
                if "Begin Solution" in line:
                    break
            i = 0
            for line in f:
                if "End Solution" in line:
                    break
                j = 0
                for c in line:
                    if c=='\n':
                        break                
                    correct[i][j] = int(c)
                    j+=1
                i+=1
        s.Load(filename)
        solver = sdk.SinglesSolver(s, miter, dlvl)
        solver.Execute()
        print(solver)
        for r in range(1,10):
            for c in range(1,10):
                self.assertEqual(correct[r-1][c-1], solver.GetSudoku()[r,c].GetValue())

if __name__ == '__main__':
    unittest.main()
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    