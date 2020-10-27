#include "sudoku.h"

Sudoku::Sudoku()
{
    // Generating grid
    mGrid.resize(9);
    for(int i=0; i<9; i++)
    {
        mGrid[i].resize(9);
        for(int j=0; j<9;j++)
        {
            mGrid[i][j] = std::make_shared<Cell>(i+1,j+1);
        }
    }
    // Generating boxes
    mBoxes.resize(9);
    for(int b=0; b<9; b++)
    {
        mBoxes[b].resize(9);
        for(int k=0; k<9;k++)
        {
            int i = b/3 + k/3;
            int j = b%3 + k%3;
            mBoxes[b][k] = mGrid[i][j];
        }
    }
}

void Sudoku::Load(std::string filename)
{
    filename += ".vtk";
    std::ifstream f(filename);
    std::string line;
    // Skipping to begining of sudoku
    while (getline (f, line))
    {
        if(line.find("Begin Sudoku"))
        {
            break;
        }
    }
    // Reading sudoku
    int i=0,j=0,val;
    while (getline (f, line))
    {
        if(line.find("End Sudoku")) break;
        for(char & c : line){
            // if(c == '\0') break;
            val = (int)c - 48;
            if(val > 0 || val < 10){
                mGrid[i][j]->Solve(val);
                j++;
                break;
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
            outp += mGrid[i][j]->ToString();
            if(j%3 == 2) outp += ' ';
        }
        if(i==2 || i==5) outp += '\n';
    }
    return outp;
}
