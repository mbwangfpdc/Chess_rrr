//
//  Board.cpp
//  Chess_revamped_revamped
//
//  Created by Morgan Borjigin-Wang on 10/29/17.
//  Copyright © 2017 Morgan Borjigin-Wang. All rights reserved.
//

#include "Board.hpp"
using namespace std;


// Operators for managing Tiles

bool Board::Tile::operator==(const Tile& rhs) const {
    return row_data == rhs.row() && col_data == rhs.col();
}

typename Board::Tile& Board::Tile::operator++() {
    if (col_data == 7) {
        ++row_data;
        col_data = 0;
    } else {
        ++col_data;
    }
    return *this;
}

Board::Board() :
board{Piece(BLACK, ROOK), Piece(BLACK, KNIGHT), Piece(BLACK, BISHOP), Piece(BLACK, QUEEN),
    Piece(BLACK, KING), Piece(BLACK, BISHOP), Piece(BLACK, KNIGHT), Piece(BLACK, ROOK),
    Piece(BLACK, PAWN), Piece(BLACK, PAWN), Piece(BLACK, PAWN), Piece(BLACK, PAWN),
    Piece(BLACK, PAWN), Piece(BLACK, PAWN), Piece(BLACK, PAWN), Piece(BLACK, PAWN),
    Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(),
    Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(),
    Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(),
    Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(),
    Piece(WHITE, PAWN), Piece(WHITE, PAWN), Piece(WHITE, PAWN), Piece(WHITE, PAWN),
    Piece(WHITE, PAWN), Piece(WHITE, PAWN), Piece(WHITE, PAWN), Piece(WHITE, PAWN),
    Piece(WHITE, ROOK), Piece(WHITE, KNIGHT), Piece(WHITE, BISHOP), Piece(WHITE, QUEEN),
    Piece(WHITE, KING), Piece(WHITE, BISHOP), Piece(WHITE, KNIGHT), Piece(WHITE, ROOK)},
move_number(0), w_king_pos(7,4), b_king_pos(0,4) {}

////////////////////////////////////////
// Functions for visual board display //
////////////////////////////////////////

void Board::print_letter_references() const {
    cout << " ";
    for (int i = 0; i < STANDARD_BOARD_SIZE; i++) {
        cout << " " << (char)(i + 65);
    }
    cout << endl;
}

void Board::print_divider() const {
    cout << " ";
    for (int i = 0; i < STANDARD_BOARD_SIZE; i++) {
        cout << " -";
    }
    cout << endl;
}

void Board::print_line(int row) const {
    for (int i = 0; i <= STANDARD_BOARD_SIZE * 2 + 2; i++) {
        if (i == 0 || i == STANDARD_BOARD_SIZE * 2 + 2) {
            cout << STANDARD_BOARD_SIZE - row;
        } else if (i % 2 == 1) {
            cout << "|";
        } else {
            cout << Piece_at(Tile(row, i / 2 - 1));
        }
    }
    cout << endl;
}

void Board::print_board() const {
    cout << endl;
    for (int i = 0; i <= STANDARD_BOARD_SIZE * 2 + 2; i++) {
        if (i == 0 || i == STANDARD_BOARD_SIZE * 2 + 2) {
            print_letter_references();
        } else if (i % 2 == 1) {
            print_divider();
        } else {
            print_line(i / 2 - 1);
        }
    }
    cout << endl;
}

ostream& operator<<(ostream& os, const Piece& Piece_in) {
    if (Piece_in.get_type() == EMPTY) {
        os << " ";
    } else if (Piece_in.get_side() == WHITE) {
        os << Piece_in.get_type();
    } else if (Piece_in.get_side() == BLACK) {
        os << (char)tolower(Piece_in.get_type());
    }
    return os;
}

////////////////////////////////////////
// Functions for visual board display //
////////////////////////////////////////























////////////////////////////////
// Functions to examine board //
////////////////////////////////

Piece& Board::Piece_at(Tile t) {
    assert(t.row() >= 0 && t.row() < 8 && t.col() >= 0 && t.col() < 8);
    return board[t.row() * STANDARD_BOARD_SIZE + t.col()];
}

const Piece& Board::Piece_at(Tile t) const {
    assert(t.row() >= 0 && t.row() < 8 && t.col() >= 0 && t.col() < 8);
    return board[t.row() * STANDARD_BOARD_SIZE + t.col()];
}

int Board::get_move_number() const {
    return move_number;
}

bool Board::is_white_turn() const {
    return (move_number % 2) == 0;
}

Board::Tile& Board::king_pos() {
    return is_white_turn() ? w_king_pos : b_king_pos;
}

const Board::Tile& Board::king_pos() const {
    return is_white_turn() ? w_king_pos : b_king_pos;
}

