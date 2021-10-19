#include "game.h"
#include "game_functions.h"
#include "ai.h"

#define SIZE 15
#define EMPTY 0
#define BLACKPIECE 1
#define WHITEPIECE 7

#define DEAD_TWO 50
#define ACTIVE_TWO 250
#define DEAD_THREE 250
#define ACTIVE_THREE 2000
#define DEAD_FOUR 2000
#define ACTIVE_FOUR 10000
#define FIVE 99999999
#define FORBIDDEN -99999999

extern int latest_x, latest_y;
extern int record_board[SIZE][SIZE];

#define NOT_ALL_CROSS_BORDER \
    latest_x - i >= 0 || latest_x + i < SIZE || latest_y - i >= 0 || latest_y + i < SIZE

int calculate_mark(int x, int y, int type)
{
    int mark = 0;
    switch (type)
    {
    case BLACKPIECE:
        mark += num_dead_two_black(x, y) * DEAD_TWO;
        mark += num_active_two_black(x, y) * ACTIVE_TWO;
        mark += num_dead_three_black(x, y) * DEAD_THREE;
        mark += num_active_three_black(x, y) * ACTIVE_THREE;
        mark += num_dead_four_black(x, y) * DEAD_FOUR;
        mark += num_active_four_black(x, y) * ACTIVE_FOUR;
        mark += is_five_black(x, y) * FIVE;
        mark += is_forbidden(x, y) * FORBIDDEN;
        break;
    case WHITEPIECE:
        mark += num_dead_two_white(x, y) * DEAD_TWO;
        mark += num_active_two_white(x, y) * ACTIVE_TWO;
        mark += num_dead_three_white(x, y) * DEAD_THREE;
        mark += num_active_three_white(x, y) * ACTIVE_THREE;
        mark += num_dead_four_white(x, y) * DEAD_FOUR;
        mark += num_active_four_white(x, y) * ACTIVE_FOUR;
        mark += is_five_white(x, y) * FIVE;
        break;
    }
    return mark;
}

int evaluate(int x, int y, int type)
{
    // 评估的方式：计算放置棋子前后在坐标(x,y)处产生的分数差
    // 此处已经假定(x,y)处没有棋子
    // 'o' represents 'original', 'n' represents 'now'
    int black_mark_o = calculate_mark(x, y, BLACKPIECE);
    int white_mark_o = calculate_mark(x, y, WHITEPIECE);
    record_board[x][y] = type;
    int black_mark_n = calculate_mark(x, y, BLACKPIECE);
    int white_mark_n = calculate_mark(x, y, WHITEPIECE);
    record_board[x][y] = EMPTY;
    return (black_mark_n - black_mark_o) + (white_mark_o - white_mark_n);
}
int is_forbidden(int x, int y)
{
    int res = 0;
    if (is_five_black(x, y))
        return 0;
    if (num_active_three_black(x, y) > 1)
        res++;
    if (num_dead_four_black(x, y) + num_active_four_black(x, y) > 1)
        res++;
    if (num_overline(x, y))
        res++;
    if (res > 0)
        return 1;
    return 0;
}

// int negative_max(int x, int y, int is_ai, int depth, int alpha, int beta)
int negative_max(int x, int y)
{
    for (int i = 1; NOT_ALL_CROSS_BORDER; i++)
    {
        for (int j = -i; j <= i; j++)
        {
            if (latest_x - i >= 0 && latest_y + j < SIZE 
                && record_board[latest_x - i][latest_y + j] == EMPTY)
            {
                printf("%d %d\n", latest_x - i, latest_y + j);
            }
            if (latest_x + i < SIZE && latest_y + j < SIZE
                && record_board[latest_x + i][latest_y + j] == EMPTY)
            {
                printf("%d %d\n", latest_x + i, latest_y + j);
            }
        }
        for (int k = -i + 1; k <= i - 1; k++)
        {
            if (latest_x + k < SIZE && latest_y - i >= 0
                && record_board[latest_x + k][latest_y - i] == EMPTY)
            {
                printf("%d %d\n", latest_x + k, latest_y - i);
            }
            if (latest_x + k < SIZE && latest_y + i < SIZE
                && record_board[latest_x + k][latest_y + i] == EMPTY)
            {
                printf("%d %d\n", latest_x + k, latest_y + i);
            }
        }
    }
    return 0;
    /*
        下一步的计划：
        1.设置递归初始条件
        2.解决放子再收回的操作
        3.研究alpha-beta剪枝的具体操作
    */
}