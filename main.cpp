#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <iostream>

#include "orientation.h"
#include "statistics.h"
#include "initInfo.h"
#include "solver.h"

#define NO_DEBUG_LEVEL 16

int wait(void)
{
#ifdef DEBUG_LEVEL
    int ch;

    fprintf(stderr, "Press any key to continue, 'q' to quit.\n");
    ch = fgetc(stdin);
    ch = toupper(ch);

    return (ch != 'Q');
#else
    return 1;
#endif
} /* end of wait */

#define NODES_PER_DOT 10000


int main(int argc, char **argv)
{
    TRACE_FUNCTION("::main");

    setbuf(stdout, NULL);

    InitInfo initInfo;

    std::string fileName("8x8.txt");
    if (argc > 1)
    {
        fileName = argv[1];
    }
    if (!initInfo.ReadFromFile(fileName))
        return 1;

    if (initInfo.m_rows * initInfo.m_cols > CBitMap::MaxBits)
    {
        std::cerr << "Board has " << initInfo.m_rows * initInfo.m_cols
                  << " squares, but this build supports at most " << CBitMap::MaxBits
                  << ". Rebuild with: make clean; make BITMAP_BITS=256" << std::endl;
        return 1;
    }

    if (initInfo.m_blocks.size() > MAX_BLOCKS)
    {
        std::cerr << "At most " << MAX_BLOCKS << " blocks are supported." << std::endl;
        return 1;
    }

    const COrientations orientations(initInfo.m_blocks);

    std::cout << "All the orientations used:" << std::endl << orientations;
    if (!wait()) return 1;

    CSolver solver(orientations, initInfo.m_rows, initInfo.m_cols);

    std::cout << std::endl;
    if (!wait()) return 1;

    std::cerr << NODES_PER_DOT << " nodes per dot." << std::endl;

    solver.Solve();

    (void) wait();

    solver.PrintStats();

    (void) wait();

    return 0;
} /* end of main */

