
#include "solver.h"
#include "trace.h"
#include <iostream>
#include <stdlib.h>
#include <iomanip>

/**************************************************************************
 **************************************************************************/
CSolver::CSolver(const COrientations& orientations, int rows, int cols) :
    m_rows(rows) ,
    m_cols(cols) ,
    m_stats(orientations.NumBlocks()) ,
    m_bitmaps(orientations.NumBlocks(), 0) ,
    m_orientations(orientations) ,
    m_board(rows, cols)
{
    TRACE_FUNCTION("CSolver::CSolver");
    m_bitmapIndex.resize(orientations.NumBlocks());
} // CSolver

/**************************************************************************
 **************************************************************************/
void CSolver::Solve()
{
    TRACE_FUNCTION("CSolver::Solve");

    m_stats.StartTimer();

    SetAllBits(m_allBitsSet);
    BuildBitMaps(m_rows, m_cols);
    ClearBitMapIndex();

    CBitMap bitmap;
    PlaceBitMaps(bitmap, 0, 0);
} // Solve

/**************************************************************************
 **************************************************************************/
void CSolver::SetAllBits(CBitMap& bitmap) const
{
    TRACE_FUNCTION("CSolver::SetAllBits");
    for (int row=0; row<m_rows; row++)
    {
        for (int col=0; col<m_cols; col++)
        {
            bitmap.SetBit(GetBitNum(CSquare(row, col)));
        } /* end of for col */
    } /* end of for row */
} // SetAllBits

/**************************************************************************
 **************************************************************************/
void CSolver::ClearBitMapIndex(void)
{
    TRACE_FUNCTION("CSolver::ClearBitMapIndex");
    for (unsigned int block=0; block<m_bitmapIndex.size(); block++)
        m_bitmapIndex[block] = -1;
} // ClearBitMapIndex

/**************************************************************************
 **************************************************************************/
void CSolver::PrintStats()
{
    TRACE_FUNCTION("CSolver::PrintStats");
    m_stats.Print();
} // PrintStats

/**************************************************************************
 **************************************************************************/
void CSolver::CreateBitMaps(std::vector<CBitMap>& bitmaps, const CBlock& block, const CSquare& offset)
{
    TRACE_FUNCTION("CSolver::CreateBitMaps");
    for (unsigned int orientation=0; orientation<block.NumOrientations(); orientation++)
    {
        const CBlock::configuration_type& configuration = block.Configuration(orientation);
        CBitMap tempBitmap; 

        bool ok = true;
        for (unsigned int sq_num=0; sq_num<configuration.size(); sq_num++)
        {
            CSquare newSq(configuration[sq_num]);
            newSq += offset;

            if (!newSq.InBounds(m_rows, m_cols))
            {
                ok = false;
                break;
            }

            tempBitmap.SetBit(GetBitNum(newSq));
        }; /* end of for element */

        if (ok)
        {
            TRACE( "Adding bitmap " << tempBitmap << ", row " << offset.Row() << ", col "
                    << offset.Col() << ", orientation " << orientation << std::endl);
            for (unsigned int bitmap_num=0; bitmap_num<bitmaps.size(); bitmap_num++)
            {
                if (bitmaps[bitmap_num] == tempBitmap)
                {
                    TRACE( "Skipped due to repetitions." << std::endl);
                    ok = false;
                    break;
                }
            } /* end of for */
        }; /* end of if */

        if (ok)
        {
            bitmaps.push_back(tempBitmap);
        }
    }
} // CreateBitMaps

/**************************************************************************
 **************************************************************************/
