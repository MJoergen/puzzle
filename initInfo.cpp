#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "initInfo.h"

static std::istringstream readLine(std::ifstream& ifs)
{
    std::string line;
    while (true)
    {
        std::getline(ifs, line);
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

void InitInfo::ReadFromFile(std::string fileName)
{
    std::ifstream infile(fileName);

    // Read size of board.
    readLine(infile) >> m_rows;
    readLine(infile) >> m_cols;

    // Read number of blocks.
    int num_blocks;
    readLine(infile) >> num_blocks;

    for (int i=0; i<num_blocks; ++i)
    {
        // Read number of squares for this block.
        int num_squares;
        readLine(infile) >> num_squares;

        BlockInfo blockInfo;
        for (int j=0; j<num_squares; ++j)
        {
            SqInfo sq;
            readLine(infile) >> sq.m_row >> sq.m_col;
            blockInfo.m_squares.push_back(sq);
        }

        showBlockInfo(blockInfo);

        m_blocks.push_back(blockInfo);
    }
} // ReadFromFile

