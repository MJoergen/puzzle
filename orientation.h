
#ifndef _ORIENTATION_H_
#define _ORIENTATION_H_

#include "bitmap.h"
#include "block.h"
#include "initInfo.h"

class COrientations
{
    friend std::ostream& operator<<(std::ostream& os, const COrientations& orientation);

    public:
        COrientations(std::vector<BlockInfo> blocks);

        unsigned int NumBlocks(void) const { return m_blocks.size(); }
        const CBlock& Block(int block) const { return m_blocks[block]; }

    private:
        std::vector<CBlock> m_blocks;

}; /* end of COrientations */

#endif /* _ORIENTATION_H_ */

