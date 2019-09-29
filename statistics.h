
#ifndef _STATISTICS_H_
#define _STATISTICS_H_

#include "trace.h"
#include "array.h"

#define MAX_BLOCKS 15

#define NODES_PER_DOT 10000

class CStatistics
{
    friend class CSolver;    // This is a dirty hack!

    public:
        CStatistics(int num_blocks) :
            m_num_blocks(num_blocks) ,
            m_blockTouches(num_blocks, num_blocks) ,
            m_blockTouchesNonZero(num_blocks, num_blocks)
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
        unsigned long m_examine_tests[MAX_BLOCKS+1];
        unsigned long m_examine_nolegal[MAX_BLOCKS+1];
        unsigned long m_examine_onlymove[MAX_BLOCKS+1];
        unsigned long m_examine_cutoffs[MAX_BLOCKS+1];
        unsigned long m_examine_oneblock[MAX_BLOCKS+1];
        unsigned long m_examine_recurse[MAX_BLOCKS+1];
#endif

        unsigned int m_num_blocks;

        Array<int> m_blockTouches;
        Array<int> m_blockTouchesNonZero;

        unsigned long m_solutions;
        unsigned long m_nodes;
        unsigned long m_dots;

        float m_starttime;
}; /* end of CStatistics */

#endif /* _STATISTICS_H_ */

