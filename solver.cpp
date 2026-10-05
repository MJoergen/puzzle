
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
    BuildSquareIndex();
    ClearBitMapIndex();

    CBitMap bitmap;
    PlaceBitMaps(bitmap, 0);
} // Solve

/**************************************************************************
 **************************************************************************/
void CSolver::BuildSquareIndex()
{
    unsigned int num_squares = m_rows*m_cols;
    m_byLowest.assign(m_bitmaps.Rows(), std::vector< std::vector<int> >(num_squares));
    for (unsigned int block=0; block<m_bitmaps.Rows(); block++)
    {
        for (unsigned int i=0; i<m_bitmaps[block].size(); i++)
        {
            const CBitMap& b = m_bitmaps[block][i];
            m_byLowest[block][b.FirstSetBit()].push_back(i);
        }
    }
} // BuildSquareIndex

/**************************************************************************
 **************************************************************************/
void CSolver::CountNode()
{
    m_stats.m_nodes++;
    if (m_stats.m_nodes == NODES_PER_DOT)
    {
        m_stats.m_nodes = 0;
        m_stats.m_dots++;
        std::cerr << ".";
    }
} // CountNode

/**************************************************************************
 **************************************************************************/
void CSolver::FoundSolution()
{
    std::cerr << "Success! count=" << m_stats.m_solutions << std::endl;
    GenerateBoard();
    std::cout << m_board;
    m_stats.Update(m_board);
    m_stats.m_solutions++;
} // FoundSolution

/**************************************************************************
 * Fill the lowest empty square. Every solution must cover it, so only the
 * fitting placements whose lowest square is that square are tried. This
 * fills the board in order from the top left, which keeps the search tree
 * small, and each step only has a handful of candidates to check.
 **************************************************************************/
void CSolver::PlaceBitMaps(const CBitMap& bitmap, unsigned int num_blocks)
{
    CountNode();

#ifdef STATISTICS
    m_stats.m_examine_tests[num_blocks]++;
#endif

    // If all blocks have been placed and the board is full, then we have
    // solved the puzzle!
    if (num_blocks == m_bitmapIndex.size())
    {
        if (bitmap == m_allBitsSet)
            FoundSolution();
        return;
    }

    // The board is full, but some blocks are left over.
    int sq = bitmap.FirstClearBit();
    if (sq >= m_rows*m_cols)
        return;
    for (unsigned int block = 0; block < m_bitmapIndex.size(); block++)
    {
        if (m_bitmapIndex[block] >= 0)
        {
            // This block has already been placed
            continue;
        }
        const std::vector<CBitMap>& bitmapsForBlock = m_bitmaps[block];
        const std::vector<int>& candidates = m_byLowest[block][sq];
        for (unsigned int c=0; c<candidates.size(); c++)
        {
            const CBitMap& placement = bitmapsForBlock[candidates[c]];
            if (bitmap.AreBitsDistinct(placement))
            {
                m_bitmapIndex[block] = candidates[c];
                CBitMap next = bitmap;
                next |= placement;
                PlaceBitMaps(next, num_blocks+1);
            }
        }
        m_bitmapIndex[block] = -1;
    }
} // PlaceBitMaps

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


