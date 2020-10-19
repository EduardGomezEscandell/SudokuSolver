class Cell:
    def __init__(self, value=None):
        if value is None:
            self.isKnown = False
            self.value = 0
            self.candidates = [i for i in range(1,10)]
        else:
            self.isKnown = True
            self.value = value
            self.candidates = [value]    
    
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
            
        if len(self.candidates) == 1:
            self.Resolve(self.candidates[0])
            return
          
    def RemoveOption(self, value):
        try:
            self.candidates.remove(value)
            return
        except ValueError:
            return
        
    def Resolve(self, value):
        self.isKnown = True
        self.value = value
        self.candidates = [value]
        
    def ResetCell(self):
        self.isKnown = False
        self.value = 0
        self.candidates = [i for i in range(1,10)]