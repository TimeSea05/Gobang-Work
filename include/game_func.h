#ifndef GAME_FUNCTIONS_H_
#define GAME_FUNCTIONS_H_

// @brief 初始化棋盘，将数组record_board的元素全部置为0
void init_record_board();

// @brief 根据数组record_board的值对display_board进行赋值
void record_to_display_array();

// @brief 打印字符数组display_board
void display_board();

// drop pieces
// type: 0 for black pieces, 1 for white pieces 
void drop_pieces(int type);

// @brief 判断是否有一方已经胜出
int game_win();
#endif