//
//  utility.cpp
//  Chess_revamped_revamped
//
//  Created by Morgan Borjigin-Wang on 10/29/17.
//  Copyright © 2017 Morgan Borjigin-Wang. All rights reserved.
//

#include "utility.hpp"

int col_to_index(char char_in) {
    return tolower(char_in) - 97;
}

int row_to_index(char char_num_in) {
    return 7 - (int)(char_num_in - '1');
}
