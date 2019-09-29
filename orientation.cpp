
#include "orientation.h"
#include "trace.h"

/**************************************************************************
 **************************************************************************/
ostream& operator<<(ostream& os, const COrientations& orientation)
{
    for (unsigned int block=0; block<orientation.blocks.size(); block++)
    {
        os << "Block number " << block << ":" << endl;
        os << orientation.blocks[block] << endl;
    } /* end of for */
    return os;
}

/**************************************************************************
 **************************************************************************/
COrientations::COrientations(SBlockInfo block_info_init[], int num_blocks)
{
    TRACE_FUNCTION("COrientations::COrientations");
    blocks.resize(num_blocks);

    for (int block=0; block<num_blocks; block++)
    {
	/* Build vector of squares for each block */
	vector<CSquare> squares;
	for (int sq=0; sq<block_info_init[block].num_squares; sq++)
	{
	    SSquare& sq_data = block_info_init[block].square_data[sq];
	    squares.push_back(CSquare(sq_data.row, sq_data.col));
	}

	/* Build each block */
	blocks[block].Init(squares);
    } /* end of for */
}

