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
        s = sdk.Sudoku()
        filename = GetPath('data/1')
        s.Load(filename)
        values=[[0]*9 for i in range(9)]
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

        

if __name__ == '__main__':
    unittest.main()