#ifndef CHECK_FORBIDDEN_MOVES_H_
#define CHECK_FORBIDDEN_MOVES_H_

// transfer current game situation to string
char * to_string(int x, int y, int direction);

char * to_string_horizontal(int x, int y);
char * to_string_horizontal_inv(int x, int y);
char * to_string_vertical(int x, int y);
char * to_string_vertical_inv(int x, int y);
char * to_string_main_diagonal(int x, int y);
char * to_string_main_diagonal_inv(int x, int y);
char * to_string_sub_diagonal(int x, int y);
char * to_string_sub_diagonal_inv(int x, int y);

// match string
// str_s: shorter string;   str_l: longer string
int str_match(char * str_s, char * str_l);



int match_active_three_black(int x, int y, int direction);
int num_active_three_black(int x, int y);
int match_active_three_white(int x, int y, int direction);
int num_active_three_white(int x, int y);

int match_active_four_black(int x, int y, int direction);
int num_active_four(int x, int y);
int match_active_four_white(int x, int y, int direction);
int num_active_four_white(int x, int y);

int match_dead_four_black(int x, int y, int direction);
int num_dead_four_black(int x, int y);
int match_dead_four_black(int x, int y, int direction);
int num_dead_four_white(int x, int y);

int is_five_black(int x, int y);
int is_five_white(int x, int y);
#endif
