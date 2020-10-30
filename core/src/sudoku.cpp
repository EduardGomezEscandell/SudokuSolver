#include "sudoku.h"
#include "exceptions.h"

namespace py = pybind11;

namespace SudokuSolve{

Sudoku::Sudoku()
{
    // Generating grid
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9;j++)
        {
            mGrid[i][j].GiveOwner(i+1,j+1, *this);
        }
    }
    // Generating boxes
    BuildBoxes();
}

Sudoku::Sudoku(const Sudoku & rRHS)
{
    // Building grid
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            mGrid[i][j] = rRHS.mGrid[i][j];
        }
    }
    // Building boxes
    BuildBoxes();
}

void Sudoku::BuildBoxes()
{
    for(int b=0; b<9; b++)
    {
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {
                int row = i + 3*(b/3);
                int col = j + 3*(b%3);
                mBoxes[b][3*i+j] = &(mGrid[row][col]);
            }
        }
    }
}

void Sudoku::Load(std::string filename)
{
    filename += ".sdk";


    std::ifstream f(filename);

    std::string line;
    // Skipping to begining of sudoku
    while (getline (f, line))
    {
        if(line.find("Begin Sudoku") !=std::string::npos)
        {
            break;
        }
        getline (f, line);
    }
    // Reading sudoku
    int i=0;
    int j=0,val;
    while (getline (f, line))
    {
        j = 0;
        if(line.find("End Sudoku") != std::string::npos) break;
        for(char & c : line){
            if(c == '\n') break;
            val = (int)c - 48;
            if(ValueWithin(val,1,9)){
                mGrid[i][j].Solve(val);
                j++;
            }
            if(val == 0){
                j++;
            }
        }
        i++;
    }

    f.close();
}

std::string Sudoku::ToString() const
{
    std::stringstream ss;
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            ss << mGrid[i][j].ToString();
            if(j%3 == 2) ss << ' ';
        }
        ss<<std::endl;
        if(i==2 || i==5) ss<<std::endl;
    }
    return ss.str();
}

Cell & Sudoku::operator()(const int row, const int col)
{
    if(!ValueWithin(row,0,9) || !ValueWithin(col,0,9))
    {
        std::stringstream msg;
        msg<< "Tried to access r" << row << 'c' << col;
        throw py::index_error(msg.str());
    }
    return mGrid[row-1][col-1];
}

Cell & Sudoku::operator[](std::tuple<int, int> index)
{
    int row, col;
    std::tie(row,col) = index;
    return this->operator()(row,col);
}

void Sudoku::assertNoDuplicates() const
{
    int value;
    for(int i=0; i<9; i++)
    {
        std::vector<int> rowcounter(10,0);
        std::vector<int> colcounter(10,0);
        std::vector<int> boxcounter(10,0);

        for(int j=0; j<9; j++)
        {
            value = mGrid[i][j].IsSolved() ? mGrid[i][j].GetValue() : 0;
            if(value && ++rowcounter[value] > 1) throw DuplicateEntryError(mGrid[i][j]);

            value = mGrid[j][i].IsSolved() ? mGrid[j][i].GetValue() : 0;
            if(value && ++colcounter[value] > 1) throw DuplicateEntryError(mGrid[j][i]);

            value = mBoxes[i][j]->IsSolved() ? mBoxes[i][j]->GetValue() : 0;
            if(value && ++boxcounter[value] > 1) throw DuplicateEntryError(*mBoxes[i][j]);
        }
    }
}

double Sudoku::GetUncertainty()  const
{
    return mAbsUncertainty / mMmaximumCandidates;
}

Cell & Sudoku::AccessByBox(const int boxId, const int entry)
{
    if(!ValueWithin(boxId,0,9) || !ValueWithin(entry,0,9))
    {
        std::stringstream msg;
        msg<< "Tried to access b" << boxId <<"e"<<entry;
        throw py::index_error(msg.str());
    }
    return *(mBoxes[boxId-1][entry-1]);
}

} //namespace SudokuSolve
