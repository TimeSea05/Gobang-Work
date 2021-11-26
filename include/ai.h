#ifndef AI_H_
#define AI_H_

int calculate_mark(int type);
int evaluate(int x, int y, int type);

int has_neighbor(int x, int y);
int negative_max(int type, int depth, int alpha, int beta);

#endif