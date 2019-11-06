#ifndef _ARRAY_H_
#define _ARRAY_H_

// This class is a wrapper for a two-dimensional array of generic type.

#include <vector>
#include "trace.h"

template <class T>
class Array
{
    private:
        Array();  // Prevent default constructor

    public:
        // Constructor requires dimensions.
        Array(unsigned int rows, unsigned int cols) : m_rows(rows), m_cols(cols)
        {
            m_data.resize(rows);
            for (unsigned int i=0; i<rows; i++)
                m_data[i].resize(cols);
        }

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
        } // Fill

        unsigned int Rows() const { return m_rows; }
        unsigned int Cols() const { return m_cols; }

        // Row access
        typedef std::vector< T > row_type;
        row_type& operator[](unsigned int row)             { return m_data[row];}
        const row_type& operator[](unsigned int row) const { return m_data[row];}

    private:
        std::vector< row_type > m_data;
        unsigned int            m_rows;
        unsigned int            m_cols;
}; // end of class Array

std::ostream& operator<<(std::ostream& os, const Array<int>& board);

#endif /* _ARRAY_H_ */

