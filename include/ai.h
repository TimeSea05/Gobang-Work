#ifndef AI_H_
#define AI_H_

#define NEGATIVE_MAX(x, y) \
if (latest_x + x >= 0 && latest_y + y < SIZE \
    && record_board[latest_x + x][latest_y + y] == EMPTY \
    && has_neighbor(latest_x + x, latest_y + y)) \
{   \
    int latest_x_copy = latest_x, latest_y_copy = latest_y; \
    latest_x = latest_x + x, latest_y = latest_y + y; \
    record_board[latest_x][latest_y] = type; \
    int value = -negative_max(trans_type(type), depth - 1, -beta, -alpha); \
    record_board[latest_x][latest_y] = EMPTY; \
    latest_x = latest_x_copy, latest_y = latest_y_copy; \
    if (value > alpha) \
    { \
        alpha = value; \
        if (depth == DEPTH) \
            next_point_x = latest_x, next_point_y = latest_y; \
        if (value >= beta) \
            return beta; \
        alpha = value; \
    } \
} \

int calculate_mark(int x, int y, int type);
int evaluate(int x, int y, int type);
int is_forbidden(int x, int y);
int has_neighbor(int x, int y);
int negative_max(int type, int depth, int alpha, int beta);
#endif