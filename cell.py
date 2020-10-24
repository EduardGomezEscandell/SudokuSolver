from errors import NoCandidatesError

class Cell:
    def __init__(self, key, value=None):
        if value is None:
            self.key = key
            self.isKnown = False
            self.value = 0
            self.candidates = [i for i in range(1,10)]
        else:
            self.isKnown = True
            self.value = value
            self.candidates = [value]
    
    def copy(self):
        newcell = Cell(self.key)
        newcell.isKnown = self.isKnown
        newcell.value = self.value
        newcell.candidates = self.candidates.copy()
        return newcell
    
    def __str__(self):
        if self.isKnown:
            return '%d'%(self.value)
        return '·'
    
    def __isub__(self, x):
        # Removes a possibility from a cell.
        self.RemoveOption(x)
        return self
    
    def GetCoords(self):
        return 'r%dc%d'%(self.key)
              
    def RemoveOption(self, value):
        try:
            self.candidates.remove(value)
        except ValueError:
            return
        if len(self.candidates) == 1:
            self.Resolve(self.candidates[0])
        elif len(self.candidates) == 0:
            raise NoCandidatesError(self)
        
    def Resolve(self, value):
        self.isKnown = True
        self.value = value
        self.candidates = [value]
        
    def ResetCell(self):
        self.isKnown = False
        self.value = 0
        self.candidates = [i for i in range(1,10)]