
#include "block.h"
#include "trace.h"

std::ostream& operator<<(std::ostream& os, const CSquare& sq)
{
    return os << "(" << sq.m_row << ", " << sq.m_col << ")";
}

void CBlock::Init(const std::vector<CSquare>& squares)
{
    TRACE_FUNCTION("CBlock::Init");
    TRACE( "CBlock::Init.  squares.size()=" << squares.size() << std::endl);

    m_num_squares = squares.size();

    for (unsigned int orientation=0; orientation<m_configurations.size(); orientation++)
    {
        m_configurations[orientation].resize(squares.size());
    }

    for (unsigned int sq_num=0; sq_num<squares.size(); sq_num++)
    {
        int sqrow = squares[sq_num].Row();
        int sqcol = squares[sq_num].Col();

        m_configurations[0][sq_num] = CSquare(sqrow, sqcol);
        m_configurations[1][sq_num] = CSquare(sqrow, -sqcol);
        m_configurations[2][sq_num] = CSquare(sqcol, sqrow);
        m_configurations[3][sq_num] = CSquare(sqcol, -sqrow);
        m_configurations[4][sq_num] = CSquare(-sqcol, sqrow);
        m_configurations[5][sq_num] = CSquare(-sqcol, -sqrow);
        m_configurations[6][sq_num] = CSquare(-sqrow, sqcol);
        m_configurations[7][sq_num] = CSquare(-sqrow, -sqcol);
    }
} /* end of Init */

std::ostream& operator<<(std::ostream& os, const CBlock& block)
{
    for (unsigned int orientation=0; orientation<block.m_configurations.size(); orientation++)
    {
        os << "orientation: " << orientation << std::endl;
        for (unsigned int elem=0; elem<block.m_configurations[orientation].size(); elem++)
        {
            os << block.m_configurations[orientation][elem] << " ";
        } /* end of for element */
        os << std::endl;
    } /* end of for orientation */

    return os;
} /* end of Show */

