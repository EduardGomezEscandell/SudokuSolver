#include "branchingsolver.h"

namespace SudokuSolve {


bool BranchingSolver::IterateOnce()
{
    bool no_uncertainty = false;
    double uncertainty = mpSudoku->GetUncertainty();
    try {
        for(Solver * child : mChildSolvers)
        {
            no_uncertainty = child->IterateOnce();

            if(no_uncertainty)
            {
                mpSudoku->assertNoDuplicates(); // If it fails, a DuplicateEntryError is thrown (a subclass of CellLevelError)
                PrintStatus(Status::solved);
                return true;
            }
        }
        double new_uncertainty = mpSudoku->GetUncertainty();
        if(new_uncertainty == uncertainty)
        {
            // Stuck. Pushing copy to stack and guessing candidate.
            Cell & guessed_cell = TakeBranch();
            PrintStatus(Status::pushed, &guessed_cell);
        } else {
            PrintStatus(Status::progressed);
        }
    }
    catch (CannotProgressError & e)
    {
        // Stuck. Pushing copy to stack and guessing candidate.
        Cell & guessed_cell = TakeBranch();
        PrintStatus(Status::pushed, &guessed_cell);
    }

    catch (CellLevelError & e) {
        // Reached impossibility. Popping stack.
        RevertBranch();
        PrintStatus(Status::popped, &e.mCell);
        return false;
    }
    return false;
}

void BranchingSolver::RevertBranch()
{
    if(mStack.empty())
    {
        throw SolveError("Attempted to pop an empty stack.");
    }
    SwitchSudoku(mStack.back());
    mStack.pop_back();
}

Cell & BranchingSolver::TakeBranch()
{
    Cell * cell = mpSudoku->CellWithFewestCandidates();
    if(cell == nullptr)
    {
        throw SolveError("Method Sudoku::CellWithFewestCandidates returned a null poiter. The sudoku might have been solved already");
    }
    // Chosing guess
    std::tuple<int,int> coords = cell->GetCoords();
    int guess = cell->GetCandidates().front();

    // Pushing copy of the grid to stack and removing guess from candidates
    mStack.push_back(std::make_shared<Sudoku>(*mpSudoku));
    (*mStack.back().get())[coords].PopCandidate(guess);

    // Solving active copy of the grid
    (*mpSudoku.get())[coords].Solve(guess);

    // Returning cell in which guess was taken
    return *cell;
}

void BranchingSolver::PrintStatus(const Status status)
{
    PrintStatus(status, nullptr);
}

void BranchingSolver::PrintStatus(const Status status, const Cell * cell)
{
    std::stringstream msg;

    std::string coords = "UNKNOWN";
    int value = -1;
    if(cell)
    {
        coords = cell->GetFormatedCoords();
        value = cell->GetValue();
    }

    int stacksize = mStack.size();
    std::string stack(stacksize, '|');
    std::string stack1((stacksize > 0) ? stacksize-1 : stacksize, '|');

    switch (status) {
        case Status::solved:
            msg << "Solved on step "<<mIters;
            break;
        case Status::progressed:
            msg << stack  << " - Step "<<mIters+1<<": Reduced uncertainty down to " << mpSudoku->GetUncertainty();
            break;
        case Status::pushed:
            msg<< stack1  << "> - Step "<<mIters+1<<": Guessed that " <<  coords << " is " << value;
            break;
        case Status::popped:
            msg<< stack << "< - Step "<<mIters+1<<": Reached an impossibility at " << coords;
            break;
    }
    PRINT(Debug::info, msg.str());
}

std::string BranchingSolver::GetDescription() const
{
    return "BranchingSolver: A recursive solver that uses branching";
}

} //namespace SudokuSolve
