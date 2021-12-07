#ifndef CHECK_FORBIDDEN_MOVES_H_
#define CHECK_FORBIDDEN_MOVES_H_

/********************棋局处理函数，将指定位置棋子处的棋局转化为字符串********************/
/** 
 * @param x 指定棋子的x坐标
 * @param y 指定棋子的y坐标
 * @param direction 要获取的棋型字符串的方向
 * -HORIZONTAL 1 水平方向
 * -VERTICAL 2 竖直方向
 * -MAIN_DIAGONAL 3 主对角线方向
 * -SUB_DIAGONAL 4 次对角线
 **/

// 把点(x, y)处的棋局转化为字符串
void to_string(char str[], int x, int y, int direction);

// 把点(x, y)处的水平方向(横向)棋局转化为字符串
void to_string_horizontal(char string_h[], int x, int y);

// 把点(x, y)处的竖直方向(纵向)棋局转化为字符串
void to_string_vertical(char string_v[], int x, int y);

// 把点(x, y)处的主对角线方向棋局转化为字符串
void to_string_main_diagonal(char string_md[], int x, int y);

// 把点(x, y)处的次对角线方向棋局转化为字符串
void to_string_sub_diagonal(char string_sd[], int x, int y);
/****************************************/


/********************字符串处理函数********************/
/**
 * @param str_s 二者中相对较短的字符串
 * @param str_l 二者中相对较长的字符串
 * @return 若匹配成功返回匹配成功的次数, 若匹配失败或者str_s长度大于str_l返回0
 **/

// 暴力匹配字符串
int str_match(char * str_s, char * str_l);

// 在长字符串的两侧暴力匹配字符串，处理棋型处于棋盘边界的情况
int str_match_side(char * str_s, char * str_l);

// 将字符串反序
void str_reverse(char * str);
/****************************************/

/********************统计指定棋子指定方向特定棋型的数目********************/
// 更详细的棋型说明，见'constants.h'

/**
 * @param x 指定棋子的x坐标
 * @param y 指定棋子的y坐标
 * @param direction 对指定棋子的某个方向进行分析
 * @return 指定棋子 指定方向 指定棋型的数目
 **/

// 统计指定黑色棋子指定方向'死二'的数目
int num_dead_two_black(int x, int y, int direction);

// 统计指定白色棋子指定方向'死二'的数目
int num_dead_two_white(int x, int y, int direction);

// 统计指定黑色棋子指定方向'活二'的数目
int num_active_two_black(int x, int y, int direction);

// 统计指定白色棋子指定方向'活二'的数目
int num_active_two_white(int x, int y, int direction);

// 统计指定黑色棋子指定方向'死三'的数目
int num_dead_three_black(int x, int y, int direction);

// 统计指定白色棋子指定方向'死三'的数目
int num_dead_three_white(int x, int y, int direction);

// 统计指定黑色棋子指定方向'活三'的数目
int num_active_three_black(int x, int y, int direction);

// 统计指定白色棋子指定方向'活三'的数目
int num_active_three_white(int x, int y, int direction);

// 统计指定黑色棋子指定方向'死四'的数目
int num_dead_four_black(int x, int y, int direction);

// 统计指定白色棋子指定方向'死四'的数目
int num_dead_four_white(int x, int y, int direction);

// 统计指定黑色棋子指定方向'活四'的数目
int num_active_four_black(int x, int y, int direction);

// 统计指定白色棋子指定方向'活四'的数目
int num_active_four_white(int x, int y, int direction);

// 统计指定黑色棋子指定方向'长连'的数目
int num_overline(int x, int y, int direction);

// @brief 判断指定黑色棋子指定方向是否形成五连
// @return 若形成五连返回1,否则返回0
int is_five_black(int x, int y, int direction);

// @brief 判断指定白色棋子指定方向是否形成五连
// @return 若形成五连返回1,否则返回0
int is_five_white(int x, int y, int direction);

#endif