void CSolver::BuildBitMaps(int in_rows, int in_cols)
{
    TRACE_FUNCTION("CSolver::BuildBitMaps");
    m_rows = in_rows;
    m_cols = in_cols;

    for (unsigned int block_no=0; block_no<m_orientations.NumBlocks(); block_no++)
    {
        m_bitmaps[block_no].resize(0);
        std::cout << "Considering block " << block_no << std::endl;
        TRACE( "Considering block " << block_no << std::endl);
        for (int row=0; row<m_rows; row++)
        {
            for (int col=0; col<m_cols; col++)
            {
                CreateBitMaps(m_bitmaps[block_no], m_orientations.Block(block_no), CSquare(row, col));
            }; /* end of for col */
        }; /* end of for row */

        std::cout << "Total of " << m_bitmaps[block_no].size() << " bitmaps." << std::endl;
        TRACE( "Total of " << m_bitmaps[block_no].size() << " bitmaps." << std::endl);
    }
} // BuildBitMaps

/**************************************************************************
 **************************************************************************/
void CSolver::GenerateBoard()
{
    TRACE_FUNCTION("CSolver::GenerateBoard");
    for (int row=0; row<m_rows; row++)
    {
        for (int col=0; col<m_cols; col++)
        {
            int bitNum = GetBitNum(CSquare(row, col));

            // Find which block occupies this square
            m_board[row][col] = -1;
            unsigned int block;
            for (block=0; block<m_bitmapIndex.size(); block++)
            {
                if (m_bitmapIndex[block] < 0)
                    continue;
                const CBitMap& bitmap = m_bitmaps[block][m_bitmapIndex[block]];
                if (bitmap.IsBitSet(bitNum))
                {
                    m_board[row][col] = block;
                    break;
                }
            } /* end of for block */
        } /* end of for col */
    } /* end of for row */
} // GenerateBoard

/**************************************************************************
 **************************************************************************/
