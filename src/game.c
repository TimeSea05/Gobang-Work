#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "game.h"
#include "chess_type.h"
#include "constants.h"

extern int record_board[SIZE][SIZE];

void to_string_horizontal(char string_h[], int x, int y)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (record_board[x][i] == EMPTY)
            string_h[i] = '0';
        else if (record_board[x][i] == BLACKPIECE || record_board[x][i] == BLACKTRIANGLE)
            string_h[i] = '1';
        else if (record_board[x][i] == WHITEPIECE || record_board[x][i] == WHITETRIANGLE)
            string_h[i] = '7';
    }
    string_h[SIZE] = '\0';
    y++; // useless statement to avoid warnings from the complier
}
void to_string_vertical(char string_v[], int x, int y)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (record_board[i][y] == EMPTY)
            string_v[i] = '0';
        else if (record_board[i][y] == BLACKPIECE || record_board[i][y] == BLACKTRIANGLE)
            string_v[i] = '1';
        else if (record_board[i][y] == WHITEPIECE || record_board[i][y] == WHITETRIANGLE)
            string_v[i] = '7';
    }
    string_v[SIZE] = '\0';
    x++; // useless statement to avoid warnings from the complier
}
void to_string_main_diagonal(char string_md[], int x, int y)
{
    int length = 15 - abs(x - y);
    if (x < y)
        for (int i = 0; i < length; i++)
        {
            if (record_board[i][y - x + i] == EMPTY)
                string_md[i] = '0';
            else if (record_board[i][y - x + i] == BLACKPIECE || record_board[i][y - x + i] == BLACKTRIANGLE)
                string_md[i] = '1';
            else if (record_board[i][y - x + i] == WHITEPIECE || record_board[i][y - x + i] == WHITETRIANGLE)
                string_md[i] = '7';
        }
    else
        for (int i = 0; i < length; i++)
        {
            if (record_board[x - y + i][i] == EMPTY)
                string_md[i] = '0';
            else if (record_board[x - y + i][i] == BLACKPIECE || record_board[x - y + i][i] == BLACKTRIANGLE)
                string_md[i] = '1';
            else if (record_board[x - y + i][i] == WHITEPIECE || record_board[x - y + i][i] == WHITETRIANGLE)
                string_md[i] = '7';
        }
    string_md[length] = '\0';
}
void to_string_sub_diagonal(char string_sd[], int x, int y)
{
    int length;
    if (x + y < 15)
    {
        length = x + y + 1;
        for (int i = 0; i < length; i++)
        {
            if (record_board[length - 1 - i][i] == EMPTY)
                string_sd[i] = '0';
            else if (record_board[length - 1 - i][i] == BLACKPIECE || record_board[length - 1 - i][i] == BLACKTRIANGLE)
                string_sd[i] = '1';
            else if (record_board[length - 1 - i][i] == WHITEPIECE || record_board[length - 1 - i][i] == WHITETRIANGLE)
                string_sd[i] = '7';
        }
        string_sd[length] = '\0';
    }
    else
    {
        length = (15 - x) + (15 - y) - 1;
        for (int i = 0; i < length; i++)
        {
            if (record_board[SIZE - 1 - i][x + y + 1 - SIZE + i] == EMPTY)
                string_sd[i] = '0';
            else if (record_board[SIZE - 1 - i][x + y + 1 - SIZE + i] == BLACKPIECE || record_board[SIZE - 1 - i][x + y + 1 - SIZE + i] == BLACKTRIANGLE)
                string_sd[i] = '1';
            else if (record_board[SIZE - 1 - i][x + y + 1 - SIZE + i] == WHITEPIECE || record_board[SIZE - 1 - i][x + y + 1 - SIZE + i] == WHITETRIANGLE)
                string_sd[i] = '7';
        }
        string_sd[length] = '\0';
    }
}
void to_string(char str[], int x, int y, int direction)
{
    switch (direction)
    {
    case HORIZONTAL:
        to_string_horizontal(str, x, y);
        break;
    case VERTICAL:
        to_string_vertical(str, x, y);
        break;
    case MAIN_DIAGONAL:
        to_string_main_diagonal(str, x, y);
        break;
    case SUB_DIAGONAL:
        to_string_sub_diagonal(str, x, y);
        break;
    default:
        ;
    }
}

