
#include "orientation.h"
#include "trace.h"

/**************************************************************************
 **************************************************************************/
std::ostream& operator<<(std::ostream& os, const COrientations& orientation)
{
    for (unsigned int block=0; block<orientation.m_blocks.size(); block++)
    {
        os << "Block number " << block << ":" << std::endl;
        os << orientation.m_blocks[block] << std::endl;
    } /* end of for */
    return os;
}

/**************************************************************************
 **************************************************************************/
COrientations::COrientations(std::vector<BlockInfo> blocks)
{
    TRACE_FUNCTION("COrientations::COrientations");
    m_blocks.resize(blocks.size());

    for (unsigned int block=0; block<blocks.size(); block++)
    {
        /* Build vector of squares for each block */
        std::vector<CSquare> squares;
        for (unsigned int sq=0; sq<blocks[block].m_squares.size(); sq++)
        {
            SqInfo& sq_data = blocks[block].m_squares[sq];
            squares.push_back(CSquare(sq_data.m_row, sq_data.m_col));
        }

        /* Build each block */
        m_blocks[block].Init(squares);
    } /* end of for */
}

