#ifndef SUDOKU_H
#define SUDOKU_H

#include "cell.h"

#include <vector>
#include <memory>
#include <fstream>
#include <string>

typedef std::vector<std::vector<std::shared_ptr<Cell>>> SharedGrid;
typedef std::vector<std::vector<std::weak_ptr<Cell>>> WeakGrid;

class Sudoku
{
public:
    Sudoku();
    void Load(std::string filename);
    std::string ToString();
protected:
    SharedGrid mGrid;
    WeakGrid mBoxes;
};

#endif // SUDOKU_H
