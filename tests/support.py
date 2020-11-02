#!/usr/bin/env python3
import os

# Support functions


def GetPath(filename):
    thisfile = os.path.abspath(__file__)
    dirpath = '/'.join(thisfile.split('/')[:-1])
    return dirpath + '/' + filename    
    
def LoadSolution(filename_no_extension):
    filename = filename_no_extension + '.sdk'
    correct = [[0]*9 for i in range(9)]
    with open(filename) as f:
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
    return correct

def LoadSudoku(filename_no_extension):
    filename = filename_no_extension + '.sdk'
    correct = [[0]*9 for i in range(9)]
    with open(filename) as f:
        for line in f:
            if "Begin Sudoku" in line:
                break
        i = 0
        for line in f:
            if "End Sudoku" in line:
                break
            j = 0
            for c in line:
                if c=='\n':
                    break                
                correct[i][j] = int(c)
                j+=1
            i+=1
    return correct