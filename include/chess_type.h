#ifndef CHESS_TYPE_H_
#define CHESS_TYPE_H_

// s represents 'symmetry'
/* 
   for some of the cases, there is no need to give a corresponding symmetrical case
   because that will cause the string to be too long
   and that case rarely happens
*/

// dead two black
char dead_two_B_1[] = "7110\0";
char s_dead_two_B_1[] = "7110117\0";
char dead_two_B_2[] = "7101\0";
char s_dead_two_B_2[] = "71017\0";
char dead_two_B_3[] = "710010\0";

// dead two white
char dead_two_W_1[] = "1770\0";
char s_dead_two_W_1[] = "1770771\0";
char dead_two_W_2[] = "1707\0";
char s_dead_two_W_2[] = "17071\0";
char dead_two_W_3[] = "170070\0";

// active two black
char active_two_B_1[] = "0110\0";
char active_two_B_2[] = "01010\0";

// active two white
char active_two_W_1[] = "0770\0";
char active_two_W_2[] = "07070\0";

// dead three black
char dead_three_B_1[] = "11001\0";
char s_dead_three_B_1[] = "110011\0";
char s_dead_three_B_1_a[] = "10011001\0";

char dead_three_B_2[] = "10101\0";
char dead_three_B_3[] = "7011107\0";
char dead_three_B_4[] = "711100\0";
char dead_three_B_5[] = "711010\0";
char dead_three_B_6[] = "710110\0";

// dead three white
char dead_three_W_1[] = "77007\0";
char s_dead_three_W_1[] = "770077\0";
char s_dead_three_W_1_a[] = "70077007\0";

char dead_three_W_2[] = "70707\0";
char dead_three_W_3[] = "1077701\0";
char dead_three_W_4[] = "177700\0";
char dead_three_W_5[] = "177070\0";
char dead_three_W_6[] = "170770\0";

// active three black
char active_three_B_1[] = "011100\0";
char s_active_three_B_1[] = "0011100\0";
char active_three_forbidden_1[] = "0111001\0";
char s_active_three_forbidden_1[] = "100111001\0";
char active_three_forbidden_2[] = "1011100\0";

char active_three_B_2[] = "011010\0";
char s_active_three_B_2[] = "01011010\0";
char active_three_forbidden_3[] = "1011010\0";
char s_active_three_forbidden_3[] = "01011010\0";
char active_three_forbidden_4[] = "0110101\0";
char s_active_three_forbidden_4[] = "1010110101\0";

// active three white
char active_three_W_1[] = "077700\0";
char s_active_three_W_1[] = "0077700\0";
char active_three_W_2[] = "077070\0";
char s_active_three_W_2[] = "07077070\0";

// active four black
char active_four_B[] = "011110\0";
char active_four_forbidden[] = "1011110\0";
char s_active_four_forbidden[] = "10111101\0";

// active four white
char active_four_W[] = "077770\0";

// dead four black
char dead_four_B_1[] = "11011\0";
char dead_four_forbidden_1[] = "111011\0";
char s_dead_four_forbidden_1[] = "1110111\0";
char s_dead_four_forbidden_1_a[] = "110111011\0";

char dead_four_B_2[] = "11101\0";
char s_dead_four_B_2[] = "1011101\0";
char s_dead_four_B_2_a[] = "1110111\0";

char dead_four_forbidden_2[] = "111101";
char s_dead_four_forbidden_2[] = "10111101\0";
char s_dead_four_forbidden_2_a[] = "111101111\0";

char dead_four_forbidden_3[] = "111011";
char s_dead_four_forbidden_3[] = "110111011\0";
char s_dead_four_forbidden_3_a[] = "1110111\0";

char dead_four_B_3[] = "711110\0";
char dead_four_forbidden_4[] = "7111101\0";

char dead_four_B_4[] = "10111100\0";
char dead_four_B_5[] = "10111107\0";

// dead four white
char dead_four_W_1[] = "77077\0";
char dead_four_W_2[] = "77707\0";
char s_dead_four_W_2[] = "7770777\0";
char dead_four_W_3[] = "177770\0";

// five
char five_B[] = "11111\0";
char five_forbidden[] = "111111\0";

char five_W[] = "77777\0";


#endif