////////////////////////////////
// Functions to examine board //
////////////////////////////////

























////////////////////////////////////////////////////////////////////
// Functions for altering the board state by taking, moving, etc. //
////////////////////////////////////////////////////////////////////

void Board::attempt_move(const Tile& s, const Tile& e) {
    // Store piece in case of bad move
    Piece taken_piece(Piece_at(e));
    Piece moved_piece(Piece_at(s));
    // Move piece
    Piece_at(e).receive(Piece_at(s));
    if (Piece_at(s).get_type() == KING) {
        king_pos() = e;
    }
    if (is_in_check()) {
        // If end up in check, revert move
        if (Piece_at(e).get_type() == KING) {
            king_pos() = s;
        }
        Piece_at(s) = moved_piece;
        Piece_at(e) = taken_piece;
        cout << "Your king will be lost!" << endl;
    } else {
        // Otherwise, go to the next move and set last_move, update king_pos
        ++move_number;
        last_move[0] = s;
        last_move[1] = e;
    }
}

void Board::castle_kingside() {
    // Make reference to whichever king_position is relevant
    Tile& k_pos(king_pos());
    Piece_at(Tile(k_pos.row(), k_pos.col() + 2)).receive(Piece_at(k_pos));
    Piece_at(Tile(k_pos.row(),
                  k_pos.col() + 1)).receive(Piece_at(Tile(k_pos.row(),
                                                                k_pos.col() + 3)));
    ++move_number;
    k_pos = Tile(k_pos.row(), k_pos.col() + 2);
    last_move[0] = Tile(k_pos.row(), k_pos.col() - 2);
    last_move[1] = k_pos;
}

void Board::castle_queenside() {
    Tile& k_pos(king_pos());
    Piece_at(Tile(k_pos.row(), k_pos.col() - 2)).receive(Piece_at(k_pos));
    Piece_at(Tile(k_pos.row(),
                  k_pos.col() - 1)).receive(Piece_at(Tile(k_pos.row(),
                                                                k_pos.col() - 4)));
    ++move_number;
    k_pos = Tile(k_pos.row(), k_pos.col() - 2);
    last_move[0] = Tile(k_pos.row(), k_pos.col() + 2);
    last_move[1] = k_pos;
}

void Board::attempt_take_EP(const Tile &s, const Tile &e) {
    Piece moving_pawn(Piece_at(s));
    Piece_at(e).receive(Piece_at(s));
    if (is_white_turn()) {
        Piece taken_pawn(Piece_at(Tile(e.row() + 1, e.col())));
        Piece_at(Tile(e.row() + 1, e.col())).receive(Piece_at(Tile(e.row() - 1, e.col())));
        if (is_in_check()) {
            Piece_at(s) = moving_pawn;
            Piece_at(Tile(e.row() + 1, e.col())) = taken_pawn;
        } else {
            ++move_number;
            last_move[0] = s;
            last_move[1] = e;
        }
    } else {
        Piece taken_pawn(Piece_at(Tile(e.row() - 1, e.col())));
        Piece_at(Tile(e.row() - 1, e.col())).receive(Piece_at(Tile(e.row() + 1, e.col()))) ;
        if (is_in_check()) {
            Piece_at(s) = moving_pawn;
            Piece_at(Tile(e.row() - 1, e.col())) = taken_pawn;
        } else {
            ++move_number;
            last_move[0] = s;
            last_move[1] = e;
        }
    }
}
////////////////////////////////////////////////////////////////////
// Functions for altering the board state by taking, moving, etc. //
////////////////////////////////////////////////////////////////////























/////////////////////////////////////////////////
// Functions for check, threatening, checkmate //
/////////////////////////////////////////////////

bool Board::can_attack(const Tile &s, const Tile &e) const {
    switch (Piece_at(s).get_type()) {
        case PAWN:
            return is_potential_pawn_take(s, e);
            break;
        case ROOK:
            return is_valid_rook_move(s, e);
            break;
        case KNIGHT:
            return is_valid_knight_move(s, e);
            break;
        case BISHOP:
            return is_valid_bishop_move(s, e);
            break;
        case QUEEN:
            return is_valid_queen_move(s, e);
            break;
        case KING:
            return is_valid_king_move(s, e);
            break;
        case EMPTY:
            return false;
            break;
        default:
            return false;
            break;
    }
}

bool Board::tile_is_attacked(const Tile& target) const {
    for (Tile tile(0,0); tile.row() < 8; ++tile) {
        if (Piece_at(tile).get_type() != EMPTY &&
            Piece_at(tile).get_side() != is_white_turn() &&
            can_attack(tile, target)) {
            return true;
        }
    }
    return false;
}

