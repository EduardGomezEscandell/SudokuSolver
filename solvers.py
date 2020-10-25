from errors import SolveError, CellLevelError, VerificationError, CannotProgressError, ReachedMaxIterError

class Solver:
    def __init__(self, sudoku, maxiter=1000, debug_lvl=0):
        self.sudoku = sudoku
        self.maxiter = maxiter
        self.debug_lvl = debug_lvl
        self.child_solvers = []
        self.extra_init()
        # DEBUG_LVL:
        # 0: No prints
        # 1: Only final result
        # 2: Step-by-step info
        # 3: Step-by-step info and partial results
    def extra_init(self):
        pass
    
    def SwitchSudoku(self, new_sudoku):
        self.sudoku = new_sudoku
        for c in self.child_solvers:
            c.SwitchSudoku(new_sudoku)
    
    def Execute(self):
        try:
            for npasses in range(1,1+self.maxiter):
                finished = self.iterate_once(npasses)
                if finished: break
        except KeyboardInterrupt:
            pass
        self.Finalize(npasses)
        
    def iterate_once(self,i):
        raise SolveError('This is a base class. Please use a subclass to solve.')

    def hidden_single_pass(self):
        for i in range(9):
            self.sudoku.HiddenSingleInRow(i+1)
            self.sudoku.HiddenSingleInCol(i+1)
            self.sudoku.HiddenSingleInBox(i+1)
            
    def naked_single_pass(self):
        for i in range(9):
            self.sudoku.NakedSingleInRow(i+1)
            self.sudoku.NakedSingleInCol(i+1)
            self.sudoku.NakedSingleInBox(i+1)
            
    def Finalize(self, npasses):
        if npasses==self.maxiter:
            raise ReachedMaxIterError()
        
        if self.debug_lvl > 1 : print('')
        if self.debug_lvl > 0:
            print('\n       SOLUTION')
            print(self.sudoku)
            print('%d passes employed'%npasses)
        
        if self.sudoku.UpdateUncertainty() > 0:
            raise SolveError('Failed to remove all uncertainty')

    def Verify(self):
        try:
            self.sudoku.AssertCorrect()
            if self.debug_lvl > 0 : print('The grid is correct')
        except VerificationError:
            if self.debug_lvl > 0 : print('The grid is INCORRECT')

class SinglesSolver(Solver):
    def extra_init(self):
        self.sudoku.UpdateUncertainty()
        
    def iterate_once(self,i):
        self.naked_single_pass()
        self.hidden_single_pass()
        
        uncert_old = self.sudoku.cached_uncertainty
        
        if self.sudoku.UpdateUncertainty() == 0:
            return True
        
        if self.sudoku.cached_uncertainty == uncert_old:
            raise CannotProgressError(i)
        
        return False

class BranchingSolver(Solver):
    def extra_init(self):
        if self.debug_lvl > 1 : print(' START - %.2f%% uncertainty\n'%(100*self.sudoku.UpdateUncertainty()))
        self.snapshots = []
        self.child_solvers.append(SinglesSolver(self.sudoku, 5))
    
    def iterate_once(self,i):
        cannot_progress = False
        no_uncertainty = False
        try:
            for child in self.child_solvers:
                no_uncertainty = child.iterate_once(i)            
                if no_uncertainty:
                    self.sudoku.AssertNoDuplicates()
                    if self.debug_lvl > 1 : print('<'*len(self.snapshots),'Step %d - Solved (0%% uncertainty)'%i)
                    return True
                if self.debug_lvl > 1 : print('|'*len(self.snapshots) + ' Step %d - Reduced uncertainty to %.2f%%'%(i, 100*self.sudoku.UpdateUncertainty()))
            
        except CellLevelError as e:
            try:
                self.SwitchSudoku(self.snapshots.pop())
            except IndexError:
                raise SolveError('Unexpected failed branch popping')
            self.sudoku.UpdateUncertainty()
            if self.debug_lvl > 1 : print('|'*len(self.snapshots) +'< Step %d'%i,'- Impossibility reached at %s'%e.GetCellCoords())
            if self.debug_lvl > 2 : print(self.sudoku)
            return False
        
        except CannotProgressError:
            index = self.cell_fewest_candidates()
            guess = self.sudoku[index].candidates[0]
            if self.debug_lvl > 1 : print('|'*(len(self.snapshots)) 
                + '> Step %i - Guessing %s is %d out of'%(i,self.sudoku[index].GetCoords(),guess),self.sudoku[index].candidates)
            self.snapshots.append(self.sudoku.copy())
            self.snapshots[-1][index].RemoveOption(guess)
            self.sudoku[index].Resolve(guess)
            self.sudoku.UpdateUncertainty()            

        if self.debug_lvl > 2 : print(self.sudoku)
        return False
                
    def cell_fewest_candidates(self):
        min_n_candidates = 10
        min_id = -1
        for i in range(1,10):
            for j in range(1,10):
                if (not self.sudoku[i,j].isKnown):
                    ln = len(self.sudoku[i,j].candidates)
                    if ln == 2:
                        return (i,j) # Can't be improved upon
                    if ln<min_n_candidates:
                        min_id = (i,j)
                        min_n_candidates = ln
        return min_id