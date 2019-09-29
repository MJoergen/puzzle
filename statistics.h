
#ifndef _STATISTICS_H_
#define _STATISTICS_H_

#include "trace.h"
#include "array.h"

#define MAX_BLOCKS 15

#define NODES_PER_DOT 10000

class CStatistics
{
    friend class CSolver;
public:
    CStatistics(int num_blocks) :
	num_blocks(num_blocks) ,
	blockTouches(num_blocks, num_blocks) ,
	blockTouchesNonZero(num_blocks, num_blocks)
    {
	TRACE_FUNCTION("CStatistics::CStatistics");
	Clear();
    }

    void Update(const Array<int>& board);
    void Clear(void);
    void StartTimer(void);
    void Print(void) const;

private:

#ifdef STATISTICS
    unsigned long examine_tests[MAX_BLOCKS+1];
    unsigned long examine_nolegal[MAX_BLOCKS+1];
    unsigned long examine_onlymove[MAX_BLOCKS+1];
    unsigned long examine_cutoffs[MAX_BLOCKS+1];
    unsigned long examine_oneblock[MAX_BLOCKS+1];
    unsigned long examine_recurse[MAX_BLOCKS+1];
#endif

    unsigned int num_blocks;

    Array<int> blockTouches;
    Array<int> blockTouchesNonZero;

    unsigned long solutions;
    unsigned long nodes;
    unsigned long dots;

    float starttime;
}; /* end of CStatistics */

#endif /* _STATISTICS_H_ */