bool Board::is_in_check() const {
    if (is_white_turn()) {
        return tile_is_attacked(w_king_pos);
    } else {
        return tile_is_attacked(b_king_pos);
    }
}

bool Board::is_checkmated() const {
    return true;
}

/////////////////////////////////////////////////
// Functions for check, threatening, checkmate //
/////////////////////////////////////////////////

























///////////////////////////////////////
// Basic movement validity functions //
///////////////////////////////////////

bool Board::is_valid_move(const Tile& s, const Tile& e) const {
    // False if trying to move EMPTY, trying to move onto friendly, or trying
    // to move an enemy piece
    if (Piece_at(s).get_type() == EMPTY ||
        (Piece_at(e).get_side() == Piece_at(s).get_side() && Piece_at(e).get_type() != EMPTY) ||
        (Piece_at(s).get_side() == BLACK && move_number % 2 == 0) ||
        (Piece_at(s).get_side() == WHITE && move_number % 2 == 1)) {
        return false;
    }
    switch (Piece_at(s).get_type()) {
        case PAWN:
            return is_valid_pawn_march(s, e) || is_valid_pawn_take(s, e);
            break;
        case ROOK:
            return is_valid_rook_move(s, e);
            break;
        case KNIGHT:
            return is_valid_knight_move(s, e);
            break;
        case BISHOP:
            return is_valid_bishop_move(s, e);
            break;
        case QUEEN:
            return is_valid_queen_move(s, e);
            break;
        case KING:
            return is_valid_king_move(s, e);
            break;
        case EMPTY:
            return false;
            break;
        default:
            return false;
            break;
    }
}

// Returns true if the pawn can move to the given destination
bool Board::is_valid_pawn_march(const Tile& s, const Tile& e) const {
    if (e.col() == s.col()) {
        // Up/down peaceful movement by pawns
        if (Piece_at(s).get_side() == WHITE) {
            // Valid only if white hasn't moved the pawn yet, and the spaces it
            // moves onto are free.
            // Otherwise, check if the space ahead of white's pawn is clear
            if (e.row() - s.row() == -2) {
                return Piece_at(Tile(e.row() + 1, e.col())).get_type() == EMPTY &&
                Piece_at(e).get_type() == EMPTY &&
                !Piece_at(s).get_has_moved();
            } else if (e.row() - s.row() == -1) {
                return Piece_at(e).get_type() == EMPTY;
            }
        } else if (Piece_at(s).get_side() == BLACK) {
            // Same as above, but for marching the opposite direction
            if (e.row() - s.row() == 2) {
                return Piece_at(Tile(e.row() - 1, e.col())).get_type() == EMPTY &&
                Piece_at(e).get_type() == EMPTY &&
                !Piece_at(s).get_has_moved();
            } else if (e.row() - s.row() == 1) {
                return Piece_at(e).get_type() == EMPTY;
            }
        }
    }
    return false;
}

bool Board::is_valid_pawn_take(const Tile &s, const Tile &e) const {
    if (Piece_at(e).get_type() != EMPTY &&
        Piece_at(e).get_side() != Piece_at(s).get_side() &&
        is_potential_pawn_take(s, e)) {
        return true;
    }
    return false;
}

bool Board::is_potential_pawn_take(const Tile &s, const Tile &e) const {
    if (abs(e.col() - s.col()) == 1) {
        // Diagonal attacking by pawns, including passantability.
        if (Piece_at(s).get_side() == WHITE) {
            return e.row() == s.row() - 1;
        } else if (Piece_at(s).get_side() == BLACK) {
            return e.row() == s.row() + 1;
        }
    }
    return false;
}

// Returns true if a rook can move to the given destination
bool Board::is_valid_rook_move(const Tile& s, const Tile& e) const {
    if (e.row() == s.row()) {
        for (int i = 1; i < abs(e.col() - s.col()); i++) {
            if (s.col() < e.col() && Piece_at(Tile(s.row(), s.col() + i)).get_type() != EMPTY) {
                return false;
            } else if (s.col() > e.col() && Piece_at(Tile(s.row(), s.col() - i)).get_type() != EMPTY) {
                return false;
            }
        }
        return true;
    }
    if (e.col() == s.col()) {
        for (int i = 1; i < abs(e.row() - s.row()); i++) {
            if (s.row() < e.row() && Piece_at(Tile(s.row() + i, s.col())).get_type() != EMPTY) {
                return false;
            } else if (s.row() > e.row() && Piece_at(Tile(s.row() - i, s.col())).get_type() != EMPTY) {
                return false;
            }
        }
        return true;
    }
    return false;
}

