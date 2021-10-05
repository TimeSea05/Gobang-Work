#ifndef CHECK_FORBIDDEN_MOVES_H_
#define CHECK_FORBIDDEN_MOVES_H_

int is_five_black(int x, int y);
int is_five_white(int x, int y);
int is_over_line(int x, int y);
int is_over_two_active_threes(int x, int y);

// detect active threes around assigned piece
int is_active_three_horizontal(int x, int y);
int is_active_three_vertical(int x, int y);
int is_active_three_main_diagonal(int x, int y);
int is_active_three_sub_diagonal(int x, int y);

// detect fours around assinged piece
int is_four_horizontal(int x, int y);
#endif
