#ifndef GAME_FUNCTIONS_H_
#define GAME_FUNCTIONS_H_

// initialize the chess board
void init_record_board();

// initialize display_board according to record_board
void record_to_display_array();

// show the board(along with pieces)
void display_board();

// drop pieces
// type: 0 for black pieces, 1 for white pieces 
void drop_pieces(int type);

// detect winnership
int game_win();
#endif