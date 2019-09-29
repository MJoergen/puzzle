
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>
#include <ostream>

/* CSquare */
class CSquare
{
    friend std::ostream& operator<<(std::ostream& os, const CSquare& sq);

    public:
        CSquare(int row=0, int col=0) : m_row(row), m_col(col) {}

        CSquare& operator += (const CSquare& sq)
        {
            m_row += sq.m_row;
            m_col += sq.m_col;
            return *this;
        }

        bool InBounds(int rows, int cols)
        {
            return ((m_row >= 0) && (m_row < rows) &&
                    (m_col >= 0) && (m_col < cols));
        }

        int Row() const {return m_row;}
        int Col() const {return m_col;}

    private:
        int m_row;
        int m_col;
}; /* end of class CSquare */

/* CBlock */
class CBlock
{
    friend std::ostream& operator<<(std::ostream& os, const CBlock& block);

    public:
        typedef std::vector<CSquare> configuration_type;

        CBlock() {m_configurations.resize(m_orientations);}

        void Init(const std::vector<CSquare>& squares);

        int NumSquares(void) const { return m_num_squares; }
        int NumOrientations(void) const { return m_configurations.size(); }
        const configuration_type& Configuration(int orientation) const
            { return m_configurations[orientation]; }
        void Show(void) const;

    private:
        int m_num_squares;
        std::vector< std::vector<CSquare> > m_configurations;

        static const int m_orientations=8;
}; /* end of CBlock */

#endif /* _BLOCK_H_ */

