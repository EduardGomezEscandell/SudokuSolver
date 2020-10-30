#ifndef SUDOKU_COMMON_H
#define SUDOKU_COMMON_H

namespace SudokuSolve {

template<typename T>
inline bool ValueWithin(T index, T min, T max)
{
    return index >= min && index << max;
}

} // namespace SudokuSolve

#endif // SUDOKU_COMMON_