void CSolver::PlaceBitMaps(CBitMap bitmap, unsigned int first_block, unsigned int num_blocks)
{
    TRACE_FUNCTION("CSolver::PlaceBitMaps");

    TRACE( "bitmap = " << bitmap << ", first_block=" << first_block << std::endl);

    m_stats.m_nodes++;
    if (m_stats.m_nodes == NODES_PER_DOT)
    {
        m_stats.m_nodes = 0;
        m_stats.m_dots++;
        std::cerr << ".";
    }

    //    GenerateBoard();
    //    TRACE( board << std::endl);

#ifdef DEBUG_LEVEL
    if (num_blocks < DEBUG_LEVEL)
    {
        if (!wait()) return;
    } /* end of if */
#endif

#ifdef STATISTICS
    m_stats.m_examine_tests[num_blocks]++;
#endif

    unsigned int block_temp;

    // For all remaining blocks, find out how many legal places it may go.
    // Keep a record of which squares can be occupied too.
    CBitMap bitmapTemp = bitmap;
    CBitMap bitmapTemp2 = bitmap;
    for (block_temp = first_block; block_temp < m_bitmapIndex.size(); block_temp++)
    {
        if (m_bitmapIndex[block_temp] >= 0)
        {
            // This block has already been placed
            continue;
        }
        const std::vector<CBitMap>& bitmapsForBlock = m_bitmaps[block_temp];

        int found = 0;
        unsigned int lastIndex = 0;
        for (unsigned int i=0; i<bitmapsForBlock.size(); i++)
        {
            if (bitmap.AreBitsDistinct(bitmapsForBlock[i]))
            {
                bitmapTemp2 |= (bitmapTemp & bitmapsForBlock[i]);
                bitmapTemp |= bitmapsForBlock[i];
                found++;
                lastIndex = i;
            } /* end of if */
        } /* end of for */
        TRACE( "Block " << block_temp << " has " << found << " legal moves." << std::endl);

        // If a block has no legal places, then abort immediately.
        if (!found)
        {
#ifdef STATISTICS
            m_stats.m_examine_nolegal[num_blocks]++;
#endif
            TRACE( "Discarded." << std::endl);
            return;
        }

        // If a block has only one place to go, then place it immediately, and return.
        if (found == 1)
        {
#ifdef STATISTICS
            m_stats.m_examine_onlymove[num_blocks]++;
#endif
            if (first_block == block_temp)
                first_block++;

            TRACE( "Playing block immediately, using bitmap " << lastIndex << 
                    " " << bitmapsForBlock[lastIndex] << std::endl);
            m_bitmapIndex[block_temp] = lastIndex;
            bitmap |= bitmapsForBlock[lastIndex];
            PlaceBitMaps(bitmap, first_block, num_blocks+1);
            m_bitmapIndex[block_temp] = -1;
            return;
        }
    } /* end of for */

    // If some squares can not be occupied, then abort immediately.
    if (!(bitmapTemp == m_allBitsSet))
    {
#ifdef STATISTICS
        m_stats.m_examine_cutoffs[num_blocks]++;
#endif
        TRACE( "Discarded because board could not be filled completely." << std::endl);
        return;
    } /* end of if */


    // If a square can only be occupied by *one* block/orientation,
    // then place that immediately, and return.
    if (!(bitmapTemp2 == m_allBitsSet))
    {
#ifdef STATISTICS
        m_stats.m_examine_oneblock[num_blocks]++;
#endif
        TRACE( "bitmapTemp2=" << bitmapTemp2 << std::endl);
        TRACE( "Some squares can only be covered by a single block." << std::endl);
        CBitMap singleSquareBits(~bitmapTemp2);

        // Now we search for the bitmap that covers any of the bits
        for (block_temp = first_block; block_temp < m_bitmapIndex.size(); block_temp++)
        {
            if (m_bitmapIndex[block_temp] >= 0)
            {
                // This block has already been placed
                continue;
            }
            const std::vector<CBitMap>& bitmapsForBlock = m_bitmaps[block_temp];

            for (unsigned int i=0; i<bitmapsForBlock.size(); i++)
            {
                if (!singleSquareBits.AreBitsDistinct(bitmapsForBlock[i]) &&
                        bitmap.AreBitsDistinct(bitmapsForBlock[i]) )
                {
                    TRACE( "Found block " << block_temp << ", bitmap " << i << std::endl);
                    if (first_block == block_temp)
                        first_block++;

                    m_bitmapIndex[block_temp] = i;
                    bitmap |= bitmapsForBlock[i];
                    PlaceBitMaps(bitmap, first_block, num_blocks+1);
                    m_bitmapIndex[block_temp] = -1;
                    return;
                }
            }
        }
        TRACE( "ERROR" << std::endl);
        exit(1); // Shouldn't reach here
    } /* end of if */

    // If all blocks have been placed, then we have solved the puzzle!
    if (num_blocks==m_bitmapIndex.size())
    {
        std::cerr << "Success! count=" << m_stats.m_solutions << ", nodes=" << m_stats.m_nodes << 
            ", dots=" << m_stats.m_dots <<
            ", completed " << (m_bitmapIndex[0]*100)/m_bitmaps[0].size() << "%" << std::endl;
        GenerateBoard();
        std::cout << m_board;
        m_stats.Update(m_board);
        m_stats.m_solutions++;
        return;
    }

#ifdef STATISTICS
    m_stats.m_examine_recurse[num_blocks]++;
#endif

    // Now we search for the next block to place
    for (block_temp = first_block; block_temp < m_bitmapIndex.size(); block_temp++)
    {
        if (m_bitmapIndex[block_temp] < 0)
        {
            // OK. Found a block that has not yet been placed.
            break;
        }
    }

    first_block = block_temp+1;

    // Now place this block and recursively call the same function again, to
    // place the remaining blocks.
    TRACE( "Searching next level with block " << block_temp << std::endl);
    const std::vector<CBitMap>& bitmapsForBlock = m_bitmaps[block_temp];
    for (unsigned int i=0; i<bitmapsForBlock.size(); i++)
    {
        if (bitmap.AreBitsDistinct(bitmapsForBlock[i]))
        {
            TRACE( "Using bitmap " << i << " " << bitmapsForBlock[i] << std::endl);
            m_bitmapIndex[block_temp] = i;

            bitmapTemp = bitmap;
            bitmapTemp |= bitmapsForBlock[i];
            PlaceBitMaps(bitmapTemp, first_block, num_blocks+1);
        }
    } /* end of for */
    m_bitmapIndex[block_temp] = -1;

} // PlaceBitMaps

