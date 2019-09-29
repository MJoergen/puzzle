
#include "block.h"
#include "trace.h"

ostream& operator<<(ostream& os, const CSquare& sq)
{
    return os << "(" << sq.row << ", " << sq.col << ")";
}

void CBlock::Init(const vector<CSquare>& squares)
{
    TRACE_FUNCTION("CBlock::Init");
    TRACE( "CBlock::Init.  squares.size()=" << squares.size() << endl);

    num_squares = squares.size();

    for (unsigned int orientation=0; orientation<configurations.size(); orientation++)
    {
	configurations[orientation].resize(squares.size());
    }

    for (unsigned int sq_num=0; sq_num<squares.size(); sq_num++)
    {
	int sqrow = squares[sq_num].Row();
	int sqcol = squares[sq_num].Col();

	configurations[0][sq_num] = CSquare(sqrow, sqcol);
	configurations[1][sq_num] = CSquare(sqrow, -sqcol);
	configurations[2][sq_num] = CSquare(sqcol, sqrow);
	configurations[3][sq_num] = CSquare(sqcol, -sqrow);
	configurations[4][sq_num] = CSquare(-sqcol, sqrow);
	configurations[5][sq_num] = CSquare(-sqcol, -sqrow);
	configurations[6][sq_num] = CSquare(-sqrow, sqcol);
	configurations[7][sq_num] = CSquare(-sqrow, -sqcol);
    }
} /* end of Init */

ostream& operator<<(ostream& os, const CBlock& block)
{
    for (unsigned int orientation=0; orientation<block.configurations.size(); orientation++)
    {
	os << "orientation: " << orientation << endl;
	for (unsigned int elem=0; elem<block.configurations[orientation].size(); elem++)
	{
	    os << block.configurations[orientation][elem] << " ";
	} /* end of for element */
	os << endl;
    } /* end of for orientation */

    return os;
} /* end of Show */

