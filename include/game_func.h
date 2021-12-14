#ifndef GAME_FUNCTIONS_H_
#define GAME_FUNCTIONS_H_

// 初始化棋盘，将数组record_board的元素全部置为0
void init_record_board();

// 根据数组record_board的值对display_board进行赋值
void record_to_display_array();

// 打印字符数组display_board
void display_board();

/** 
 * @brief 落子
 * @param type BLACKPIECE: 黑子  WHITEPIECE 白子
 * @param game_mode 游戏模式(人人或者人机)
 * @return 0为正常落子, 1为悔棋
 **/
int drop_pieces(int type, int game_mode);

// 悔棋
void regret(int game_mode);

// 判断是否有一方已经胜出
int game_win();

// 检查禁手
int is_forbidden();

// 人人对战模式
void person_vs_person();

// 人机对战模式
void person_vs_computer();
#endif