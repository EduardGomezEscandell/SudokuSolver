#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Oct 19 19:41:45 2020

@author: eduard
"""

from sudoku import Sudoku

s = Sudoku('data/2')
print(s)
s.AssertCorrect()

for i in range(15):
    if s.IsSolved():
        break
    
    print(s)
    
    for i in range(1,10):
        s.RemoveDuplicatesRow(i)
        s.RemoveDuplicatesCol(i)
        s.RemoveDuplicatesBlock(i)
        
        s.FindMissingRow(i)
        s.FindMissingCol(i)
        s.FindMissingBlock(i)

print(s)
s.AssertCorrect()