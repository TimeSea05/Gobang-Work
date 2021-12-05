#ifndef AI_H_
#define AI_H_

// 计分函数
// @param type 棋子的种类
int calculate_mark(int type);

// 判断指定位置周围有无棋子
// @param x x坐标 
// @param y y坐标
int has_neighbor(int x, int y);

/**
 * @brief 搜索算法 主要采用极大极小值算法与alpha-beta剪枝算法
 * @param depth 搜索的深度 只能为奇数
 * @param is_ai 判断是否为AI决策
 * @param alpha 搜索上界
 * @param beta  搜索下界
 * @param type 棋子的种类
 **/
int alpha_beta_prune(int depth, int is_ai, int alpha, int beta, int type);

#endif