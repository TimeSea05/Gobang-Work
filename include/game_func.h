#ifndef GAME_FUNCTIONS_H_
#define GAME_FUNCTIONS_H_

// 初始化棋盘，将数组record_board的元素全部置为0
void init_record_board();

// 根据数组record_board的值对display_board进行赋值
void record_to_display_array();

// 打印字符数组display_board
void display_board();

// 落子
// @param: type BLACKPIECE: 黑子  WHITEPIECE 白子
void drop_pieces(int type);

// 判断是否有一方已经胜出
int game_win();

// 检查禁手
int is_forbidden();

// 人人对战模式
void person_vs_person();

// 人机对战模式
void person_vs_computer();
#endif