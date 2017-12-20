//
//  Piece.hpp
//  Chess_revamped_revamped
//
//  Created by Morgan Borjigin-Wang on 10/29/17.
//  Copyright © 2017 Morgan Borjigin-Wang. All rights reserved.
//

#ifndef Piece_hpp
#define Piece_hpp

#include <stdio.h>
#include "utility.hpp"

class Piece {
private:
    // Data for Pieces
    char type;
    bool side;
    bool has_moved;
public:
    // Standard constructors for Pieces and empty tiles
    Piece(bool side_in, char type_in);
    Piece();
    Piece(const Piece& Piece_in);
    // Assignment operator for copying
    Piece& operator=(Piece& Piece_in);
    // Getters for variables
    char get_type() const;
    bool get_side() const;
    bool get_has_moved() const;
    void receive(Piece& Piece_in);
};

#endif /* Piece_hpp */
