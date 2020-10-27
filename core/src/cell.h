#ifndef CELL_H
#define CELL_H

#include <tuple>

class Cell
{
public:
    Cell(const int i, const int j);
    std::tuple<int, int> GetCoords();
protected:
    int row;
    int col;
};

#endif // CELL_H
