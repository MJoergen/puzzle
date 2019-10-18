#ifndef _BLOCK_H_
#define _BLOCK_H_

// The class CBlock is used to contain all possible orientations of a specific
// block.  The contentes of the class are only set in the Init() call, and are
// otherwise only inspected, and never updated.

#include <vector>
#include <ostream>

class CSquare
{
    friend std::ostream& operator<<(std::ostream& os, const CSquare& sq);

    public:
        // Constructor
        CSquare(int row=0, int col=0) : m_row(row), m_col(col) {}

        // Modifiers
        CSquare& operator += (const CSquare& sq)
        {
            m_row += sq.m_row;
            m_col += sq.m_col;
            return *this;
        }

        // Inspectors
        bool InBounds(int rows, int cols) const
        {
            return ((m_row >= 0) && (m_row < rows) &&
                    (m_col >= 0) && (m_col < cols));
        }

        int Row() const {return m_row;}
        int Col() const {return m_col;}

    private:
        // The member variables m_row and m_col must be signed integers,
        // because they indicate relative distance on the board.
        int m_row;
        int m_col;
}; // end of class CSquare


class CBlock
{
    friend std::ostream& operator<<(std::ostream& os, const CBlock& block);

    public:
        // Constructor
        CBlock() {m_configurations.resize(m_orientations);}

        // Modifiers
        void Init(const std::vector<CSquare>& squares);

        // Inspectors
        unsigned int NumSquares(void) const      { return m_num_squares; }
        unsigned int NumOrientations(void) const { return m_configurations.size(); }

        typedef std::vector<CSquare> configuration_type;
        const configuration_type& Configuration(int orientation) const
        {
           return m_configurations[orientation];
        }

    private:
        unsigned int                      m_num_squares;
        std::vector< configuration_type > m_configurations;

        static const int m_orientations=8;
}; // end of CBlock

#endif /* _BLOCK_H_ */

