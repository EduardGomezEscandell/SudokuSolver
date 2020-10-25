from cell import Cell
from errors import VerificationError, DuplicateEntryError


def skip_to_line(f, target):
    for line in f:
        if target in line:
            return line
    raise "Line not found"


class Sudoku:

    def __init__(self):
        self.board = [[Cell((i+1,j+1)) for j in range(9)] for i in range(9)]
        self.known_rows = []
        self.known_cols = []
        self.known_boxes = []
        
        self.boxes = [self.BuildBox(i) for i in range(1,10)]

    def load(self, filename, loadsolution='False'):
        filename += '.sdk'        
        with open(filename,"r") as f:
            line = skip_to_line(f, "Begin Sudoku")
            i = 0
            for line in f:
                if "End" in line:
                    break
                j = 0
                for c in line:
                    if c=='\n':
                        break
                    if c != '0':
                        self.board[i][j].Resolve(int(c))
                    j+=1
                i+=1
            if loadsolution:
                self.correct = [[0 for i in range(9)] for i in range(9)]
                line = skip_to_line(f, "Begin Solution")
                i = 0
                for line in f:
                    if "End" in line:
                        break
                    j = 0
                    for c in line:
                        if c=='\n':
                            break                
                        self.correct[i][j] = int(c)
                        j+=1
                    i+=1

    def __str__(self):
        ret = ''
        for i in range(9):
            for j in range(9):
                ret += ' ' + str(self.board[i][j])
                if(j%3==2):
                    ret += ' '
            ret += '\n'
            if(i%3 == 2):
                ret += '\n'
        return(ret)

    def copy(self):
        new_sudoku = Sudoku()
        for i in range(9):
            for j in range(9):
                new_sudoku.board[i][j] = self.board[i][j].copy()
        new_sudoku.known_rows  = self.known_rows
        new_sudoku.known_cols  = self.known_cols
        new_sudoku.known_boxes = self.known_boxes
        new_sudoku.correct = self.correct
        return new_sudoku

    #################################
    #                               #
    #   Getters and setters         #
    #                               #
    #################################    

    def __getitem__(self, key):
        if len(key) != 2:
            print("Only 2 index access supported")
            raise TypeError
        i = key[0] - 1
        j = key[1] - 1
        return self.board[i][j]
        
    def __setitem__(self, key, value):
        if len(key) != 2:
            print("Only 2 index access supported")
            raise TypeError
        i = key[0]-1
        j = key[1]-1
        if i>8 or j>8:
            raise IndexError
        self.board[i][j].Resolve(value)
        
    def BuildBox(self, bid):
        rows = [i + 3*((bid-1)//3) for i in range(1,4)]
        cols = [j + 3*((bid-1)%3)  for j in range(1,4)]
        
        box = []
        for r in rows:
            for c in cols:
                box.append(self.board[r-1][c-1])
        return box
        
    #################################
    #                               #
    #        Aggregate Data         #
    #                               #
    #################################
    
    def AssertCorrect(self):
        for i in range(9):
            for j in range(9):
                cell = self.board[i][j]
                if cell.isKnown:
                    if cell.value != self.correct[i][j]:
                        raise VerificationError(cell)
        
    def UpdateUncertainty(self):
        # Of potential placements
        ncandidates = 0
        for row in self.board:
            for cell in row:
                if cell.isKnown:
                    ncandidates +=1
                else:
                    ncandidates += len(cell.candidates)
        self.cached_uncertainty = (ncandidates - 81.0) / 648.0
        return self.cached_uncertainty
    

    def AssertNoDuplicates(self):
        for i in range(9):
            rowcounter = [0]*9
            colcounter = [0]*9
            boxcounter = [0]*9
            B = self.boxes[i]
            for j in range(9):
                cellrow = self[(i+1,j+1)]
                cellcol = self[(j+1,i+1)]
                cellbox = B[j]
                if cellrow.isKnown:
                    rowcounter[cellrow.value-1] += 1
                    if rowcounter[cellrow.value-1] > 1:
                        raise DuplicateEntryError(cellrow)
                if cellcol.isKnown:
                    colcounter[cellcol.value-1] += 1
                    if colcounter[cellcol.value-1] > 1:
                        raise DuplicateEntryError(cellcol)
                if cellbox.isKnown:
                    boxcounter[cellbox.value-1] += 1
                    if boxcounter[cellbox.value-1] > 1:
                        raise DuplicateEntryError(cellbox)
                
    def IsSolved(self):
        for i in range(9):
            for j in range(9):
                if not self.board[i][j].isKnown:
                    return False
        return True
    
    def HowManyMissing(self):
        ret = 0
        for i in range(9):
            for j in range(9):
                if not self.board[i][j].isKnown:
                    ret += 1
        return ret
    
    #################################
    #                               #
    #    Finding Naked Singles      #
    #                               #
    #################################
    
    def NakedSingleInRow(self, r):
        if r > 9:
            raise IndexError
        
        if r in self.known_rows:
            return
        
        knownvalues = 0
        for c in range(1,10):
            if self[r,c].isKnown:
                knownvalues += 1
                for ctarget in range(1,10):
                    if c!=ctarget:
                        self[r,ctarget].RemoveOption(self[r,c].value)
                        
        if knownvalues == 9:
            self.known_rows.append(r)
    
    def NakedSingleInCol(self, c):
        if c > 9:
            raise IndexError
        
        if c in self.known_rows:
            return
        
        knownvalues = 0
        for r in range(1,10):
            if self[r,c].isKnown:
                knownvalues += 1
                for rtarget in range(1,10):
                    if r!=rtarget:
                        self[rtarget,c].RemoveOption(self[r,c].value)
                        
        if knownvalues == 9:
            self.known_cols.append(c)
        
    def NakedSingleInBox(self, b):
        if b > 9:
            raise IndexError
        
        if b in self.known_boxes:
            return 
        
        knownvalues = 0
        for u in range(9):
            if self.boxes[b-1][u].isKnown:
                knownvalues += 1
                for utarget in range(9):
                    if u!=utarget:
                        self.boxes[b-1][utarget].RemoveOption(self.boxes[b-1][u].value)
                        
        if knownvalues == 9:
            self.known_boxes.append(b)
    
    #################################
    #                               #
    #   Finding Hidden Singles      #
    #                               #
    #################################
            
    def HiddenSingleInRow(self, row):
        if row > 9:
            raise IndexError
        
        if row in self.known_rows:
            return
        
        i = row - 1
        
        locations = [[] for a in range(9)]
        
        for j in range(9):
            cell = self.board[i][j]
            for x in cell.candidates:
                locations[x-1].append(j)
       
        for l in range(9):
            if len(locations[l]) == 1:
                cell = self.board[i][locations[l][0]]
                if not cell.isKnown:
                    cell.Resolve(l+1)
            
    def HiddenSingleInCol(self, col):
        if col > 9:
            raise IndexError
        
        if col in self.known_cols:
            return
        
        j = col - 1
        
        locations = [[] for a in range(9)]
        
        for i in range(9):
            cell = self.board[i][j]
            for x in cell.candidates:
                locations[x-1].append(i)
       
        for l in range(9):
            if len(locations[l]) == 1:
                cell = self.board[locations[l][0]][j]
                if not cell.isKnown:
                    cell.Resolve(l+1)
        
    def HiddenSingleInBox(self, b):
        if b > 9:
            raise IndexError
        
        if b in self.known_boxes:
            return
        
        locations = [[] for a in range(9)]
        
        for i in range(9):
            cell = self.boxes[b-1][i]
            for x in cell.candidates:
                locations[x-1].append(i)
       
        for l in range(9):
            if len(locations[l]) == 1:
                cell = self.boxes[b-1][locations[l][0]]
                if not cell.isKnown:
                    cell.Resolve(l+1)