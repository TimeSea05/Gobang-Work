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



#endif