void str_reverse(char str[])
{
    int c, i, j;
    for (i = 0, j = strlen(str)-1; i < j; i++, j--) 
    {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
}
int str_match(char* str_s, char* str_l)
{
    size_t len_str_s = strlen(str_s);
    if (len_str_s > strlen(str_l))
        return 0;

    int res = 0;
    while (strlen(str_l) >= len_str_s)
    {
        char* p_str = strstr(str_l, str_s);
        if (p_str == NULL)
            return res;
        else
        {
            res++;
            str_l = p_str + len_str_s;
        }
    }
    return res;
}
int str_match_side(char* str_s, char* str_l)
{
    int len_str_s = strlen(str_s), len_str_l = strlen(str_l);
    if (len_str_s > len_str_l)
        return 0;

    int res = 0;
    // 棋盘一侧
    int i;
    for (i = 0; i < len_str_s; i++)
        if (!(str_s[i] == str_l[i]))
            break;
    if (i == len_str_s)
        res++;
    // 棋盘另一侧
    for (i = 0; i < len_str_s; i++)
        if (!(str_s[i] == str_l[len_str_l - 1 - i]))
            break;
    if (i == len_str_s)
        res++;

    return res;
}

int num_dead_two_black(int x, int y, int direction)
{
    int res = 0;
    char str[16];
    to_string(str, x, y, direction);

    res += str_match(dead_two_B_1, str);
    res += str_match(dead_two_B_2, str);
    str_reverse(dead_two_B_1);
    str_reverse(dead_two_B_2);
    res += str_match(dead_two_B_1, str);
    res += str_match(dead_two_B_2, str);

    // 将原来的字符串还原
    str_reverse(dead_two_B_1);
    str_reverse(dead_two_B_2);

    res -= str_match(s_dead_two_B_1, str);
    res -= str_match(s_dead_two_B_2, str);

    res += str_match_side(e_dead_two_B_4, str);

    return res;
}
int num_dead_two_white(int x, int y, int direction)
{
    int res = 0;
    char str[16];
    to_string(str, x, y, direction);

    res += str_match(dead_two_W_1, str);
    res += str_match(dead_two_W_2, str);

    str_reverse(dead_two_W_1);
    str_reverse(dead_two_W_2);
    res += str_match(dead_two_W_1, str);
    res += str_match(dead_two_W_2, str);
    str_reverse(dead_two_W_1);
    str_reverse(dead_two_W_2);

    res -= str_match(s_dead_two_W_1, str);
    res -= str_match(s_dead_two_W_2, str);

    res += str_match_side(e_dead_two_W_4, str);

    return res;
}
int num_active_two_black(int x, int y, int direction)
{
    int res = 0;
    char str[16];
    to_string(str, x, y, direction);
    res += str_match(active_two_B_1, str);
    res += str_match(active_two_B_2, str);
    return res;
}
int num_active_two_white(int x, int y, int direction)
{
    int res = 0;
    char str[16];
    to_string(str, x, y, direction);
    res += str_match(active_two_W_1, str);
    res += str_match(active_two_W_2, str);
    return res;
}
int num_dead_three_black(int x, int y, int direction)
{
    int res = 0;
    char str[16];
    to_string(str, x, y, direction);

    res += str_match(dead_three_B_1, str);
    res += str_match(dead_three_B_3, str);
    res += str_match(dead_three_B_4, str);
    res += str_match(dead_three_B_5, str);
    res += str_match(dead_three_B_6, str);

    // reverse
    str_reverse(dead_three_B_1);
    str_reverse(dead_three_B_4);
    str_reverse(dead_three_B_5);
    str_reverse(dead_three_B_6);

    res += str_match(dead_three_B_1, str);
    res += str_match(dead_three_B_4, str);
    res += str_match(dead_three_B_5, str);
    res += str_match(dead_three_B_6, str);

    str_reverse(dead_three_B_1);
    str_reverse(dead_three_B_4);
    str_reverse(dead_three_B_5);
    str_reverse(dead_three_B_6);    

    // symmetry
    res -= str_match(s_dead_three_B_1, str);
    res += str_match_side(e_dead_three_B_7, str);

    return res;
}
int num_dead_three_white(int x, int y, int direction)
{
    int res = 0;
    char str[16];
    to_string(str, x, y, direction);

    res += str_match(dead_three_W_1, str);
    res += str_match(dead_three_W_3, str);
    res += str_match(dead_three_W_4, str);
    res += str_match(dead_three_W_5, str);
    res += str_match(dead_three_W_6, str);

    // reverse
    str_reverse(dead_three_W_1);
    str_reverse(dead_three_W_4);
    str_reverse(dead_three_W_5);
    str_reverse(dead_three_W_6);

    res += str_match(dead_three_W_1, str);
    res += str_match(dead_three_W_4, str);
    res += str_match(dead_three_W_5, str);
    res += str_match(dead_three_W_6, str);

    str_reverse(dead_three_W_1);
    str_reverse(dead_three_W_4);
    str_reverse(dead_three_W_5);
    str_reverse(dead_three_W_6);

    // symmetry
    res -= str_match(s_dead_three_W_1, str);

    res += str_match_side(e_dead_three_W_7, str);

    return res;
}
int num_active_three_black(int x, int y, int direction)
{
    int res = 0;
    char str[16];
    to_string(str, x, y, direction);
        
    res += str_match(active_three_B_1, str);
    res += str_match(active_three_B_2, str);

    // reverse
    str_reverse(active_three_B_1);
    str_reverse(active_three_B_2);
    res += str_match(active_three_B_1, str);
    res += str_match(active_three_B_2, str);
    str_reverse(active_three_B_1);
    str_reverse(active_three_B_2);

    // symmetry
    res -= str_match(s_active_three_B_1, str);
    res -= str_match(s_active_three_B_2, str);

    return res;
}
int num_active_three_white(int x, int y, int direction)
{
    int res = 0;
    char str[16];
    to_string(str, x, y, direction);

    res += str_match(active_three_W_1, str);
    res += str_match(active_three_W_2, str);

    // reverse
    str_reverse(active_three_W_1);
    str_reverse(active_three_W_2);

    res += str_match(active_three_W_1, str);
    res += str_match(active_three_W_2, str);

    str_reverse(active_three_W_1);
    str_reverse(active_three_W_2);

    // symmetry
    res -= str_match(s_active_three_W_1, str);
    res -= str_match(s_active_three_W_2, str);

    return res;
}
int num_active_four_black(int x, int y, int direction)
{
    int res = 0;
    char str[16];
    to_string(str, x, y, direction);
    res += str_match(active_four_B, str);
    return res;
}
int num_active_four_white(int x, int y, int direction)
{
    int res = 0;
    char str[16];
    to_string(str, x, y, direction);

    res += str_match(active_four_W, str);
    return res;
}
int num_dead_four_black(int x, int y, int direction)
{
    int res = 0;
    char str[16];
    to_string(str, x, y, direction);

    res += str_match(dead_four_B_1, str);
    res += str_match(dead_four_B_2, str);
    res += str_match(dead_four_B_3, str);

    // reverse
    str_reverse(dead_four_B_2);
    res += str_match(dead_four_B_2, str);
    res += str_match(dead_four_B_3, str);

    str_reverse(dead_four_B_2);

    // symmetry
    res -= str_match(s_dead_four_B_2, str);
    res += str_match_side(e_dead_four_B_6, str);

    return res;
}
int num_dead_four_white(int x, int y, int direction)
{
    int res = 0;
    char str[16];
    to_string(str, x, y, direction);

    res += str_match(dead_four_W_1, str);
    res += str_match(dead_four_W_2, str);
    res += str_match(dead_four_W_3, str);

    // reverse
    str_reverse(dead_four_W_1);
    str_reverse(dead_four_W_2);
    str_reverse(dead_four_W_3);

    res += str_match(dead_four_W_1, str);
    res += str_match(dead_four_W_2, str);
    res += str_match(dead_four_W_3, str);

    str_reverse(dead_four_W_1);
    str_reverse(dead_four_W_2);
    str_reverse(dead_four_W_3);

    // symmetry
    res -= str_match(s_dead_four_W_2, str);

    res += str_match_side(e_dead_three_W_7, str);

    return res;
}
int is_five_black(int x, int y, int direction)
{
    char str[16];
    to_string(str, x, y, direction);
    if (str_match(five_forbidden, str))
        return 0;  // 触发禁手
    if (str_match(five_B, str))
        return 1;
    return 0;
}
int is_five_white(int x, int y, int direction)
{
    char str[16];
    to_string(str, x, y, direction);
    if (str_match(five_W, str))
        return 1;
    return 0;
}
int num_overline(int x, int y, int direction)
{
    int res = 0;
    char str[16];
    to_string(str, x, y, direction);
    res += str_match(five_forbidden, str);
    return res;
}
int num_special_forbiddens(int x, int y, int direction)
{
    int res = 0;
    char str[16];
    to_string(str, x, y, direction);
    res += str_match(forbidden_1, str);
    res += str_match(forbidden_2, str);
    res += str_match(forbidden_3, str);
    return res;
}