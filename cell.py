#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Oct 19 20:06:56 2020

@author: eduard
"""


class Cell:
    def __init__(self, value=None):
        if value is None:
            self.isKnown = False
            self.value = 0
            self.possibilities = [i for i in range(1,10)]
        else:
            self.isKnown = True
            self.value = value
            self.possibilities = [value]    
    
    def __str__(self):
        if self.isKnown:
            return str(self.value)
        return '·'
    
    def __isub__(self, value):
        # Removes a possibility from a cell.
        if self.isKnown:
            return
        
        if type(value) == int:
            self.RemoveOption(value)
        elif type(value) == list:
            for x in value:
                self.RemoveOption(x)
        else:
            raise TypeError
            
        if len(self.possibilities) == 1:
            self.Resolve(self.possibilities[0])
            return
          
    def RemoveOption(self, value):
        try:
            self.possibilities.remove(value)
            return
        except ValueError:
            return
        
    def Resolve(self, value):
        self.isKnown = True
        self.value = value
        self.possibilities = [value]
        
    def ResetCell(self):
        self.isKnown = False
        self.value = 0
        self.possibilities = [i for i in range(1,10)]