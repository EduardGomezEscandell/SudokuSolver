class SolveError(Exception):
    def __init__(self, msg):
        self.msg = msg
        
    def __str__(self):
        return self.msg
    
class ReachedMaxIterError(SolveError):
    def __init__(self):
        self.msg = 'Ran out of iterations'

class CannotProgressError(SolveError):
    def __init__(self):
        self.msg = 'Cannot advance any further. Try a more robust algorithm.'


class CellLevelError(Exception):
    def __init__(self, cell):
        self.cell = cell
    
    def GetCellCoords(self):
        return self.cell.GetCoords()

class NoCandidatesError(CellLevelError):
    def __str__(self):
        return 'Cell %s ran out of candidates'%self.getCellCoords()
        
class DuplicateEntryError(CellLevelError):
    def __str__(self):
        return 'Invalid value at cell %s'%self.getCellCoords()

class VerificationError(CellLevelError):
    def __str__(self):
        return 'Mismatch at cell %s'%self.getCellCoords()