#ifndef CHECK_FORBIDDEN_MOVES_H_
#define CHECK_FORBIDDEN_MOVES_H_

/********************棋局处理函数，将指定位置棋子处的棋局转化为字符串********************/
// 这些函数都用到了动态内存分配，必须与C库函数free()同时使用
/** 
 * @brief 把点(x, y)处的棋局转化为字符串并返回
 * @param x 指定棋子的x坐标
 * @param y 指定棋子的y坐标
 * @param direction 要获取的棋型字符串的方向
 * -HORIZONTAL 1 水平方向
 * -VERTICAL 2 竖直方向
 * -MAIN_DIAGONAL 3 主对角线方向
 * -SUB_DIAGONAL 4 次对角线
 * @return 返回表示相应棋局的字符串
 * - '0' 空
 * - '1' 黑色棋子
 * - '7' 白色棋子
 **/
char * to_string(int x, int y, int direction);

/**
 * @brief 把点(x, y)处的水平方向棋局转化为字符串并返回
 * @param x 指定棋子的x坐标
 * @param y 指定棋子的y坐标
 * @return 返回相应的字符串
 **/
char * to_string_horizontal(int x, int y);

/**
 * @brief 把点(x, y)处的竖直方向棋局转化为字符串并返回
 * @param x 指定棋子的x坐标
 * @param y 指定棋子的y坐标
 * @return 返回相应的字符串
 **/
char * to_string_vertical(int x, int y);

/**
 * @brief 把点(x, y)处的主对角线方向棋局转化为字符串并返回
 * @param x 指定棋子的x坐标
 * @param y 指定棋子的y坐标
 * @return 返回相应的字符串
 **/
char * to_string_main_diagonal(int x, int y);

/**
 * @brief 把点(x, y)处的次对角线方向棋局转化为字符串并返回
 * @param x 指定棋子的x坐标
 * @param y 指定棋子的y坐标
 * @return 返回相应的字符串
 **/
char * to_string_sub_diagonal(int x, int y);
/****************************************/


/********************字符串处理函数********************/
/**
 * @brief 暴力匹配字符串
 * @param str_s 二者中相对较短的字符串
 * @param str_l 二者中相对较长的字符串
 * @return 若匹配成功返回匹配成功的次数, 若匹配失败或者str_s长度大于str_l返回0
 **/
int str_match(char * str_s, char * str_l);

/**
 * @brief 在长字符串的两侧暴力匹配字符串，处理棋型处于棋盘边界的情况
 * @param str_s 二者中相对较短的字符串
 * @param str_l 二者中相对较长的字符串
 * @return 若匹配成功返回匹配成功的次数, 若匹配失败或者str_s长度大于str_l返回0
 **/
int str_match_side(char * str_s, char * str_l);

/**
 * @brief 将字符串反序
 * @param str 将要被反序的字符串
 * @return 反序后的字符串
 **/
char * str_reverse(char * str);
/****************************************/

/********************统计指定棋子周围特定棋型的数目********************/
// 更详细的棋型，见'constants.h'

/**
 * @brief 统计指定黑色棋子周围'死二'的数目
 * @param x 指定棋子的x坐标
 * @param y 指定棋子的y坐标
 * @return 指定黑色棋子周围'死二'的数目
 **/
int num_dead_two_black(int x, int y);

/**
 * @brief 统计指定白色棋子周围'死二'的数目
 * @param x 指定棋子的x坐标
 * @param y 指定棋子的y坐标
 * @return 指定白色棋子周围'死二'的数目
 **/
int num_dead_two_white(int x, int y);

/**
 * @brief 统计指定黑色棋子周围'活二'的数目
 * @param x 指定棋子的x坐标
 * @param y 指定棋子的y坐标
 * @return 指定黑色棋子周围'活二'的数目
 **/
int num_active_two_black(int x, int y);

/**
 * @brief 统计指定白色棋子周围'活二'的数目
 * @param x 指定棋子的x坐标
 * @param y 指定棋子的y坐标
 * @return 指定白色棋子周围'活二'的数目
 **/
int num_active_two_white(int x, int y);

/**
 * @brief 统计指定黑色棋子周围'死三'的数目
 * @param x 指定棋子的x坐标
 * @param y 指定棋子的y坐标
 * @return 指定黑色棋子周围'死三'的数目
 **/
int num_dead_three_black(int x, int y);

/**
 * @brief 统计指定白色棋子周围'死三'的数目
 * @param x 指定棋子的x坐标
 * @param y 指定棋子的y坐标
 * @return 指定白色棋子周围'死三'的数目
 **/
int num_dead_three_white(int x, int y);

/**
 * @brief 统计指定黑色棋子周围'活三'的数目
 * @param x 指定棋子的x坐标
 * @param y 指定棋子的y坐标
 * @return 指定黑色棋子周围'活三'的数目
 **/
int num_active_three_black(int x, int y);

/**
 * @brief 统计指定白色棋子周围'活三'的数目
 * @param x 指定棋子的x坐标
 * @param y 指定棋子的y坐标
 * @return 指定白色棋子周围'活三'的数目
 **/
int num_active_three_white(int x, int y);

/**
 * @brief 统计指定黑色棋子周围'活四'的数目
 * @param x 指定棋子的x坐标
 * @param y 指定棋子的y坐标
 * @return 指定黑色棋子周围'活四'的数目
 **/
int num_active_four_black(int x, int y);

/**
 * @brief 统计指定白色棋子周围'活四'的数目
 * @param x 指定棋子的x坐标
 * @param y 指定棋子的y坐标
 * @return 指定白色棋子周围'活四'的数目
 **/
int num_active_four_white(int x, int y);

/**
 * @brief 统计指定黑色棋子周围'死四'的数目
 * @param x 指定棋子的x坐标
 * @param y 指定棋子的y坐标
 * @return 指定黑色棋子周围'死四'的数目
 **/
int num_dead_four_black(int x, int y);

/**
 * @brief 统计指定白色棋子周围'死四'的数目
 * @param x 指定棋子的x坐标
 * @param y 指定棋子的y坐标
 * @return 指定白色棋子周围'死四'的数目
 **/
int num_dead_four_white(int x, int y);

/**
 * @brief 统计指定黑色棋子周围'长连'的数目
 * @param x 指定棋子的x坐标
 * @param y 指定棋子的y坐标
 * @return 指定黑色棋子周围'长连'的数目
 **/
int num_overline(int x, int y);

/**
 * @brief 判断指定黑色棋子周围是否形成五连
 * @param x 指定棋子的x坐标
 * @param y 指定棋子的y坐标
 * @return 若形成五连返回1,否则返回0
 **/
int is_five_black(int x, int y);

/**
 * @brief 判断指定白色棋子周围是否形成五连
 * @param x 指定棋子的x坐标
 * @param y 指定棋子的y坐标
 * @return 若形成五连返回1,否则返回0
 **/
int is_five_white(int x, int y);

#endif
