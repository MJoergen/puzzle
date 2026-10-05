#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "initInfo.h"

// Returns the next line that is neither empty nor a comment. At end of file
// the returned stream is in a failed state.
static std::istringstream readLine(std::ifstream& ifs)
{
    std::string line;
    while (true)
    {
        if (!std::getline(ifs, line))
        {
            std::istringstream eof;
            eof.setstate(std::ios::failbit);
            return eof;
        }

        // Skip empty lines
        if (line == "")
            continue;

        // Skip over comments
        if (line[0] == '#')
            continue;
        
        return std::istringstream(line);
    }
} // readLine

bool operator == (const SqInfo& lhs, const SqInfo& rhs)
{
   return lhs.m_row == rhs.m_row && lhs.m_col == rhs.m_col;
}

static bool isSquareInBlock(const BlockInfo& blockInfo, const SqInfo& sqInfo)
{
   return std::find(blockInfo.m_squares.begin(), blockInfo.m_squares.end(), sqInfo) != blockInfo.m_squares.end();
}

static void showBlockInfo(const BlockInfo& blockInfo)
{
   for (int y=0; y<10; ++y)
   {
      for (int x=0; x<10; ++x)
      {
         SqInfo sqInfo = {y, x};
         if (isSquareInBlock(blockInfo, sqInfo))
            std::cout << "X";
         else
            std::cout << ".";
      }
      std::cout << std::endl;
   }
   std::cout << std::endl;
} // end of showBlockInfo

bool InitInfo::ReadFromFile(std::string fileName)
{
    std::ifstream infile(fileName);
    if (!infile)
    {
        std::cerr << "Cannot open file " << fileName << std::endl;
        return false;
    }

    // Read size of board.
    int num_blocks;
    if (!(readLine(infile) >> m_rows) ||
        !(readLine(infile) >> m_cols) ||
        !(readLine(infile) >> num_blocks))  // Read number of blocks.
    {
        std::cerr << fileName << ": Missing board size or number of blocks" << std::endl;
        return false;
    }

    for (int i=0; i<num_blocks; ++i)
    {
        // Read number of squares for this block.
        int num_squares;
        if (!(readLine(infile) >> num_squares))
        {
            std::cerr << fileName << ": Missing size of block " << i << std::endl;
            return false;
        }

        BlockInfo blockInfo;
        for (int j=0; j<num_squares; ++j)
        {
            SqInfo sq;
            if (!(readLine(infile) >> sq.m_row >> sq.m_col))
            {
                std::cerr << fileName << ": Missing square " << j << " of block " << i << std::endl;
                return false;
            }
            blockInfo.m_squares.push_back(sq);
        }

        showBlockInfo(blockInfo);

        m_blocks.push_back(blockInfo);
    }
    return true;
} // ReadFromFile
