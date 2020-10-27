#include "cell.h"
#include <tuple>

Cell::Cell(const int i, const int j)
{
    row = i;
    col = j;
}

std::tuple<int, int> Cell::GetCoords()
{
    return std::tie(row, col);
}
