#include <stdio.h>
#include "game.h"
#include "game_func.h"
#include "ai.h"
#include "constants.h"

extern int latest_x, latest_y;
extern int record_board[SIZE][SIZE];

// 判断搜索是否进行继续的判据
#define NOT_ALL_CROSS_BORDER \
    latest_x - i >= 0 || latest_x + i < SIZE || latest_y - i >= 0 || latest_y + i < SIZE

extern int next_point_x, next_point_y;

int calculate_mark(int type)
{
    int mark_b = 0, mark_w = 0;

    /*******************计算黑棋得分*******************/
    // HORIZONTAL
    for (int i = 0; i < SIZE; i++)
    {
        mark_b += num_dead_two_black(i, 0, HORIZONTAL) * DEAD_TWO;
        mark_b += num_active_two_black(i, 0, HORIZONTAL) * ACTIVE_TWO;
        mark_b += num_dead_three_black(i, 0, HORIZONTAL) * DEAD_THREE;
        mark_b += num_active_three_black(i, 0, HORIZONTAL) * ACTIVE_THREE;
        mark_b += num_dead_four_black(i, 0, HORIZONTAL) * DEAD_FOUR;
        mark_b += num_active_four_black(i, 0, HORIZONTAL) * ACTIVE_FOUR;
        mark_b += is_five_black(i, 0, HORIZONTAL) * FIVE;
        mark_b += is_forbidden(i, 0, HORIZONTAL) * FORBIDDEN;
    }
    // VERTICAL
    for (int j = 0; j < SIZE; j++)
    {
        mark_b += num_dead_two_black(0, j, VERTICAL) * DEAD_TWO;
        mark_b += num_active_two_black(0, j, VERTICAL) * ACTIVE_TWO;
        mark_b += num_dead_three_black(0, j, VERTICAL) * DEAD_THREE;
        mark_b += num_active_three_black(0, j, VERTICAL) * ACTIVE_THREE;
        mark_b += num_dead_four_black(0, j, VERTICAL) * DEAD_FOUR;
        mark_b += num_active_four_black(0, j, VERTICAL) * ACTIVE_FOUR;
        mark_b += is_five_black(0, j, VERTICAL) * FIVE;
        mark_b += is_forbidden(0, j, VERTICAL) * FORBIDDEN;
    }
    // MAIN DIAGONAL
    for (int i = 0; i < SIZE; i++)
    {
        mark_b += num_dead_two_black(0, i, MAIN_DIAGONAL) * DEAD_TWO;
        mark_b += num_active_two_black(0, i, MAIN_DIAGONAL) * ACTIVE_TWO;
        mark_b += num_dead_three_black(0, i, MAIN_DIAGONAL) * DEAD_THREE;
        mark_b += num_active_three_black(0, i, MAIN_DIAGONAL) * ACTIVE_THREE;
        mark_b += num_dead_four_black(0, i, MAIN_DIAGONAL) * DEAD_FOUR;
        mark_b += num_active_four_black(0, i, MAIN_DIAGONAL) * ACTIVE_FOUR;
        mark_b += is_five_black(0, i, MAIN_DIAGONAL) * FIVE;
        mark_b += is_forbidden(0, i, MAIN_DIAGONAL) * FORBIDDEN;
    }
    for (int i = 0; i < SIZE - 1; i++)
    {
        mark_b += num_dead_two_black(14, i, MAIN_DIAGONAL) * DEAD_TWO;
        mark_b += num_active_two_black(14, i, MAIN_DIAGONAL) * ACTIVE_TWO;
        mark_b += num_dead_three_black(14, i, MAIN_DIAGONAL) * DEAD_THREE;
        mark_b += num_active_three_black(14, i, MAIN_DIAGONAL) * ACTIVE_THREE;
        mark_b += num_dead_four_black(14, i, MAIN_DIAGONAL) * DEAD_FOUR;
        mark_b += num_active_four_black(14, i, MAIN_DIAGONAL) * ACTIVE_FOUR;
        mark_b += is_five_black(14, i, MAIN_DIAGONAL) * FIVE;
        mark_b += is_forbidden(14, i, MAIN_DIAGONAL) * FORBIDDEN;
    }
    // SUB DIAGONAL
    for (int j = 0; j < SIZE; j++)
    {
        mark_b += num_dead_two_black(0, j, SUB_DIAGONAL) * DEAD_TWO;
        mark_b += num_active_two_black(0, j, SUB_DIAGONAL) * ACTIVE_TWO;
        mark_b += num_dead_three_black(0, j, SUB_DIAGONAL) * DEAD_THREE;
        mark_b += num_active_three_black(0, j, SUB_DIAGONAL) * ACTIVE_THREE;
        mark_b += num_dead_four_black(0, j, SUB_DIAGONAL) * DEAD_FOUR;
        mark_b += num_active_four_black(0, j, SUB_DIAGONAL) * ACTIVE_FOUR;
        mark_b += is_five_black(0, j, SUB_DIAGONAL) * FIVE;
        mark_b += is_forbidden(0, j, SUB_DIAGONAL) * FORBIDDEN;
    }
    for (int j = 0; j < SIZE - 1; j++)
    {
        mark_b += num_dead_two_black(14, j, SUB_DIAGONAL) * DEAD_TWO;
        mark_b += num_active_two_black(14, j, SUB_DIAGONAL) * ACTIVE_TWO;
        mark_b += num_dead_three_black(14, j, SUB_DIAGONAL) * DEAD_THREE;
        mark_b += num_active_three_black(14, j, SUB_DIAGONAL) * ACTIVE_THREE;
        mark_b += num_dead_four_black(14, j, SUB_DIAGONAL) * DEAD_FOUR;
        mark_b += num_active_four_black(14, j, SUB_DIAGONAL) * ACTIVE_FOUR;
        mark_b += is_five_black(14, j, SUB_DIAGONAL) * FIVE;
        mark_b += is_forbidden(14, j, SUB_DIAGONAL) * FORBIDDEN;
    }

    /*******************计算白棋得分*******************/
    // HORIZONTAL
    for (int i = 0; i < SIZE; i++)
    {
        mark_w += num_dead_two_white(i, 0, HORIZONTAL) * DEAD_TWO;
        mark_w += num_active_two_white(i, 0, HORIZONTAL) * ACTIVE_TWO;
        mark_w += num_dead_three_white(i, 0, HORIZONTAL) * DEAD_THREE;
        mark_w += num_active_three_white(i, 0, HORIZONTAL) * ACTIVE_THREE;
        mark_w += num_dead_four_white(i, 0, HORIZONTAL) * DEAD_FOUR;
        mark_w += num_active_four_white(i, 0, HORIZONTAL) * ACTIVE_FOUR;
        mark_w += is_five_white(i, 0, HORIZONTAL) * FIVE;
    }
    // VERTICAL
    for (int j = 0; j < SIZE; j++)
    {
        mark_w += num_dead_two_white(0, j, VERTICAL) * DEAD_TWO;
        mark_w += num_active_two_white(0, j, VERTICAL) * ACTIVE_TWO;
        mark_w += num_dead_three_white(0, j, VERTICAL) * DEAD_THREE;
        mark_w += num_active_three_white(0, j, VERTICAL) * ACTIVE_THREE;
        mark_w += num_dead_four_white(0, j, VERTICAL) * DEAD_FOUR;
        mark_w += num_active_four_white(0, j, VERTICAL) * ACTIVE_FOUR;
        mark_w += is_five_white(0, j, VERTICAL) * FIVE;
    }
    // MAINDIAGONAL
    for (int i = 0; i < SIZE; i++)
    {
        mark_w += num_dead_two_white(0, i, MAIN_DIAGONAL) * DEAD_TWO;
        mark_w += num_active_two_white(0, i, MAIN_DIAGONAL) * ACTIVE_TWO;
        mark_w += num_dead_three_white(0, i, MAIN_DIAGONAL) * DEAD_THREE;
        mark_w += num_active_three_white(0, i, MAIN_DIAGONAL) * ACTIVE_THREE;
        mark_w += num_dead_four_white(0, i, MAIN_DIAGONAL) * DEAD_FOUR;
        mark_w += num_active_four_white(0, i, MAIN_DIAGONAL) * ACTIVE_FOUR;
        mark_w += is_five_white(0, i, MAIN_DIAGONAL) * FIVE;
    }
    for (int i = 0; i < SIZE - 1; i++)
    {
        mark_w += num_dead_two_white(14, i, MAIN_DIAGONAL) * DEAD_TWO;
        mark_w += num_active_two_white(14, i, MAIN_DIAGONAL) * ACTIVE_TWO;
        mark_w += num_dead_three_white(14, i, MAIN_DIAGONAL) * DEAD_THREE;
        mark_w += num_active_three_white(14, i, MAIN_DIAGONAL) * ACTIVE_THREE;
        mark_w += num_dead_four_white(14, i, MAIN_DIAGONAL) * DEAD_FOUR;
        mark_w += num_active_four_white(14, i, MAIN_DIAGONAL) * ACTIVE_FOUR;
        mark_w += is_five_white(14, i, MAIN_DIAGONAL) * FIVE;
    }
    // SUB DIAGONAL
    for (int j = 0; j < SIZE; j++)
    {
        mark_w += num_dead_two_white(0, j, SUB_DIAGONAL) * DEAD_TWO;
        mark_w += num_active_two_white(0, j, SUB_DIAGONAL) * ACTIVE_TWO;
        mark_w += num_dead_three_white(0, j, SUB_DIAGONAL) * DEAD_THREE;
        mark_w += num_active_three_white(0, j, SUB_DIAGONAL) * ACTIVE_THREE;
        mark_w += num_dead_four_white(0, j, SUB_DIAGONAL) * DEAD_FOUR;
        mark_w += num_active_four_white(0, j, SUB_DIAGONAL) * ACTIVE_FOUR;
        mark_w += is_five_white(0, j, SUB_DIAGONAL) * FIVE;
    }
    for (int j = 0; j < SIZE - 1; j++)
    {
        mark_w += num_dead_two_white(14, j, SUB_DIAGONAL) * DEAD_TWO;
        mark_w += num_active_two_white(14, j, SUB_DIAGONAL) * ACTIVE_TWO;
        mark_w += num_dead_three_white(14, j, SUB_DIAGONAL) * DEAD_THREE;
        mark_w += num_active_three_white(14, j, SUB_DIAGONAL) * ACTIVE_THREE;
        mark_w += num_dead_four_white(14, j, SUB_DIAGONAL) * DEAD_FOUR;
        mark_w += num_active_four_white(14, j, SUB_DIAGONAL) * ACTIVE_FOUR;
        mark_w += is_five_white(14, j, SUB_DIAGONAL) * FIVE;
    }
    
    if (type == BLACKPIECE)
        return mark_b - 0.5 * mark_w;
    return mark_w - 0.5 * mark_b;
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

// type: BLACKPIECE or WHITEPIECE
int trans_type(int type)
{
    if (type == BLACKPIECE)
        return WHITEPIECE;
    return BLACKPIECE;
}

int negative_max(int type, int depth, int alpha, int beta)
{
    if (game_win() || depth == 0)
        return calculate_mark(type);
    // 搜索方式：以刚下的棋的位置为中心，一圈一圈向外进行搜索
    // 宏定义 NOT_ALL_CROSS_BORDER 是判断搜索是否进行继续的判据
    for (int i = 1; NOT_ALL_CROSS_BORDER; i++)
    {
        for (int k = -i + 1; k <= i - 1; k++)
        {
            if (latest_x + k >= 0 && latest_x + k < SIZE && latest_y - i >= 0
                && record_board[latest_x + k][latest_y - i] == EMPTY
                && has_neighbor(latest_x + k, latest_y - i))
                // 如果搜索的位置周围没有棋子，那么我们就不再考虑这个位置
            {
                int latest_x_copy = latest_x, latest_y_copy = latest_y;
                latest_x = latest_x + k, latest_y = latest_y - i;
                record_board[latest_x][latest_y] = type;
                int value = -negative_max(trans_type(type), depth - 1 , -beta, -alpha);
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
                int value = -negative_max(trans_type(type), depth - 1 , -beta, -alpha);
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
                int value = -negative_max(trans_type(type), depth - 1 , -beta, -alpha);
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
                int value = -negative_max(trans_type(type), depth - 1 , -beta, -alpha);
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
