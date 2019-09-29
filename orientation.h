
#ifndef _ORIENTATION_H_
#define _ORIENTATION_H_

#include "bitmap.h"
#include "block.h"
#include "init.h"

class COrientations
{
    friend std::ostream& operator<<(std::ostream& os, const COrientations& orientation);

    public:
        COrientations(SBlockInfo block_info_init[], int num_blocks);

        unsigned int NumBlocks(void) const { return m_blocks.size(); }
        const CBlock& Block(int block) const { return m_blocks[block]; }

    private:
        std::vector<CBlock> m_blocks;

}; /* end of COrientations */

#endif /* _ORIENTATION_H_ */

