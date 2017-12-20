//
//  Board.hpp
//  Chess_revamped_revamped
//
//  Created by Morgan Borjigin-Wang on 10/29/17.
//  Copyright © 2017 Morgan Borjigin-Wang. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>
#include "Piece.hpp"


class Board {
public:
    // Tile class to represent board locations
    struct Tile {
    private:
        int row_data;
        int col_data;
    public:
        Tile(int row_in, int col_in) : row_data(row_in), col_data(col_in) {}
        Tile() : row_data(0), col_data(0) {}
        int row() const { return row_data; }
        int col() const { return col_data; }
        Tile& operator++();
        bool operator==(const Tile& rhs) const;
    };
private:
    // The gameboard's data array
    Piece board[STANDARD_BOARD_SIZE * STANDARD_BOARD_SIZE];
    // The history of moves on this board, in form s, e
    int move_number;
    Tile last_move[2];
    Piece last_taken;
    
    Tile w_king_pos;
    Tile b_king_pos;
    
    // Returning reference to a Piece at a given location, const or not
    Piece& Piece_at(Tile t);
    const Piece& Piece_at(Tile t) const;
    
    // Functions to print board
    // Prints letters on bottom and top rows
    void print_letter_references() const;
    // Prints dividers between rows
    void print_divider() const;
    // Print a line with pieces, numerical indicators, and | barriers
    void print_line(int row) const;
    
    // Functions for piece move validity
    bool is_valid_pawn_march(const Tile& s, const Tile& e) const;
    bool is_valid_pawn_take(const Tile& s, const Tile& e) const;
    bool is_potential_pawn_take(const Tile& s, const Tile& e) const;
    bool is_valid_knight_move(const Tile& s, const Tile& e) const;
    bool is_valid_bishop_move(const Tile& s, const Tile& e) const;
    bool is_valid_rook_move(const Tile& s, const Tile& e) const;
    bool is_valid_queen_move(const Tile& s, const Tile& e) const;
    bool is_valid_king_move(const Tile& s, const Tile& e) const;
    
    // Returns w_king_pos or b_king_pos based on turn_num
    Tile& king_pos();
    const Tile& king_pos() const;
    
    // Position evaluation for check/checkmate
    // Returns true if piece at s can attack tile e
    bool can_attack(const Tile& s, const Tile& e) const;
    // Returns true if tile is threatened by ENEMY ARMY
    bool tile_is_attacked(const Tile& target) const;
    
    
    // Returns a vector of vectors of Tiles to run analysis on
    std::vector<std::vector<Tile>> get_legal_moves();
    
    // Position evaluation for AI
    int position_score(std::vector<Piece>);
public:
    // Default and only ctor
    Board();
    // Prints out the board
    void print_board() const;
    // Returns the movenumber for use in Game
    int get_move_number() const;
    // Returns true if it's white's turn
    bool is_white_turn() const;
    
    // Return true if the piece has a valid standard move
    bool is_valid_move(const Tile& s, const Tile& e) const;
    // Special cases of movement
    bool is_enpassantable(const Tile& s, const Tile& e) const;
    bool can_castle_kingside() const;
    bool can_castle_queenside() const;
    // For move legality regarding king under attack
    // Returns true if enemy army can attack king
    bool is_in_check() const;
    bool move_drops_king(const Tile& s, const Tile& e);
    bool EP_drops_king(const Tile&s, const Tile& e);
    
    // Sets the Piece at e.row(), e.col() to the Piece at s.row(), s.col()
    // then set that starting Piece to empty.  If this leaves your king in
    // check, revert to original state and allow another move
    void attempt_move(const Tile& s, const Tile& e);
    // Special move commands
    void castle_kingside();
    void castle_queenside();
    void attempt_take_EP(const Tile& s, const Tile& e);
    // Returns true if enemy army can attack king and king can't find safety
    bool is_checkmated() const;
    
};

std::ostream& operator<<(std::ostream& os, const Piece& Piece_in);

#endif /* Board_hpp */
