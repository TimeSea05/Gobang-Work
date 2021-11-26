#ifndef CHESS_TYPE_H_
#define CHESS_TYPE_H_

// s 代表"对称"，就是把整个字符串对称化，用来解决重复计数的问题
// e 代表"边缘"，用来处理棋型在棋盘边缘时的情况
/* 
   对于一些棋型，我们没有必要对其进行对称化，因为对称化后的棋型在对战中几乎不出现，
   因此没有必要对其进行对称化
*/

// 黑棋死二
char dead_two_B_1[] = "7110\0";
char s_dead_two_B_1[] = "7110117\0";
char dead_two_B_2[] = "7101\0";
char s_dead_two_B_2[] = "71017\0";
char e_dead_two_B_4[] = "110\0";

// 白棋死二
char dead_two_W_1[] = "1770\0";
char s_dead_two_W_1[] = "1770771\0";
char dead_two_W_2[] = "1707\0";
char s_dead_two_W_2[] = "17071\0";
char e_dead_two_W_4[] = "770\0";

// 黑棋活二
char active_two_B_1[] = "0110\0";
char active_two_B_2[] = "01010\0";

// 白棋活二
char active_two_W_1[] = "0770\0";
char active_two_W_2[] = "07070\0";

// 黑棋死三
char dead_three_B_1[] = "11001\0";
char s_dead_three_B_1[] = "110011\0";
char dead_three_B_3[] = "7011107\0";
char dead_three_B_4[] = "711100\0";
char dead_three_B_5[] = "711010\0";
char dead_three_B_6[] = "710110\0";
char e_dead_three_B_7[] = "1110\0";

// 白棋死三
char dead_three_W_1[] = "77007\0";
char s_dead_three_W_1[] = "770077\0";
char dead_three_W_3[] = "1077701\0";
char dead_three_W_4[] = "177700\0";
char dead_three_W_5[] = "177070\0";
char dead_three_W_6[] = "170770\0";
char e_dead_three_W_7[] = "7770\0";

// 黑棋活三
char active_three_B_1[] = "011100\0";
char s_active_three_B_1[] = "0011100\0";
char active_three_B_2[] = "011010\0";
char s_active_three_B_2[] = "01011010\0";

// 白棋活三
char active_three_W_1[] = "077700\0";
char s_active_three_W_1[] = "0077700\0";
char active_three_W_2[] = "077070\0";
char s_active_three_W_2[] = "07077070\0";

// 黑棋死四
char dead_four_B_1[] = "11011\0";
char dead_four_B_2[] = "11101\0";
char s_dead_four_B_2[] = "1011101\0";
char dead_four_B_3[] = "711110\0";
char e_dead_four_B_6[] = "11110\0";

// 白棋死四
char dead_four_W_1[] = "77077\0";
char dead_four_W_2[] = "77707\0";
char s_dead_four_W_2[] = "7770777\0";
char dead_four_W_3[] = "177770\0";
char e_dead_four_W_6[] = "11110\0";

// 黑棋活四
char active_four_B[] = "011110\0";

// 白棋活四
char active_four_W[] = "077770\0";

// 黑棋五连
char five_B[] = "11111\0";

// 白棋五连
char five_W[] = "77777\0";

// 黑棋长连
char five_forbidden[] = "111111\0";
#endif