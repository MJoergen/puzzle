#ifndef _ARRAY_H_
#define _ARRAY_H_

#include "trace.h"
#include <vector>

using namespace std;

template <class T>
class Array
{
private:
    Array();
public:
    Array(int rows, int cols) : rows(rows), cols(cols)
    {
	Resize(rows, cols);
    }
    typedef vector< T > row_type;
private:
    void Resize(unsigned int new_rows, unsigned int new_cols)
    {
	rows = new_rows;
	cols = new_cols;

	data.resize(rows);
	for (unsigned int i=0; i<rows; i++)
	    data[i].resize(cols);
    }
public:
    void Fill(T val)
    {
	TRACE_FUNCTION("Array::Fill");
	for (unsigned int i=0; i<data.size(); i++)
	{
	    for (unsigned int j=0; j<data[i].size(); j++)
	    {
		data[i][j] = val;
	    }
	}
    }
    unsigned int Rows() const { return rows; }
    unsigned int Cols() const { return cols; }
    row_type& operator[](unsigned int row) { return data[row];}
    const row_type& operator[](unsigned int row) const { return data[row];}

private:
    vector< row_type > data;
    unsigned int rows;
    unsigned int cols;
}; /* end of class Array */

ostream& operator<<(ostream& os, const Array<int>& board);

#endif /* _ARRAY_H_ */

