
#ifndef _INIT_H_
#define _INIT_H_

struct SSquare
{
    int row;
    int col;
};

#define MAX_SQUARES_IN_BLOCK 5
struct SBlockInfo
{
    SSquare square_data[MAX_SQUARES_IN_BLOCK];
    int num_squares;
};

#define MAX_BLOCKS 15
struct SInitInfo
{
    int rows;
    int cols;
    int blocks;
    SBlockInfo blockInfo[MAX_BLOCKS];
};

extern SInitInfo init_data;

#endif /* _INIT_H_ */

