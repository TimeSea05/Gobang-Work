#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <stddef.h>
#include <locale.h>
#include <limits.h>

#define SIZE 15
#define DEPTH 2

enum PIECES{
    EMPTY = 0,
    BLACKPIECE = 1,
    BLACKTRIANGLE = 3,
    WHITEPIECE = 7,
    WHITETRIANGLE = 9
};

enum DIRECTIONS{
    HORIZONTAL = 1,
    VERTICAL,
    MAIN_DIAGONAL,
    SUB_DIAGONAL
};

enum CHESS_TYPE_MARKS{
    DEAD_TWO = 50,
    ACTIVE_TWO = 2500,
    DEAD_THREE = 4500,
    ACTIVE_THREE = 20000,
    DEAD_FOUR = 20000,
    ACTIVE_FOUR = INT_MAX / 32,
    FIVE = INT_MAX / 2,
    FORBIDDEN = -INT_MAX / 2
};

#endif 