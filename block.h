
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>
#include <ostream>

using namespace std;

/* CSquare */
class CSquare
{
friend ostream& operator<<(ostream& os, const CSquare& sq);

public:
    CSquare(int row=0, int col=0) : row(row), col(col) {}

    CSquare& operator += (const CSquare& sq)
    {
	row += sq.row;
	col += sq.col;
	return *this;
    }

    bool InBounds(int rows, int cols)
    {
	return ((row >= 0) && (row < rows) &&
		(col >= 0) && (col < cols));
    }

    int Row() const {return row;}
    int Col() const {return col;}

private:
    int row;
    int col;
}; /* end of class CSquare */

/* CBlock */
class CBlock
{
friend ostream& operator<<(ostream& os, const CBlock& block);

private:
    static const int orientations=8;
public:
    typedef vector<CSquare> configuration_type;

    CBlock() {configurations.resize(orientations);}

    void Init(const vector<CSquare>& squares);

    int NumSquares(void) const { return num_squares; }
    int NumOrientations(void) const { return configurations.size(); }
    const configuration_type& Configuration(int orientation) const
        { return configurations[orientation]; }
    void Show(void) const;
    
private:
    int num_squares;
    vector< vector<CSquare> > configurations;
}; /* end of CBlock */

#endif /* _BLOCK_H_ */

