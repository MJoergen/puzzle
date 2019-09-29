
#include "bitmap.h"
#include "orientation.h"
#include "statistics.h"

class CSolver
{
public:
    CSolver(const COrientations& orientations, int rows, int cols);
    void Solve();
    void PrintStats();

private:
    void PlaceBitMaps(CBitMap bitmap, unsigned int first_block, unsigned int num_blocks);
    void CreateBitMaps(vector<CBitMap>& bitmaps, const CBlock& block, const CSquare& sq);
    void BuildBitMaps(int in_rows, int in_cols);
    void ClearBitMapIndex(void);
    int GetBitNum(const CSquare& sq) const
    {
        return sq.Row()*m_cols + sq.Col();
    }
    void SetAllBits(CBitMap& bitmap) const;
    void GenerateBoard();
    void ShowBoard() const;

    int                  m_rows;
    int                  m_cols;
    CStatistics          m_stats;
    Array<CBitMap>       m_bitmaps; // Holds bitmaps of all blocks
    const COrientations& m_orientations; // Holds orientations of all blocks
                                         // Only used in BuildBitMaps
    vector< signed short > m_bitmapIndex; // Holds current bitmap used by each block
    Array< int >         m_board;
    CBitMap              m_allBitsSet;

}; /* end of class CSolver */

