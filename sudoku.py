from cell import Cell

def skip_to_line(f, target):
    for line in f:
        if target in line:
            return line
    raise "Line not found"


class Sudoku:
    def __init__(self, filename):
        filename += '.sdk'
        self.board = [[Cell() for i in range(9)] for i in range(9)]
        f = open(filename,"r")
        line = skip_to_line(f, "Begin Sudoku")
        
        self.known_rows = []
        self.known_cols = []
        self.known_blocks = []
        
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
                    
    #################################
    #                               #
    #   Getters and setters         #
    #                               #
    #################################    
                
    def __getitem__(self, key):
        if len(key) != 2:
            raise "Only 2 index access supported"
        i = key[0] - 1
        j = key[1] - 1
        return self.board[i][j].candidates.copy()
        
    def __setitem__(self, key, value):
        if len(key) != 2:
            print("Only 2 index access supported")
            raise TypeError        
        i = key[0]-1
        j = key[1]-1
        if i>8 or j>8:
            raise IndexError
        self.board[key].Resolve(value)
        
    def GetBlock(self, bid):
        rows = [i + 3*((bid-1)//3) for i in range(1,4)]
        cols = [j + 3*((bid-1)%3)  for j in range(1,4)]
        
        block = []
        for r in rows:
            for c in cols:
                block.append(self.board[r-1][c-1])
        return block
        
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
                        raise Exception('Mismatch at cell (%d, %d)'%(i+1,j+1))
        
            
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
    
    def NakedSingleInRow(self, row):
        if row > 9:
            raise IndexError
        
        if row in self.known_rows:
            return
        
        i = row - 1
        knowns = [cell.value for cell in self.board[i] if cell.isKnown]
        if len(knowns) == 9:
            self.known_rows.append(row)
            return
                
        for cell in self.board[i]:
            cell -= knowns
    
    def NakedSingleInCol(self, col):
        if col > 9:
            raise IndexError
        
        if col in self.known_cols:
            return
        
        j = col - 1
        knowns = [row[j].value for row in self.board if row[j].isKnown]
        if len(knowns) == 9:
            self.known_cols.append(col)
            return
                
        for row in self.board:
            cell = row[j]
            cell -= knowns
        
    def NakedSingleInBlock(self, b):
        if b > 9:
            raise IndexError
        
        if b in self.known_blocks:
            return
        
        B = self.GetBlock(b)        
        
        knowns = [cell.value for cell in B if cell.isKnown]
        if len(knowns) == 9:
            self.known_blocks.append(b)
            return
                
        for cell in B:
            cell -= knowns
    
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
        
    def HiddenSingleInBlock(self, b):
        if b > 9:
            raise IndexError
        
        if b in self.known_blocks:
            return
        
        block = self.GetBlock(b)
        
        locations = [[] for a in range(9)]
        
        for i in range(9):
            cell = block[i]
            for x in cell.candidates:
                locations[x-1].append(i)
       
        for l in range(9):
            if len(locations[l]) == 1:
                cell = block[locations[l][0]]
                if not cell.isKnown:
                    cell.Resolve(l+1)