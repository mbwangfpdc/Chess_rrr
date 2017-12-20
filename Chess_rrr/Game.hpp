//
//  Game.hpp
//  Chess_revamped_revamped
//
//  Created by Morgan Borjigin-Wang on 10/29/17.
//  Copyright © 2017 Morgan Borjigin-Wang. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <fstream>
#include "Board.hpp"

using namespace std;

class Game {
private:
    Board board;
    int player_num;
    
    void print_prompt() const;
    bool is_standard_input(std::string input) const;
    bool is_castling_input(std::string input) const;
    bool is_EP_input(std::string input) const;
    void invalid_input(istream& is) const;
    
    void calculate_move();
    void make_move_human(string input, istream& is);
    void make_move_computer();
public:
    void run_2P_game(istream& in_s);
    void run_1P_game(istream& in_s);
    void run_0P_game(istream& in_s);
    Game(int player_number_in);
};

#endif /* Game_hpp */
