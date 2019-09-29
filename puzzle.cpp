#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <iostream>

#include "orientation.h"
#include "statistics.h"
#include "init.h"
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


int main(void)
{
    TRACE_FUNCTION("::main");

    setbuf(stdout, NULL);

    const COrientations orientations(init_data.blockInfo, init_data.blocks);

    std::cout << "All the orientations used:" << std::endl << orientations;
    if (!wait()) return 1;

    CSolver solver(orientations, init_data.rows, init_data.cols);

    std::cout << std::endl;
    if (!wait()) return 1;

    std::cerr << NODES_PER_DOT << " nodes per dot." << std::endl;

    solver.Solve();

    (void) wait();

    solver.PrintStats();

    (void) wait();

    return 0;
} /* end of main */

