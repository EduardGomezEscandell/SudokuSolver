#include "branchingsolver.h"

namespace SudokuSolve {


bool BranchingSolver::IterateOnce()
{
    bool no_uncertainty = false;
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
            PrintStatus(Status::progressed);
        }
    } catch (CellLevelError e) {
        // Reached impossibility. Popping stack.
        RevertBranch();
        PrintStatus(Status::popped, &e.mCell);
        return false;
    } catch (CannotProgressError e){
        // Stuck. Pushing copy to stack and guessing candidate.
        Cell & guessed_cell = TakeBranch();
        PrintStatus(Status::pushed, &guessed_cell);
    }

    return false;
}

std::string BranchingSolver::GetDescription() const
{
    return "A recursive solver that uses branhing";
}

void BranchingSolver::RevertBranch()
{
    if(mStack.size() == 0)
    {
        throw SolveError("Attempted to pop an empty stack.");
    }
    SwitchSudoku(*mStack.back());
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
    mStack.emplace_back(std::make_shared<Sudoku>(*mpSudoku));
    (*mStack.back())[coords].PopCandidate(guess);

    // Solving active copy of the grid
    (*mpSudoku)[coords].Solve(guess);

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
    std::string stackstr("|", mStack.size());

    std::string coords = "UNKNOWN";
    int value = -1;
    if(cell)
    {
        coords = cell->GetFormatedCoords();
        value = cell->GetValue();
    }

    switch (status) {
        case Status::solved:
            msg << "Solved on step "<<mIters;
            break;
        case Status::progressed:
            msg << stackstr << " - Step "<<mIters<<": Reduced uncertainty down to " << mpSudoku->GetUncertainty();
            break;
        case Status::pushed:
            msg << stackstr << "> - Step "<<mIters<<": Guessed that " <<  coords << " is " << value;
            break;
        case Status::popped:
            msg << stackstr << "< - Step "<<mIters<<": Reached an impossibility at " << coords;
            break;
    }

    msg << std::endl;
    PRINT(Debug::info, msg.str());
}


} //namespace SudokuSolve