// Returns true if the given destination is on the same diagonal as the Piece and there are only EMPTY pieces in the way.
bool Board::is_valid_bishop_move(const Tile& s, const Tile& e) const {
    if (abs(e.col() - s.col()) == abs(e.row() - s.row())) {
        for (int i = 1; i < abs(e.row() - s.row()); i++) {
            if (Piece_at(Tile(s.row() + i * ((e.row() - s.row()) / abs(e.row() - s.row())),
                         s.col() + i * ((e.col() - s.col()) / abs(e.col() - s.col())))).get_type() != EMPTY) {
                return false;
            }
        }
        return true;
    }
    return false;
}

// Returns true if the given destination is 2 + 1 away from the Piece's current location.  CAN LEAP OVER PIECES.
bool Board::is_valid_knight_move(const Tile& s, const Tile& e) const {
    return (abs(e.row() - s.row()) + abs(e.col() - s.col()) == 3 &&
            (abs(e.row() - s.row()) == 1 || abs(e.col() - s.col()) == 1));
}

// Returns true if the given destination is one of the 8 tiles surrounding the Piece's current location
bool Board::is_valid_king_move(const Tile& s, const Tile& e) const {
    return (abs(e.row() - s.row()) <= 1 && abs(e.col() - s.col()) <= 1);
}

bool Board::is_valid_queen_move(const Tile& s, const Tile& e) const {
    return is_valid_rook_move(s, e) || is_valid_bishop_move(s, e);
}



/*bool Board::is_exposing_king(const Tile &s, const Tile &e) const {
    if (s != king_pos()) {
        if (s.col() != e.col() && s.col() == king_pos().col()) {
            <#statements#>
        }
        if (s.row() != e.row() && s.row() == king_pos().row){
            <#statements#>
        }
        if () {
            
        }
    } else {
        return tile_is_attacked(e);
    }
    
}*/
///////////////////////////////////////
// Basic movement validity functions //
///////////////////////////////////////





































////////////////////////////
// Special movement cases //
////////////////////////////

// Returns true if the pawn at s.row(), s.col() can take an enemy pawn
// With en passant by moving to e.row(), e.col()
bool Board::is_enpassantable(const Tile& s, const Tile& e) const {
    if (abs(e.col() - s.col()) != 1) {
        return false;
    }
    if (is_white_turn()) {
        return e.row() == s.row() - 1 &&
        Piece_at(Tile(e.row() + 1, e.col())).get_type() == PAWN &&
        Piece_at(Tile(e.row() + 1, e.col())).get_side() == BLACK &&
        last_move[0] == Tile(e.row() - 1, e.col()) &&
        last_move[1] == Tile(e.row() + 1, e.col());
    } else {
        return e.row() == s.row() + 1 &&
        Piece_at(Tile(e.row() - 1, e.col())).get_type() == PAWN &&
        Piece_at(Tile(e.row() - 1, e.col())).get_side() == WHITE &&
        last_move[0] == Tile(e.row() + 1, e.col()) &&
        last_move[1] == Tile(e.row() - 1, e.col());
    }
}

// Return true if space between king and kingside guard are empty, and each are
// unmoved
bool Board::can_castle_kingside() const {
    return !tile_is_attacked(king_pos()) &&
    !tile_is_attacked(Tile(king_pos().row(), king_pos().col() + 1)) &&
    !tile_is_attacked(Tile(king_pos().row(), king_pos().col() + 2)) &&
    Piece_at(Tile(king_pos().row(), king_pos().col() + 1)).get_type() == EMPTY &&
    Piece_at(Tile(king_pos().row(), king_pos().col() + 2)).get_type() == EMPTY &&
    Piece_at(king_pos()).get_has_moved() == UNMOVED &&
    Piece_at(Tile(king_pos().row(), king_pos().col() + 3)).get_has_moved() == UNMOVED;
}

// Return true if space between king and queenside guard are empty, and each are
// unmoved
bool Board::can_castle_queenside() const {
    return !tile_is_attacked(king_pos()) &&
    !tile_is_attacked(Tile(king_pos().row(), king_pos().col() - 1)) &&
    !tile_is_attacked(Tile(king_pos().row(), king_pos().col() - 2)) &&
    Piece_at(Tile(king_pos().row(), king_pos().col() - 1)).get_type() == EMPTY &&
    Piece_at(Tile(king_pos().row(), king_pos().col() - 2)).get_type() == EMPTY &&
    Piece_at(Tile(king_pos().row(), king_pos().col() - 3)).get_type() == EMPTY &&
    Piece_at(king_pos()).get_has_moved() == UNMOVED &&
    Piece_at(Tile(king_pos().row(), king_pos().col() - 4)).get_has_moved() == UNMOVED;
}

////////////////////////////
// Special movement cases //
////////////////////////////
