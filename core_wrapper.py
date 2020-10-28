import sudoku_core as sdk

def copy_cell(self):
    return sdk.Cell(self)

setattr(sdk.Cell, "copy", copy_cell)

def copy_sudoku(self):
    return sdk.Sudoku(self)

setattr(sdk.Cell,   "copy", copy_cell)
setattr(sdk.Sudoku, "copy", copy_sudoku)