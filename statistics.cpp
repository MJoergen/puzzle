
#include <iostream>
#include <iomanip>

#include "array.h"
#include "statistics.h"

void CStatistics::Update(const Array<int>& board)
{
    TRACE_FUNCTION("CStatistics::Update");
    int block1, block2;
    Array<int> blockTouchesTemp(m_num_blocks, m_num_blocks);

    blockTouchesTemp.Fill(0);

    for (unsigned int row=0; row<board.Rows()-1; row++)
    {
        for (unsigned int col=0; col<board.Cols(); col++)
        {
            block1 = board[row][col];
            block2 = board[row+1][col];
            if (block1 < block2)
                blockTouchesTemp[block1][block2]++;
            else
                blockTouchesTemp[block2][block1]++;
        } /* end of for col */
    } /* end of for row */

    for (unsigned int row=0; row<board.Rows(); row++)
    {
        for (unsigned int col=0; col<board.Cols()-1; col++)
        {
            block1 = board[row][col];
            block2 = board[row][col+1];
            if (block1 < block2)
                blockTouchesTemp[block1][block2]++;
            else
                blockTouchesTemp[block2][block1]++;
        } /* end of for col */
    } /* end of for row */

    for (unsigned int block1=0; block1<m_num_blocks; block1++)
    {
        blockTouchesTemp[block1][block1] = 0;
        for (unsigned int block2=0; block2<m_num_blocks; block2++)
        {
            m_blockTouches[block1][block2] += blockTouchesTemp[block1][block2];
            if (blockTouchesTemp[block1][block2])
                m_blockTouchesNonZero[block1][block2]++;
        } /* end of for block2 */
    } /* end of for block1 */

} /* end of Update */

void CStatistics::Clear(void)
{
    TRACE_FUNCTION("CStatistics::Clear");
#ifdef STATISTICS
    for (unsigned int block1=0; block1<m_num_blocks; block1++)
    {
        m_examine_tests[block1]    = 0;
        m_examine_nolegal[block1]  = 0;
        m_examine_onlymove[block1] = 0;
        m_examine_cutoffs[block1]  = 0;
        m_examine_oneblock[block1] = 0;
        m_examine_recurse[block1]  = 0;
    }
#endif

    m_blockTouches.Fill(0);
    m_blockTouchesNonZero.Fill(0);

    m_solutions = 0;
    m_nodes = 0;
    m_dots = 0;

} /* end of Clear */

void CStatistics::StartTimer(void)
{
    m_starttime = (float)clock()/(float)CLOCKS_PER_SEC;
}

void CStatistics::Print(void) const
{
    std::cout << "Block connection statistics." << std::endl;
    std::cout << "[B1,B2]: count, nonzero" << std::endl;

#ifdef STATISTICS
    unsigned long num_tests     = 0;
    unsigned long num_nolegal   = 0;
    unsigned long num_onlymove  = 0;
    unsigned long num_cutoffs   = 0;
    unsigned long num_oneblock  = 0;
    unsigned long num_recurse   = 0;
#endif

    for (unsigned int block1=0; block1<m_num_blocks; block1++)
    {
#ifdef STATISTICS
        printf("Examined tests: %ld\n",    m_examine_tests[block1]);
        printf("Examined nolegal: %ld\n",  m_examine_nolegal[block1]);
        printf("Examined onlymove: %ld\n", m_examine_onlymove[block1]);
        printf("Examined cutoffs: %ld\n",  m_examine_cutoffs[block1]);
        printf("Examined oneblock: %ld\n", m_examine_oneblock[block1]);
        printf("Examined recurse: %ld\n",  m_examine_recurse[block1]);
        num_tests     += m_examine_tests[block1];
        num_nolegal   += m_examine_nolegal[block1];
        num_onlymove  += m_examine_onlymove[block1];
        num_cutoffs   += m_examine_cutoffs[block1];
        num_oneblock  += m_examine_oneblock[block1];
        num_recurse   += m_examine_recurse[block1];
#endif
        for (unsigned int block2=0; block2<m_num_blocks; block2++)
        {
            std::cout << "[" << block1 << "," << block2 << "]: " <<
                m_blockTouches[block1][block2] << " " << 
                m_blockTouchesNonZero[block1][block2] << std::endl;
        } /* end of for block2 */
        std::cout << std::endl;
    } /* end of for block1 */

    float endtime = (float)clock()/(float)CLOCKS_PER_SEC;
    std::cout << "A total of " << m_dots << m_nodes << " nodes searched." << std::endl;
#ifdef STATISTICS
    std::cout << "Number of tests    : " << std::setw(10) << num_tests << std::endl;
    std::cout << "Number of nolegal  : " << std::setw(10) << num_nolegal << std::endl;
    std::cout << "Number of onlymove : " << std::setw(10) << num_onlymove << std::endl;
    std::cout << "Number of cutoffs  : " << std::setw(10) << num_cutoffs << std::endl;
    std::cout << "Number of oneblock : " << std::setw(10) << num_oneblock << std::endl;
    std::cout << "Number of recurse  : " << std::setw(10) << num_recurse << std::endl;
#endif
    std::cout << "A total of " << m_solutions << " solutions found," << std::endl;
    std::cout << "including rotations and reflections." << std::endl;

    float nodes_pr_sec = (1.0*NODES_PER_DOT*m_dots + m_nodes) / (endtime-m_starttime);

    std::cout << "Total time used: " << endtime-m_starttime << std::endl;
    std::cout << "Nodes pr second: " << (int) nodes_pr_sec << std::endl;

} /* end of Print */

