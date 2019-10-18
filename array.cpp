#include <iomanip>

#include "array.h"

std::ostream& operator<<(std::ostream& os, const Array<int>& board)
{
    for (unsigned int row=0; row<board.Rows(); row++)
    {
        for (unsigned int col=0; col<board.Cols(); col++)
        {
            if (board[row][col] != -1)
                os << std::setw(2) << std::setfill(' ') << board[row][col] << " ";
            else
                os << " . ";
        }
        os << std::endl;
    }
    return os;
}

