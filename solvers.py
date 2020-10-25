from errors import SolveError, CellLevelError, VerificationError, CannotProgressError, ReachedMaxIterError

class Solver:
    def __init__(self, sudoku, *args, **kwargs):
        self.maxiter=1000
        self.debug_lvl=0
        if 'maxiter'   in kwargs: self.maxiter  = kwargs['maxiter']
        if 'debug_lvl' in kwargs: self.debug_lvl= kwargs['debug_lvl']
        
        self.sudoku = sudoku
        self.child_solvers = []
        self.extra_init(args, kwargs)
        # DEBUG_LVL:
        # 0: No prints
        # 1: Only final result
        # 2: Step-by-step info
        # 3: Step-by-step info and partial results
    
    def extra_init(self,*args, **kwargs):
        pass
    
    def print(self, *msg, **kwargs):
        debug_lvl_required = 0
        if 'debug_lvl'  in kwargs: debug_lvl_required = kwargs['debug_lvl']
        if self.debug_lvl > debug_lvl_required:
            print(*msg)
        
    def SwitchSudoku(self, new_sudoku):
        self.sudoku = new_sudoku
        for c in self.child_solvers:
            c.SwitchSudoku(new_sudoku)
    
    def Execute(self):
        try:
            for npasses in range(1,1+self.maxiter):
                finished = self.iterate_once(npasses)
                if finished: break
                self.print(self.sudoku,debug_lvl=2)
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
        
        self.print(' ',debug_lvl=1)
        self.print('\n       SOLUTION\n%s%d passes employed'%(self.sudoku,npasses), debug_lvl=0)
        
        if self.sudoku.UpdateUncertainty() > 0:
            raise SolveError('Failed to remove all uncertainty')

    def Verify(self):
        try:
            self.sudoku.AssertCorrect()
            self.print('The grid is correct')
        except VerificationError:
            self.print('The grid is INCORRECT')

class SinglesSolver(Solver):
    def extra_init(self, *args, **kwargs):
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
    # Necessary methods
    def extra_init(self, *args, **kwargs):
        self.print(' START - %.2f%% uncertainty\n'%(100*self.sudoku.UpdateUncertainty()), debug_lvl=1)
        self.snapshots = []
        self.child_solvers.append(SinglesSolver(self.sudoku, 5))
    
    def iterate_once(self,i):
        no_uncertainty = False
        try:
            for child in self.child_solvers:
                no_uncertainty = child.iterate_once(i)            
                if no_uncertainty:
                    self.sudoku.AssertNoDuplicates()
                    self.print('<'*len(self.snapshots),'Step %d - Solved (0%% uncertainty)'%i, debug_lvl=1)
                    return True
                self.print('|'*len(self.snapshots) + ' Step %d - Reduced uncertainty to %.2f%%'%(i, 100*self.sudoku.UpdateUncertainty()),debug_lvl=1)
            
        except CellLevelError as e:
            self.revert_branch()
            self.print('|'*len(self.snapshots) +'< Step %d'%i,'- Impossibility reached at %s'%e.GetCellCoords(),debug_lvl=1)
            return False
        
        except CannotProgressError:
            index = self.cell_fewest_candidates()
            guess = self.sudoku[index].candidates[0]
            self.print('|'*(len(self.snapshots)) + '> Step %i - Guessing %s is %d out of'%(i,self.sudoku[index].GetCoords(),guess),self.sudoku[index].candidates,debug_lvl=1)
            self.take_branch(index, guess)
        return False
    
    # Support methods
    
    def take_branch(self, index, guess):
        self.snapshots.append(self.sudoku.copy())
        self.snapshots[-1][index].RemoveOption(guess)
        self.sudoku[index].Resolve(guess)
        self.sudoku.UpdateUncertainty()
        
    def revert_branch(self):
        try:
            self.SwitchSudoku(self.snapshots.pop())
        except IndexError:
            raise SolveError('Unexpected failed branch popping')
        self.sudoku.UpdateUncertainty()
                
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