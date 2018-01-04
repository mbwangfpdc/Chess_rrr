//
//  main.cpp
//  Chess_revamped_revamped
//
//  Created by Morgan Borjigin-Wang on 10/29/17.
//  Copyright © 2017 Morgan Borjigin-Wang. All rights reserved.
//

#include <iostream>
#include "Game.hpp"
using namespace std;


int main(int argc, const char * argv[]) {
    Game game(2);
    ifstream test_file;
    test_file.open("test_EP_down.txt");
    game.run_2P_game(cin);
}


