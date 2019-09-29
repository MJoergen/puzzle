#ifndef _ARRAY_H_
#define _ARRAY_H_

// This class is a wrapper for a two-dimensional array.

#include "trace.h"
#include <vector>

template <class T>
class Array
{
    public:
        Array(int rows, int cols) : m_rows(rows), m_cols(cols)
        {
            Resize(rows, cols);
        }
        typedef std::vector< T > row_type;

        void Fill(T val)
        {
            TRACE_FUNCTION("Array::Fill");
            for (unsigned int i=0; i<m_data.size(); i++)
            {
                for (unsigned int j=0; j<m_data[i].size(); j++)
                {
                    m_data[i][j] = val;
                }
            }
        }
        unsigned int Rows() const { return m_rows; }
        unsigned int Cols() const { return m_cols; }
        row_type& operator[](unsigned int row) { return m_data[row];}
        const row_type& operator[](unsigned int row) const { return m_data[row];}

    private:
        Array();

    private:
        void Resize(unsigned int new_rows, unsigned int new_cols)
        {
            m_rows = new_rows;
            m_cols = new_cols;

            m_data.resize(m_rows);
            for (unsigned int i=0; i<m_rows; i++)
                m_data[i].resize(m_cols);
        }

    private:
        std::vector< row_type > m_data;
        unsigned int m_rows;
        unsigned int m_cols;
}; /* end of class Array */

std::ostream& operator<<(std::ostream& os, const Array<int>& board);

#endif /* _ARRAY_H_ */

