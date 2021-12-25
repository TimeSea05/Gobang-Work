#include <stdio.h>
#include "game.h"
#include "game_func.h"
#include "ai.h"
#include "constants.h"

extern int latest_x, latest_y;
extern int record_board[SIZE][SIZE];
extern int next_point_x, next_point_y;

extern int leftest, rightest;
extern int uppest, downest;
extern int md_leftest_up, md_rightest_up, md_leftest_down, md_rightest_down;
extern int sd_leftest_up, sd_rightest_up, sd_leftest_down, sd_rightest_down;

extern int pos_x_arr[SIZE * SIZE], pos_y_arr[SIZE * SIZE];
extern int p_pos_arr;
extern int prune_times;

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
#define ADD_MARK_BLACK(pos_x, pos_y, direction) \
    mark_b += num_dead_two_black(pos_x, pos_y, direction) * DEAD_TWO;\
    mark_b += num_active_two_black(pos_x, pos_y, direction) * ACTIVE_TWO;\
    mark_b += num_dead_three_black(pos_x, pos_y, direction) * DEAD_THREE;\
    mark_b += num_active_three_black(pos_x, pos_y, direction) * ACTIVE_THREE; \
    mark_b += num_dead_four_black(pos_x, pos_y, direction) * DEAD_FOUR;\
    mark_b += num_active_four_black(pos_x, pos_y, direction) * ACTIVE_FOUR;\
    mark_b += is_five_black(pos_x, pos_y, direction) * FIVE;

// 计算白棋得分
#define ADD_MARK_WHITE(pos_x, pos_y, direction) \
    mark_w += num_dead_two_white(pos_x, pos_y, direction) * DEAD_TWO;\
    mark_w += num_active_two_white(pos_x, pos_y, direction) * ACTIVE_TWO;\
    mark_w += num_dead_three_white(pos_x, pos_y, direction) * DEAD_THREE;\
    mark_w += num_active_three_white(pos_x, pos_y, direction) * ACTIVE_THREE;\
    mark_w += num_dead_four_white(pos_x, pos_y, direction) * DEAD_FOUR;\
    mark_w += num_active_four_white(pos_x, pos_y, direction) * ACTIVE_FOUR;\
    mark_w += is_five_white(pos_x, pos_y, direction) * FIVE;

int calculate_mark(int type, double ratio)
{
    int mark_b = 0, mark_w = 0;

    /*******************计算黑棋和白棋得分*******************/
    // HORIZONTAL
    for (int i = 0; i < SIZE; i++)
    {
        ADD_MARK_BLACK(i, 0, HORIZONTAL);
        ADD_MARK_WHITE(i, 0, HORIZONTAL);
    }
    // VERTICAL
    for (int j = 0; j < SIZE; j++)
    {
        ADD_MARK_BLACK(0, j, VERTICAL);
        ADD_MARK_WHITE(0, j, VERTICAL);
    }
    // MAIN DIAGONAL
    for (int i = 0; i < SIZE; i++)
    {
        ADD_MARK_BLACK(0, i, MAIN_DIAGONAL);
        ADD_MARK_WHITE(0, i, MAIN_DIAGONAL);
    }
    for (int i = 0; i < SIZE - 1; i++)
    {
        ADD_MARK_BLACK(14, i, MAIN_DIAGONAL);
        ADD_MARK_WHITE(14, i, MAIN_DIAGONAL);
    }
    // SUB DIAGONAL
    for (int j = 0; j < SIZE; j++)
    {
        ADD_MARK_BLACK(0, j, SUB_DIAGONAL);
        ADD_MARK_WHITE(0, j, SUB_DIAGONAL);
    }
    for (int j = 0; j < SIZE - 1; j++)
    {
        ADD_MARK_BLACK(14, j, SUB_DIAGONAL);
        ADD_MARK_WHITE(14, j, SUB_DIAGONAL);
    }
    mark_b += is_forbidden() * FORBIDDEN;
    
    if (type == BLACKPIECE)
        return mark_b - ratio * mark_w;
    return mark_w - ratio * mark_b;
}


int has_neighbor(int x, int y)
{
    // 上下左右 左上 右上 左下 右下 共8个方向
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
        {
            // 排除棋子自己的位置
            if (i == 0 && j == 0)
                continue;
            // 忽略越界情况
            if (x + i < 0 || x + i >= SIZE || y + j < 0 || y + j >= SIZE)
                continue;
            if (!record_board[x + i][y + j] == EMPTY)
                return 1;
        }
    return 0;
}

// 改变棋子类型
// type: BLACKPIECE or WHITEPIECE
int change_type(int type)
{
    if (type == BLACKPIECE)
        return WHITEPIECE;
    return BLACKPIECE;
}

/**
 * 机器智能进行搜索
 * 对棋盘上某点进行评估的前提：此处为空且此处周围有棋子(使用has_neighbor函数进行判定)
 * pos_x, pos_y是搜索的位置，在min_max_search处会有较为详细的解释
 * 因为我们是测试，所以我们要存储最后一次落子的位置，在测试完成后，再进行还原，这样模拟了下面的过程
 * 即落子之后又把子拿走
 * 在进行递归后，进行alpha-beta剪枝，如果需要剪枝，那么直接跳出搜索(goto finish_ai)
 **/
#define SEARCH_AI(pos_x, pos_y) \
    if (record_board[latest_x + (pos_x)][latest_y + (pos_y)] == EMPTY \
        && has_neighbor(latest_x + (pos_x), latest_y + (pos_y))) \
    { \
        int latest_x_copy = latest_x, latest_y_copy = latest_y; \
        latest_x = latest_x + (pos_x), latest_y = latest_y + (pos_y); \
        p_pos_arr++; \
		pos_x_arr[p_pos_arr] = latest_x, pos_y_arr[p_pos_arr] = latest_y; \
        record_board[latest_x][latest_y] = type; \
        update_border(); \
        int val = min_max_search(depth - 1, !is_ai, alpha, beta, change_type(type), ratio); \
        record_board[latest_x][latest_y] = EMPTY; \
        p_pos_arr--; \
        reset_border(); \
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
#define SEARCH_NOT_AI(pos_x, pos_y) \
    if (record_board[latest_x + (pos_x)][latest_y + (pos_y)] == EMPTY \
        && has_neighbor(latest_x + (pos_x), latest_y + (pos_y))) \
    { \
        int latest_x_copy = latest_x, latest_y_copy = latest_y; \
        latest_x = latest_x + (pos_x), latest_y = latest_y + (pos_y); \
        p_pos_arr++; \
		pos_x_arr[p_pos_arr] = latest_x, pos_y_arr[p_pos_arr] = latest_y; \
        record_board[latest_x][latest_y] = type; \
        update_border(); \
        int val = min_max_search(depth - 1, !is_ai, alpha, beta, change_type(type), ratio); \
        p_pos_arr--; \
        reset_border(); \
        record_board[latest_x][latest_y] = EMPTY; \
        if (val < beta) \
        { \
            beta = val; \
        } \
        latest_x = latest_x_copy, latest_y = latest_y_copy; \
        if (alpha > beta) \
            goto finish_not_ai; \
    }


int min_max_search(int depth, int is_ai, int alpha, int beta, int type, double ratio)
{
    if (depth == 0)
        return calculate_mark(type, ratio);
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
            prune_times++;
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
            prune_times++;
            return beta;
    }
}