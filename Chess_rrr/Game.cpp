//
//  Game.cpp
//  Chess_revamped_revamped
//
//  Created by Morgan Borjigin-Wang on 10/29/17.
//  Copyright © 2017 Morgan Borjigin-Wang. All rights reserved.
//

#include "Game.hpp"
using namespace std;

Game::Game(int player_number_in) : board(), player_num(player_number_in) {}

bool Game::is_standard_input(string input) const {
    return input.length() == 4 &&
           col_to_index(input[0]) >= 0 && col_to_index(input[0]) < STANDARD_BOARD_SIZE &&
           row_to_index(input[1]) >= 0 && row_to_index(input[1]) < STANDARD_BOARD_SIZE &&
           col_to_index(input[2]) >= 0 && col_to_index(input[2]) < STANDARD_BOARD_SIZE &&
           row_to_index(input[3]) >= 0 && row_to_index(input[3]) < STANDARD_BOARD_SIZE;
}

bool Game::is_castling_input(string input) const {
    return input == "0-0" || input == "0-0-0";
}

bool Game::is_EP_input(std::string input) const {
    return input.length() == 6 &&
    col_to_index(input[0]) >= 0 && col_to_index(input[0]) < STANDARD_BOARD_SIZE &&
    row_to_index(input[1]) >= 0 && row_to_index(input[1]) < STANDARD_BOARD_SIZE &&
    col_to_index(input[2]) >= 0 && col_to_index(input[2]) < STANDARD_BOARD_SIZE &&
    row_to_index(input[3]) >= 0 && row_to_index(input[3]) < STANDARD_BOARD_SIZE &&
    input[4] == 'e' && input[5] == 'p';
}

void Game::run_2P_game(istream& ifs) {
    print_prompt();
    string input;
    while (ifs >> input && input != "resign") {
        if (board.is_checkmated()) { cout << "Checkmate!" << endl; break; }
        make_move_human(input, ifs);
    }
    if (board.get_move_number() % 2 == 0) {
        cout << "Black wins!" << endl;
    } else {
        cout << "White wins!" << endl;
    }
}

void Game::print_prompt() const {
    board.print_board();
    cout << "Turn " << board.get_move_number() / 2 + 1 << endl;
    if (board.get_move_number() % 2 == 0) {
        cout << "White";
    } else {
        cout << "Black";
    }
    cout << " to move:" << endl;
}

void Game::invalid_input(istream& is) const {
    string garbo;
    cout << "Invalid input" << endl;
    getline(cin, garbo);
    cin.clear();
}

void Game::calculate_move() {
    
}

void Game::make_move_human(string input, istream& is) {
    Board::Tile s(row_to_index(input[1]), col_to_index(input[0]));
    Board::Tile e(row_to_index(input[3]), col_to_index(input[2]));
    if (is_standard_input(input)) {
        if (board.is_valid_move(s, e)) {
            board.attempt_move(s, e);
            print_prompt();
        } else {
            cout << "Illegal move" << endl;
        }
    } else if (is_castling_input(input)) {
        if (input.length() == 3 && board.can_castle_kingside()) {
            board.castle_kingside();
            print_prompt();
        } else if (board.can_castle_queenside()) {
            board.castle_queenside();
            print_prompt();
        } else {
            cout << "Illegal move" << endl;
        }
    } else if (is_EP_input(input)) {
        if (board.is_enpassantable(s, e)) {
            board.attempt_take_EP(s, e);
            print_prompt();
        } else {
            cout << "Illegal move" << endl;
        }
    } else {
        invalid_input(is);
    }
}
