#pragma once

#include <vector>
#include <string>

struct SqInfo
{
    int m_row;
    int m_col;
}; // SqInfo

struct BlockInfo
{
    std::vector<SqInfo> m_squares;
}; // BlockInfo

struct InitInfo
{
    void ReadFromFile(std::string fileName);

    int m_rows;
    int m_cols;
    std::vector<BlockInfo> m_blocks;
}; // InitInfo

