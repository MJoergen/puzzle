#include <iomanip>

#include "array.h"

/**************************************************************************
 **************************************************************************/
ostream& operator<<(ostream& os, const Array<int>& board)
{
    for (unsigned int row=0; row<board.Rows(); row++)
    {
        for (unsigned int col=0; col<board.Cols(); col++)
        {
            if (board[row][col] != -1)
                os << setw(2) << setfill(' ') << board[row][col] << " ";
            else
                os << " . ";
        }
        os << endl;
    }
    return os;
}

