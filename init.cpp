
#include "init.h"

/*

   O		PLUS	0
  OOO
   O

  OO		SQ	    1
  OO

  OOOOO		BAR	    2

  OO		M	    3
   OO
    O

  O		    Z	    4
  OOO
    O

  OOO		L	    5
    O
    O

    O		T	    6
  OOO
    O

  OOO		U	    7
  O O

  OOOO		HOOK	8
     O

  OOO		FLASH	9
    OO

  OOOO		TRIP	10
    O

    O		TWID	11
  OOO
   O

  OOO		BOX	    12
   OO

*/

#define BLOCK_PLUS	{{{1,0}, {1,1}, {1,2}, {0,1}, {2,1}}, 5}
#define BLOCK_SQ	{{{0,0}, {0,1}, {1,1}, {1,0}}, 4}
#define BLOCK_BAR	{{{0,0}, {1,0}, {2,0}, {3,0}, {4,0}}, 5}
#define BLOCK_M		{{{1,0}, {1,1}, {0,1}, {0,2}, {2,0}}, 5}
#define BLOCK_Z		{{{0,0}, {0,1}, {1,1}, {2,1}, {2,2}}, 5}
#define BLOCK_L		{{{2,0}, {2,1}, {2,2}, {1,2}, {0,2}}, 5}
#define BLOCK_T		{{{1,0}, {1,1}, {1,2}, {0,2}, {2,2}}, 5}
#define BLOCK_U		{{{0,0}, {1,0}, {2,0}, {2,1}, {0,1}}, 5}
#define BLOCK_HOOK	{{{0,0}, {0,1}, {0,2}, {0,3}, {1,3}}, 5}
#define BLOCK_FLASH	{{{0,0}, {1,0}, {2,0}, {2,1}, {3,1}}, 5}
#define BLOCK_TRIP	{{{0,0}, {0,1}, {0,2}, {0,3}, {1,2}}, 5}
#define BLOCK_TWID	{{{0,1}, {1,1}, {1,2}, {1,0}, {2,0}}, 5}
#define BLOCK_BOX	{{{0,0}, {1,0}, {0,1}, {1,1}, {0,2}}, 5}

#define BLOCK_1	{{{0,0}, {2,0}}, 2}
#define BLOCK_2	{{{0,0}, {3,0}}, 2}
#define BLOCK_3	{{{0,0}, {4,0}}, 2}
#define BLOCK_4	{{{0,0}, {5,0}}, 2}
#define BLOCK_5	{{{0,0}, {6,0}}, 2}
#define BLOCK_6	{{{0,0}, {7,0}}, 2}
#define BLOCK_7	{{{0,0}, {8,0}}, 2}
#define BLOCK_8	{{{0,0}, {9,0}}, 2}

#define BLOCK_1a	{{{0,0},  {2,0},  {4,0}}, 3}
#define BLOCK_2a	{{{0,0},  {3,0},  {6,0}}, 3}
#define BLOCK_3a	{{{0,0},  {4,0},  {8,0}}, 3}
#define BLOCK_4a	{{{0,0},  {5,0}, {10,0}}, 3}
#define BLOCK_5a	{{{0,0},  {6,0}, {12,0}}, 3}
#define BLOCK_6a	{{{0,0},  {7,0}, {14,0}}, 3}
#define BLOCK_7a	{{{0,0},  {8,0}, {16,0}}, 3}
#define BLOCK_8a	{{{0,0},  {9,0}, {18,0}}, 3}
#define BLOCK_9a	{{{0,0}, {10,0}, {20,0}}, 3}

// 300 solutions
#define GAME_1x16 { 1, 16, 8, \
  { BLOCK_1, BLOCK_2, BLOCK_3, BLOCK_4, \
    BLOCK_5, BLOCK_6, BLOCK_7, BLOCK_8 } };

// 6 solutions
#define GAME_1x27 { 1, 27, 9, \
  { BLOCK_1a, BLOCK_2a, BLOCK_3a, BLOCK_4a, \
    BLOCK_5a, BLOCK_6a, BLOCK_7a, BLOCK_8a, BLOCK_9a } };

// 8 solutions
#define GAME_4x5 { 4, 5, 4, \
  { BLOCK_HOOK, BLOCK_FLASH, BLOCK_Z, BLOCK_L } };

// 8 solutions
#define GAME_5x5 { 5, 5, 5, \
  { BLOCK_M, BLOCK_Z, BLOCK_L, BLOCK_TRIP, BLOCK_BOX } };

// 32 solutions
#define GAME_8x5 { 8, 5, 8, \
  { BLOCK_T, BLOCK_FLASH, BLOCK_U, BLOCK_Z, BLOCK_L, BLOCK_TRIP, \
    BLOCK_M, BLOCK_BOX } };

// 168 solutions
#define GAME_9x5 { 9, 5, 9, \
  { BLOCK_BAR, BLOCK_T, BLOCK_FLASH, BLOCK_U, BLOCK_Z, BLOCK_L, \
    BLOCK_TRIP, BLOCK_M, BLOCK_BOX } };

// 160 solutions
#define GAME_7x7a { 7, 7, 10, \
  { BLOCK_PLUS, BLOCK_SQ, BLOCK_BAR, BLOCK_M, BLOCK_Z, BLOCK_L, \
    BLOCK_HOOK, BLOCK_FLASH, BLOCK_TWID, BLOCK_BOX } };

// 160 solutions found in 15 seconds (on 64-bit) or 27 seconds (on 32-bit).
#define GAME_7x7b { 7, 7, 10, \
  { BLOCK_BAR, BLOCK_HOOK, BLOCK_BOX, BLOCK_TWID, BLOCK_L, BLOCK_Z, \
    BLOCK_SQ, BLOCK_PLUS, BLOCK_FLASH, BLOCK_M } };

// 160 solutions
#define GAME_7x7c { 7, 7, 10, \
  { BLOCK_PLUS, BLOCK_SQ, BLOCK_BAR, BLOCK_M, BLOCK_Z, BLOCK_L, \
    BLOCK_HOOK, BLOCK_FLASH, BLOCK_TWID, BLOCK_BOX } };

// 9356 solutions
#define GAME_6x10 { 6, 10, 12, \
  { BLOCK_PLUS, BLOCK_BAR, BLOCK_M, BLOCK_Z, BLOCK_L, BLOCK_T, BLOCK_U, \
    BLOCK_HOOK, BLOCK_FLASH, BLOCK_TRIP, BLOCK_TWID, BLOCK_BOX } };

// 4040 solutions
#define GAME_5x12 { 5, 12, 12, \
  { BLOCK_PLUS, BLOCK_BAR, BLOCK_M, BLOCK_Z, BLOCK_L, BLOCK_T, BLOCK_U, \
    BLOCK_HOOK, BLOCK_FLASH, BLOCK_TRIP, BLOCK_TWID, BLOCK_BOX } };

// 129168 solutions found in 34 minutes
#define GAME_8x8 { 8, 8, 13, \
  { BLOCK_PLUS, BLOCK_SQ, BLOCK_BAR, BLOCK_M, BLOCK_Z, BLOCK_L, BLOCK_T, \
    BLOCK_U, BLOCK_HOOK, BLOCK_FLASH, BLOCK_TRIP, BLOCK_TWID, BLOCK_BOX } };

//SInitInfo init_data = GAME_8x8
SInitInfo init_data = GAME_7x7b
//SInitInfo init_data = GAME_1x16
//SInitInfo init_data = GAME_1x27

