#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <stddef.h>
#include <locale.h>

#define SIZE 15
#define DEPTH 1

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
    ACTIVE_TWO = 250,
    DEAD_THREE = 250,
    ACTIVE_THREE = 2000,
    DEAD_FOUR = 2000,
    ACTIVE_FOUR = 10000,
    FIVE = 99999999,
    FORBIDDEN = -99999999
};

#endif 