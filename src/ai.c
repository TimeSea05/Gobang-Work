#include <stdio.h>
#include "game.h"
#include "game_func.h"
#include "ai.h"
#include "constants.h"

extern int latest_x, latest_y;
extern int record_board[SIZE][SIZE];
extern int next_point_x, next_point_y;

/**
 * 在程序中多处使用宏函数来精简代码结构，导致代码的可读性降低
 * 如果想更好地理解每一个宏函数的意义，可借助你使用的IDE或者编辑器
 * 以VSCode for Linux为例，当鼠标停留在宏函数上方时
 * 编辑器会自动将宏扩展
 **/

// 判断搜索是否进行继续的判据
#define NOT_ALL_CROSS_BORDER \
    latest_x - i >= 0 || latest_x + i < SIZE || latest_y - i >= 0 || latest_y + i < SIZE

// 计算黑棋得分
#define ADD_MARK_BLACK(pos_1, pos_2, DIRECTION) \
    mark_b += num_dead_two_black(pos_1, pos_2, DIRECTION) * DEAD_TWO;\
    mark_b += num_active_two_black(pos_1, pos_2, DIRECTION) * ACTIVE_TWO;\
    mark_b += num_dead_three_black(pos_1, pos_2, DIRECTION) * DEAD_THREE;\
    mark_b += num_active_three_black(pos_1, pos_2, DIRECTION) * ACTIVE_THREE; \
    mark_b += num_dead_four_black(pos_1, pos_2, DIRECTION) * DEAD_FOUR;\
    mark_b += num_active_four_black(pos_1, pos_2, DIRECTION) * ACTIVE_FOUR;\
    mark_b += is_five_black(pos_1, pos_2, DIRECTION) * FIVE;

// 计算白棋得分
#define ADD_MARK_WHITE(pos_1, pos_2, DIRECTION) \
    mark_w += num_dead_two_white(pos_1, pos_2, DIRECTION) * DEAD_TWO;\
    mark_w += num_active_two_white(pos_1, pos_2, DIRECTION) * ACTIVE_TWO;\
    mark_w += num_dead_three_white(pos_1, pos_2, DIRECTION) * DEAD_THREE;\
    mark_w += num_active_three_white(pos_1, pos_2, DIRECTION) * ACTIVE_THREE;\
    mark_w += num_dead_four_white(pos_1, pos_2, DIRECTION) * DEAD_FOUR;\
    mark_w += num_active_four_white(pos_1, pos_2, DIRECTION) * ACTIVE_FOUR;\
    mark_w += is_five_white(pos_1, pos_2, DIRECTION) * FIVE;

int calculate_mark(int type)
{
    int mark_b = 0, mark_w = 0;

    /*******************计算黑棋得分*******************/
    // HORIZONTAL
    for (int i = 0; i < SIZE; i++)
    {
        ADD_MARK_BLACK(i, 0, HORIZONTAL);
    }
    // VERTICAL
    for (int j = 0; j < SIZE; j++)
    {
        ADD_MARK_BLACK(0, j, VERTICAL);
    }
    // MAIN DIAGONAL
    for (int i = 0; i < SIZE; i++)
    {
        ADD_MARK_BLACK(0, i, MAIN_DIAGONAL);
    }
    for (int i = 0; i < SIZE - 1; i++)
    {
        ADD_MARK_BLACK(14, i, MAIN_DIAGONAL);
    }
    // SUB DIAGONAL
    for (int j = 0; j < SIZE; j++)
    {
        ADD_MARK_BLACK(0, j, SUB_DIAGONAL);
    }
    for (int j = 0; j < SIZE - 1; j++)
    {
        ADD_MARK_BLACK(14, j, SUB_DIAGONAL);
    }
    mark_b += is_forbidden() * FORBIDDEN;
    
    /*******************计算白棋得分*******************/
    // HORIZONTAL
    for (int i = 0; i < SIZE; i++)
    {
        ADD_MARK_WHITE(i, 0, HORIZONTAL);
    }
    // VERTICAL
    for (int j = 0; j < SIZE; j++)
    {
        ADD_MARK_WHITE(0, j, VERTICAL);
    }
    // MAINDIAGONAL
    for (int i = 0; i < SIZE; i++)
    {
        ADD_MARK_WHITE(0, i, MAIN_DIAGONAL);
    }
    for (int i = 0; i < SIZE - 1; i++)
    {
        ADD_MARK_WHITE(14, i, MAIN_DIAGONAL);
    }
    // SUB DIAGONAL
    for (int j = 0; j < SIZE; j++)
    {
        ADD_MARK_WHITE(0, j, SUB_DIAGONAL);
    }
    for (int j = 1; j < SIZE; j++)
    {
        ADD_MARK_WHITE(14, j, SUB_DIAGONAL);
    }
    
    if (type == BLACKPIECE)
        return mark_b - 0.2 * mark_w;
    return mark_w - 0.2 * mark_b;
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

// 改变棋子类型
// type: BLACKPIECE or WHITEPIECE
int trans_type(int type)
{
    if (type == BLACKPIECE)
        return WHITEPIECE;
    return BLACKPIECE;
}

/**
 * 机器智能进行搜索
 * 对棋盘上某点进行评估的前提：此处为空且此处周围有棋子(使用has_neighbor函数进行判定)
 * para_1, para_2是搜索的顺序参数，在alpha_beta_prune处会有较为详细的解释
 * 因为我们是测试，所以我们要存储最后一次落子的位置，在测试完成后，再进行还原，这样模拟了下面的过程
 * 即落子之后又把子拿走
 * 在进行递归后，进行alpha-beta剪枝，如果需要剪枝，那么直接跳出搜索(goto finish_ai)
 **/
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
/**
 * 机器对对手的落子可能进行搜索
 * 思路与上面的宏函数基本相同
 **/
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
        /**
         * 极大值搜索
         * 此处进行搜索的思路是：以刚下的棋子的位置为中心，一圈一圈地搜索，直到搜索范围超过棋盘边界
         * 宏NOT_ALL_CROSS_BORDER为搜索范围是否超过棋盘边界的判据
         * 使用for循环嵌套宏函数SEARCH_AI即为搜索的过程
         * 首先搜索正方形的上下两条边(棋盘是正方形的)
         * 再搜索正方形的左右两条边
         **/
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
        /**
         * 此处搜索的思路与上面基本相同
         * 不同的是此处为极小值搜索
         **/
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