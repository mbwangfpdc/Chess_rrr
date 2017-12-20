//
//  utility.hpp
//  Chess_revamped_revamped
//
//  Created by Morgan Borjigin-Wang on 10/29/17.
//  Copyright © 2017 Morgan Borjigin-Wang. All rights reserved.
//

#ifndef utility_hpp
#define utility_hpp

#include <vector>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cassert>
#include <unordered_map>


// Functions to convert user inputs to board indices
int col_to_index(char char_in);
int row_to_index(char char_num_in);

// Character identifiers
const char EMPTY = ' ';
const char PAWN = 'P';
const char KNIGHT = 'N';
const char BISHOP = 'B';
const char ROOK = 'R';
const char QUEEN = 'Q';
const char KING = 'K';

// constants for allegiance
const bool WHITE = true;
const bool BLACK = false;

// The size of the board... for now
const int STANDARD_BOARD_SIZE = 8;

// For enPassant, castling, others
const bool HAS_MOVED = true;
const bool UNMOVED = false;
#endif /* utility_hpp */
