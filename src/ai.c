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
    }
    mark_b += is_forbidden() * FORBIDDEN;
    
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
        return mark_b - 0.1 * mark_w;
    return mark_w - 0.1 * mark_b;
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


#define SEARCH_AI(para_1, para_2) \
    if (record_board[latest_x + (para_1)][latest_y + (para_2)] == EMPTY \
        && has_neighbor(latest_x + (para_1), latest_y + (para_2))) \
    { \
        int latest_x_copy = latest_x, latest_y_copy = latest_y; \
        latest_x = latest_x + (para_1), latest_y = latest_y + (para_2); \
        record_board[latest_x][latest_y] = type; \
        int val = alpha_beta_prune(depth - 1, !is_ai, alpha, beta, trans_type(type)); \
        record_board[latest_x][latest_y] = EMPTY; \
        if (val > alpha) \
        { \
            alpha = val; \
            if (depth == DEPTH) \
                next_point_x = latest_x, next_point_y = latest_y; \
        } \
        latest_x = latest_x_copy, latest_y = latest_y_copy; \
        if (alpha > beta) \
            goto finish_ai; \
    }

#define SEARCH_NOT_AI(para_1, para_2) \
    if (record_board[latest_x + (para_1)][latest_y + (para_2)] == EMPTY \
        && has_neighbor(latest_x + (para_1), latest_y + (para_2))) \
    { \
        int latest_x_copy = latest_x, latest_y_copy = latest_y; \
        latest_x = latest_x + (para_1), latest_y = latest_y + (para_2); \
        record_board[latest_x][latest_y] = type; \
        int val = alpha_beta_prune(depth - 1, !is_ai, alpha, beta, trans_type(type)); \
        record_board[latest_x][latest_y] = EMPTY; \
        if (val < beta) \
        { \
            beta = val; \
            if (depth == DEPTH) \
                next_point_x = latest_x, next_point_y = latest_y; \
        } \
        latest_x = latest_x_copy, latest_y = latest_y_copy; \
        if (alpha > beta) \
            goto finish_not_ai; \
    }

int alpha_beta_prune(int depth, int is_ai, int alpha, int beta, int type)
{
    if (depth == 0)
        return calculate_mark(type);
    if (is_ai)
    {
        for (int i = 0; NOT_ALL_CROSS_BORDER; i++)
        {
            for (int k = -i + 1; k <= i - 1; k++)
            {
                SEARCH_AI(k, -i);
                SEARCH_AI(k, i);
            }
            for (int j = -i; j <= i; j++)
            {
                SEARCH_AI(-i, j);
                SEARCH_AI(i, j);
            }
        }
        finish_ai: 
            return alpha;  
    }
    else
    {
        for (int i = 0; NOT_ALL_CROSS_BORDER; i++)
        {
            for (int k = -i + 1; k <= i - 1; k++)
            {
                SEARCH_NOT_AI(k, -i);
                SEARCH_NOT_AI(k, i);
            }
            for (int j = -i; j <= i; j++)
            {
                SEARCH_NOT_AI(-i, j);
                SEARCH_NOT_AI(i, j);
            }
        }
        finish_not_ai:
            return beta;
    }
}