
#ifndef _ORIENTATION_H_
#define _ORIENTATION_H_

#include "bitmap.h"
#include "block.h"
#include "init.h"

class COrientations
{
friend ostream& operator<<(ostream& os, const COrientations& orientation);

public:
    COrientations(SBlockInfo block_info_init[], int num_blocks);

    unsigned int NumBlocks(void) const { return blocks.size(); }
    const CBlock& Block(int block) const { return blocks[block]; }

private:
    vector<CBlock> blocks;

}; /* end of COrientations */

#endif /* _ORIENTATION_H_ */

