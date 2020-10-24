from sudoku import Sudoku
from errors import SolveError, CellLevelError, VerificationError, NoCandidatesError, CannotProgressError, ReachedMaxIterError

class Solver:
    def __init__(self, sudoku, maxiter=1000, debug_lvl=0):
        self.sudoku = sudoku
        self.maxiter = maxiter
        self.debug_lvl = debug_lvl
        self.extra_init()
        # 0: No prints
        # 1: Only final result
        # 2: Step-by-step info
        # 3: Step-by-step info and partial results
    def extra_init(self):
        pass
    
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
        
        if self.sudoku.GetUncertainty() > 0:
            raise SolveError('Failed to remove all uncertainty')
                
        try:
            self.sudoku.AssertCorrect()
            if self.debug_lvl > 0 : print('The grid is correct')
        except VerificationError:
            if self.debug_lvl > 0 : print('The grid is INCORRECT')

class SinglesSolver(Solver):
    def extra_init(self):
        self.uncertainty = self.sudoku.GetUncertainty()
        
    def iterate_once(self,i):
        self.naked_single_pass()
        self.hidden_single_pass()
        
        uncert_old = self.uncertainty
        self.uncertainty = self.sudoku.GetUncertainty()
        if self.uncertainty == uncert_old:
            raise CannotProgressError()

class BranchingSolver(Solver):
    def extra_init(self):
        self.uncertainty = self.sudoku.GetUncertainty()
        if self.debug_lvl > 1 : print(' START - %.2f%% uncertainty\n'%(100*self.uncertainty))
        self.snapshots = []
        
        self.logicalsolver = SinglesSolver(self.sudoku, maxiter=5, debug_lvl=0)
    
    def iterate_once(self,i):
        try:
            old_uncert = self.uncertainty
            
            self.naked_single_pass()
            self.hidden_single_pass()
            self.uncertainty = self.sudoku.GetUncertainty()
            
            if self.uncertainty == 0:
                self.sudoku.AssertNoDuplicates()
                if self.debug_lvl > 1 : print('<'*len(self.snapshots),'Step %d - Solved (0%% uncertainty)'%i)
                return True
            
        except CellLevelError as e:
            try:
                self.sudoku = self.snapshots.pop()
            except IndexError:
                raise SolveError('Unexpected failed branch popping')
            if self.debug_lvl > 1 : print('|'*len(self.snapshots) +'< Step %d'%i,'- Impossibility reached at %s'%e.GetCellCoords())
            if self.debug_lvl > 2 : print(self.sudoku)
            return False
        
        
        if old_uncert == self.uncertainty:
            index = self.best_guess()
            guess = self.sudoku[index].candidates[0]
            if self.debug_lvl > 1 : print('|'*(len(self.snapshots)) 
                + '> Step %i - Guessing %s is %d out of'%(i,self.sudoku[index].GetCoords(),guess),self.sudoku[index].candidates)
            self.snapshots.append(self.sudoku.copy())
            self.snapshots[-1][index].RemoveOption(guess)
            self.sudoku[index].Resolve(guess)
            self.uncertainty = self.sudoku.GetUncertainty()
            
        else:
            if self.debug_lvl > 1 : print('|'*len(self.snapshots) + ' Step %d - Reduced uncertainty to %.2f%%'%(i, 100*self.uncertainty))
            
        if self.debug_lvl > 2 : print(self.sudoku)
        return False
                
    def best_guess(self):
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