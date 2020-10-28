#include "sudoku.h"

namespace py = pybind11;

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
        for(int k=0; k<9;k++)
        {
            int i = b/3 + k/3;
            int j = b%3 + k%3;
            mBoxes[b][k] = &(mGrid[i][j]);
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
            if(val > 0 && val < 10){
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

std::string Sudoku::ToString()
{
    std::string outp;
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            outp += mGrid[i][j].ToString();
            if(j%3 == 2) outp += ' ';
        }
        outp += '\n';
        if(i==2 || i==5) outp += '\n';
    }
    return outp;
}

Cell & Sudoku::operator()(const int row, const int col)
{
    if(row < 0 || row > 9 || col <0 || col > 9)
    {
        std::stringstream msg;
        msg<< "Tried to access r" << row << 'r' << col;
        throw std::out_of_range(msg.str());
    }
    return mGrid[row-1][col-1];
}

Cell & Sudoku::operator[](std::tuple<int, int> index)
{
    int row, col;
    std::tie(row,col) = index;
    return this->operator()(row,col);
}

void Sudoku::assertNoDuplicates()
{
    int value;
    for(int i=0; i<9; i++)
    {
        std::vector<int> rowcounter(10,0);
        std::vector<int> colcounter(10,0);
        std::vector<int> boxcounter(10,0);

        for(int j=0; j<9; j++)
        {
            std::stringstream ss;
            ss << 'r' << i << 'r' << j;
            std::string rowcol = ss.str();

            value = mGrid[i][j].isSolved() ? mGrid[i][j].GetValue() : 0;
            if(value && ++rowcounter[value] > 1) throw py::value_error("Invalid digit at "+rowcol);

            value = mGrid[j][i].isSolved() ? mGrid[j][i].GetValue() : 0;
            if(value && ++colcounter[value] > 1) throw py::value_error("Invalid digit at "+rowcol);

            value = mBoxes[i][j]->isSolved() ? mBoxes[i][j]->GetValue() : 0;
            if(value && ++boxcounter[value] > 1) throw py::value_error("Invalid digit at "+rowcol);
        }
    }
}

inline double Sudoku::GetUncertainty()
{
    return mAbsUncertainty / mMmaximumCandidates;
}
