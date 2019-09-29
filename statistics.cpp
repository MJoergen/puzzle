
#include <iostream>
#include <iomanip>

#include "array.h"
#include "statistics.h"

using namespace std;

void CStatistics::Update(const Array<int>& board)
{
    TRACE_FUNCTION("CStatistics::Update");
    int block1, block2;
    Array<int> blockTouchesTemp(num_blocks, num_blocks);

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

    for (unsigned int block1=0; block1<num_blocks; block1++)
    {
        blockTouchesTemp[block1][block1] = 0;
        for (unsigned int block2=0; block2<num_blocks; block2++)
        {
            blockTouches[block1][block2] += blockTouchesTemp[block1][block2];
            if (blockTouchesTemp[block1][block2])
                blockTouchesNonZero[block1][block2]++;
        } /* end of for block2 */
    } /* end of for block1 */

} /* end of Update */

void CStatistics::Clear(void)
{
    TRACE_FUNCTION("CStatistics::Clear");
#ifdef STATISTICS
    for (unsigned int block1=0; block1<num_blocks; block1++)
    {
        examine_tests[block1]    = 0;
        examine_nolegal[block1]  = 0;
        examine_onlymove[block1] = 0;
        examine_cutoffs[block1]  = 0;
        examine_oneblock[block1] = 0;
        examine_recurse[block1]  = 0;
    }
#endif

    blockTouches.Fill(0);
    blockTouchesNonZero.Fill(0);

    solutions = 0;
    nodes = 0;
    dots = 0;

} /* end of Clear */

void CStatistics::StartTimer(void)
{
    starttime = (float)clock()/(float)CLOCKS_PER_SEC;
}

void CStatistics::Print(void) const
{
    cout << "Block connection statistics." << endl;
    cout << "[B1,B2]: count, nonzero" << endl;

#ifdef STATISTICS
    unsigned long num_tests     = 0;
    unsigned long num_nolegal   = 0;
    unsigned long num_onlymove  = 0;
    unsigned long num_cutoffs   = 0;
    unsigned long num_oneblock  = 0;
    unsigned long num_recurse   = 0;
#endif

    for (unsigned int block1=0; block1<num_blocks; block1++)
    {
#ifdef STATISTICS
        printf("Examined tests: %ld\n",   examine_tests[block1]);
        printf("Examined nolegal: %ld\n",  examine_nolegal[block1]);
        printf("Examined onlymove: %ld\n", examine_onlymove[block1]);
        printf("Examined cutoffs: %ld\n",  examine_cutoffs[block1]);
        printf("Examined oneblock: %ld\n", examine_oneblock[block1]);
        printf("Examined recurse: %ld\n",  examine_recurse[block1]);
        num_tests     += examine_tests[block1];
        num_nolegal   += examine_nolegal[block1];
        num_onlymove  += examine_onlymove[block1];
        num_cutoffs   += examine_cutoffs[block1];
        num_oneblock  += examine_oneblock[block1];
        num_recurse   += examine_recurse[block1];
#endif
        for (unsigned int block2=0; block2<num_blocks; block2++)
        {
            cout << "[" << block1 << "," << block2 << "]: " <<
                blockTouches[block1][block2] << " " << 
                blockTouchesNonZero[block1][block2] << endl;
        } /* end of for block2 */
        cout << endl;
    } /* end of for block1 */

    float endtime = (float)clock()/(float)CLOCKS_PER_SEC;
    cout << "A total of " << dots << nodes << " nodes searched." << endl;
#ifdef STATISTICS
    cout << "Number of tests    : " << setw(10) << num_tests << endl;
    cout << "Number of nolegal  : " << setw(10) << num_nolegal << endl;
    cout << "Number of onlymove : " << setw(10) << num_onlymove << endl;
    cout << "Number of cutoffs  : " << setw(10) << num_cutoffs << endl;
    cout << "Number of oneblock : " << setw(10) << num_oneblock << endl;
    cout << "Number of recurse  : " << setw(10) << num_recurse << endl;
#endif
    cout << "A total of " << solutions << " solutions found," << endl;
    cout << "including rotations and reflections." << endl;

    float nodes_pr_sec = (1.0*NODES_PER_DOT*dots + nodes) / (endtime-starttime);

    cout << "Total time used: " << endtime-starttime << endl;
    cout << "Nodes pr second: " << (int) nodes_pr_sec << endl;

} /* end of Print */

