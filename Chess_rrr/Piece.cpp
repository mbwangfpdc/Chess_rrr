//
//  Piece.cpp
//  Chess_revamped_revamped
//
//  Created by Morgan Borjigin-Wang on 10/29/17.
//  Copyright © 2017 Morgan Borjigin-Wang. All rights reserved.
//

#include "Piece.hpp"
using namespace std;

Piece::Piece(bool side_in, char type_in)
:  type(type_in), side(side_in), has_moved(false) {}

Piece::Piece() : type(EMPTY), side(WHITE), has_moved(false) {}

Piece::Piece(const Piece& Piece_in) : type(Piece_in.type), side(Piece_in.side), has_moved(Piece_in.has_moved) {}

Piece& Piece::operator=(Piece& Piece_in) {
    side = Piece_in.side;
    type = Piece_in.type;
    has_moved = Piece_in.has_moved;    
    return *this;
}

char Piece::get_type() const {
    return type;
}
bool Piece::get_side() const {
    return side;
}
bool Piece::get_has_moved() const {
    return has_moved;
}

void Piece::receive(Piece &Piece_in) {
    side = Piece_in.side;
    type = Piece_in.type;
    has_moved = true;
    
    Piece_in.type = EMPTY;
}
