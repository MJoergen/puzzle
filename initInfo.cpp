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

        m_blocks.push_back(blockInfo);
    }
} // ReadFromFile

