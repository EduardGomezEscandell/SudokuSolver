#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <string>
#include <tuple>
#include <list>

typedef std::list<int> Candidates;

class Cell
{
public:
    // Constructors
    Cell(const int i, const int j);
    Cell(Cell & rOther); // Copy constructor

    // Getters
    std::tuple<int, int> GetCoords();
    int GetValue();
    Candidates GetCandidates();

    // Output
    std::string ToString();
    std::ostream & operator<<(std::ostream & Str);

    // Manipulators
    int PopCandidate(const int toRemove);
    void Solve(const int value);
protected:
    int mRow;
    int mCol;
    int mValue;
    bool mSolved;
    Candidates mCandidates;
};

#endif // CELL_H
