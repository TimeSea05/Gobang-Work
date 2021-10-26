#include <stdio.h>
#include "game.h"
#include "game_func.h"
#include "ai.h"
#include "constants.h"

extern int latest_x, latest_y;
extern int record_board[SIZE][SIZE];

#define NOT_ALL_CROSS_BORDER \
    latest_x - i >= 0 || latest_x + i < SIZE || latest_y - i >= 0 || latest_y + i < SIZE

extern int next_point_x, next_point_y;

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
    // 此处已经假定(x,y)处有棋子
    // 'o' represents 'original', 'n' represents 'now'
    int black_mark_o = calculate_mark(x, y, BLACKPIECE);
    int white_mark_o = calculate_mark(x, y, WHITEPIECE);
    record_board[x][y] = EMPTY;
    int black_mark_n = calculate_mark(x, y, BLACKPIECE);
    int white_mark_n = calculate_mark(x, y, WHITEPIECE);
    record_board[x][y] = type;
    if (type == BLACKPIECE)
        return (black_mark_o - black_mark_n) - (white_mark_o - white_mark_n);
    return (white_mark_o - white_mark_n) - (black_mark_o - black_mark_n) * 10;
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

int has_neighbor(int x, int y)
{
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;
            if (x + i < 0 || x + i >= SIZE || y + j < 0 || y + j >= SIZE)
                continue;
            if (!record_board[x + i][y + j] == EMPTY)
                return 1;
        }
    return 0;
}

int trans_type(int type)
{
    if (type == BLACKPIECE)
        return WHITEPIECE;
    return BLACKPIECE;
}
// type: BLACKPIECE or WHITEPIECE

int negative_max(int type, int depth, int alpha, int beta)
{
    if (game_win() || depth == 0)
        return evaluate(latest_x, latest_y, trans_type(type));
    for (int i = 1; NOT_ALL_CROSS_BORDER; i++)
    {
        for (int k = -i + 1; k <= i - 1; k++)
        {
            if (latest_x + k >= 0 && latest_x + k < SIZE && latest_y - i >= 0
                && record_board[latest_x + k][latest_y - i] == EMPTY
                && has_neighbor(latest_x + k, latest_y - i))
            {
                int latest_x_copy = latest_x, latest_y_copy = latest_y;
                latest_x = latest_x + k, latest_y = latest_y - i;
                record_board[latest_x][latest_y] = type;
                int value = evaluate(latest_x, latest_y, type);
                record_board[latest_x][latest_y] = EMPTY;
                if (value > alpha)
                {
                    alpha = value;
                    if (depth == DEPTH)
                        next_point_x = latest_x, next_point_y = latest_y;
                    if (value >= beta)
                    {
                        latest_x = latest_x_copy, latest_y = latest_y_copy;
                        return beta;
                    }
                    alpha = value;
                }
                latest_x = latest_x_copy, latest_y = latest_y_copy;
            }
            if (latest_x + k >= 0 && latest_x + k < SIZE && latest_y + i <= SIZE
                && record_board[latest_x + k][latest_y + i] == EMPTY
                && has_neighbor(latest_x + k, latest_y + i))
            {
                int latest_x_copy = latest_x, latest_y_copy = latest_y;
                latest_x = latest_x + k, latest_y = latest_y + i;
                record_board[latest_x][latest_y] = type;
                int value = evaluate(latest_x, latest_y, type);
                record_board[latest_x][latest_y] = EMPTY;
                if (value > alpha)
                {
                    alpha = value;
                    if (depth == DEPTH)
                        next_point_x = latest_x, next_point_y = latest_y;
                    if (value >= beta)
                    {
                        latest_x = latest_x_copy, latest_y = latest_y_copy;
                        return beta;
                    }
                    alpha = value;
                }
                latest_x = latest_x_copy, latest_y = latest_y_copy;
            }
        }

        for (int j = -i; j <= i; j++)
        {
            if (latest_x - i >= 0 && latest_y + j >= 0 && latest_y + j < SIZE
                && record_board[latest_x - i][latest_y + j] == EMPTY
                && has_neighbor(latest_x - i, latest_y + j))
            {
                int latest_x_copy = latest_x, latest_y_copy = latest_y;
                latest_x = latest_x - i, latest_y = latest_y + j;
                record_board[latest_x][latest_y] = type;
                int value = evaluate(latest_x, latest_y, type);
                record_board[latest_x][latest_y] = EMPTY;
                if (value > alpha)
                {
                    alpha = value;
                    if (depth == DEPTH)
                        next_point_x = latest_x, next_point_y = latest_y;
                    if (value >= beta)
                    {
                        latest_x = latest_x_copy, latest_y = latest_y_copy;
                        return beta;
                    }
                    alpha = value;
                }
                latest_x = latest_x_copy, latest_y = latest_y_copy;
            }
            if (latest_x + i < SIZE && latest_y + j >= 0 && latest_y + j < SIZE
                && record_board[latest_x + i][latest_y + j] == EMPTY
                && has_neighbor(latest_x + i, latest_y + j))
            {
                int latest_x_copy = latest_x, latest_y_copy = latest_y;
                latest_x = latest_x + i, latest_y = latest_y + j;
                record_board[latest_x][latest_y] = type;
                int value = evaluate(latest_x, latest_y, type);
                record_board[latest_x][latest_y] = EMPTY;
                if (value > alpha)
                {
                    alpha = value;
                    if (depth == DEPTH)
                        next_point_x = latest_x, next_point_y = latest_y;
                    if (value >= beta)
                    {
                        latest_x = latest_x_copy, latest_y = latest_y_copy;
                        return beta;
                    }
                    alpha = value;
                }
                latest_x = latest_x_copy, latest_y = latest_y_copy;
            }
        }
        
    }
    return alpha;
}
