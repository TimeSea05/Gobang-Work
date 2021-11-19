#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "game.h"
#include "chess_type.h"
#include "constants.h"

extern int record_board[SIZE][SIZE];

char* to_string_horizontal(int x, int y)
{
    char* string_h = (char* )malloc(15);
    for (int i = 0; i < SIZE; i++)
    {
        if (record_board[x][i] == EMPTY)
            string_h[i] = '0';
        else if (record_board[x][i] == BLACKPIECE || record_board[x][i] == BLACKTRIANGLE)
            string_h[i] = '1';
        else if (record_board[x][i] == WHITEPIECE || record_board[x][i] == WHITETRIANGLE)
            string_h[i] = '7';
    }
    strcat(string_h, "\0");
    y++; // useless statement to avoid warnings from the complier
    return string_h;
}
char* to_string_vertical(int x, int y)
{
    char* string_v = (char* )malloc(15);
    for (int i = 0; i < SIZE; i++)
    {
        if (record_board[i][y] == EMPTY)
            string_v[i] = '0';
        else if (record_board[i][y] == BLACKPIECE || record_board[i][y] == BLACKTRIANGLE)
            string_v[i] = '1';
        else if (record_board[i][y] == WHITEPIECE || record_board[i][y] == WHITETRIANGLE)
            string_v[i] = '7';
    }
    strcat(string_v, "\0");
    x++; // useless statement to avoid warnings from the complier
    return string_v;
}
char* to_string_main_diagonal(int x, int y)
{
    int length = 15 - abs(x - y);
    char* string_md = (char* )malloc(length);
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
    strcat(string_md, "\0");
    return string_md;
}
char* to_string_sub_diagonal(int x, int y)
{
    int length;
    if (x + y < 15)
    {
        length = x + y + 1;
        char* string_sd = (char* )malloc(length);
        for (int i = 0; i < length; i++)
        {
            if (record_board[length - 1 - i][i] == EMPTY)
                string_sd[i] = '0';
            else if (record_board[length - 1 - i][i] == BLACKPIECE || record_board[length - 1 - i][i] == BLACKTRIANGLE)
                string_sd[i] = '1';
            else if (record_board[length - 1 - i][i] == WHITEPIECE || record_board[length - 1 - i][i] == WHITETRIANGLE)
                string_sd[i] = '7';
        }
        strcat(string_sd, "\0");
        return string_sd;
    }
    else
    {
        length = (15 - x) + (15 - y) - 1;
        char* string_sd = (char* )malloc(length);
        for (int i = 0; i < length; i++)
        {
            if (record_board[SIZE - 1 - i][x + y + 1 - SIZE + i] == EMPTY)
                string_sd[i] = '0';
            else if (record_board[SIZE - 1 - i][x + y + 1 - SIZE + i] == BLACKPIECE || record_board[SIZE - 1 - i][x + y + 1 - SIZE + i] == BLACKTRIANGLE)
                string_sd[i] = '1';
            else if (record_board[SIZE - 1 - i][x + y + 1 - SIZE + i] == WHITEPIECE || record_board[SIZE - 1 - i][x + y + 1 - SIZE + i] == WHITETRIANGLE)
                string_sd[i] = '7';
        }
        strcat(string_sd, "\0");
        return string_sd;
    }
    return NULL;
}

char* to_string(int x, int y, int direction)
{
    switch (direction)
    {
    case HORIZONTAL:
        return to_string_horizontal(x, y);
    case VERTICAL:
        return to_string_vertical(x, y);
    case MAIN_DIAGONAL:
        return to_string_main_diagonal(x, y);
    case SUB_DIAGONAL:
        return to_string_sub_diagonal(x, y);
    default:
        return NULL;
    }
}
char* str_reverse(char* str)
{
    int len = strlen(str) + 1;
    char* reverse_str = (char* )malloc(len);
    for (int i = 0; i < len - 1; i++)
        reverse_str[i] = str[len - 2 - i];
    reverse_str[len - 1] = '\0';
    return reverse_str;
}

int str_match(char* str_s, char* str_l)
{
    int len_str_s = strlen(str_s), len_str_l = strlen(str_l);
    if (len_str_s > len_str_l)
        return 0;

    int res = 0;
    int i, j;
    for (i = 0; i <= len_str_l - len_str_s; i++)
    {
        for (j = 0; j < len_str_s; j++)
            if (str_s[j] != str_l[i + j])
                break;
        if (j == len_str_s)
        {
            i += (len_str_s - 1);
            res++;
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
    // one side
    int i;
    for (i = 0; i < len_str_s; i++)
        if (!(str_s[i] == str_l[i]))
            break;
    if (i == len_str_s)
        res++;
    // another side
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

    char* r_dead_two_B_1 = str_reverse(dead_two_B_1);
    char* r_dead_two_B_2 = str_reverse(dead_two_B_2);
    char* r_dead_two_B_3 = str_reverse(dead_two_B_3);

    char* str = to_string(x, y, direction);

    res += str_match(dead_two_B_1, str);
    res += str_match(dead_two_B_2, str);
    res += str_match(dead_two_B_3, str);

    res += str_match(r_dead_two_B_1, str);
    res += str_match(r_dead_two_B_2, str);
    res += str_match(r_dead_two_B_3, str);

    res -= str_match(s_dead_two_B_1, str);
    res -= str_match(s_dead_two_B_2, str);

    res += str_match_side(e_dead_two_B_4, str);

    free(str);

    res -= num_dead_three_black(x, y, direction);

    free(r_dead_two_B_1);
    free(r_dead_two_B_2);
    free(r_dead_two_B_3);

    return res;
}
int num_dead_two_white(int x, int y, int direction)
{
    int res = 0;

    char* r_dead_two_W_1 = str_reverse(dead_two_W_1);
    char* r_dead_two_W_2 = str_reverse(dead_two_W_2);
    char* r_dead_two_W_3 = str_reverse(dead_two_W_3);


    char* str = to_string(x, y, direction);

    res += str_match(dead_two_W_1, str);
    res += str_match(dead_two_W_2, str);
    res += str_match(dead_two_W_3, str);

    res += str_match(r_dead_two_W_1, str);
    res += str_match(r_dead_two_W_2, str);
    res += str_match(r_dead_two_W_3, str);

    res -= str_match(s_dead_two_W_1, str);
    res -= str_match(s_dead_two_W_2, str);

    res += str_match_side(e_dead_two_W_4, str);

    free(str);

    res -= num_dead_three_white(x, y, direction);

    free(r_dead_two_W_1);
    free(r_dead_two_W_2);
    free(r_dead_two_W_3);

    return res;
}

int num_active_two_black(int x, int y, int direction)
{
    int res = 0;

    char* str = to_string(x, y, direction);
    res += str_match(active_two_B_1, str);
    res += str_match(active_two_B_2, str);
    free(str);

    res -= num_active_three_black(x, y, direction);
    res -= num_dead_four_black(x, y, direction);
    return res;
}
int num_active_two_white(int x, int y, int direction)
{
    int res = 0;

    char* str = to_string(x, y, direction);
    res += str_match(active_two_W_1, str);
    res += str_match(active_two_W_2, str);

    free(str);
    
    res -= num_active_three_white(x, y, direction);
    res -= num_dead_four_white(x, y, direction);
    return res;
}

int num_dead_three_black(int x, int y, int direction)
{
    int res = 0;

    char* r_dead_three_B_1 = str_reverse(dead_three_B_1);
    char* r_dead_three_B_4 = str_reverse(dead_three_B_4);
    char* r_dead_three_B_5 = str_reverse(dead_three_B_5);
    char* r_dead_three_B_6 = str_reverse(dead_three_B_6);

    
    char* str = to_string(x, y, direction);

    res += str_match(dead_three_B_1, str);
    res += str_match(dead_three_B_2, str);
    res += str_match(dead_three_B_3, str);
    res += str_match(dead_three_B_4, str);
    res += str_match(dead_three_B_5, str);
    res += str_match(dead_three_B_6, str);

    // reverse
    res += str_match(r_dead_three_B_1, str);
    res += str_match(r_dead_three_B_4, str);
    res += str_match(r_dead_three_B_5, str);
    res += str_match(r_dead_three_B_6, str);

    // symmetry
    res -= str_match(s_dead_three_B_1, str);
    res -= str_match(s_dead_three_B_1_a, str);

    res += str_match_side(e_dead_three_B_7, str);
    res -= str_match_side(e_dead_three_B_7_forbidden, str);

    free(str);
    free(r_dead_three_B_1);
    free(r_dead_three_B_4);
    free(r_dead_three_B_5);
    free(r_dead_three_B_6);

    return res;
}
int num_dead_three_white(int x, int y, int direction)
{
    int res = 0;

    char* r_dead_three_W_1 = str_reverse(dead_three_W_1);
    char* r_dead_three_W_4 = str_reverse(dead_three_W_4);
    char* r_dead_three_W_5 = str_reverse(dead_three_W_5);
    char* r_dead_three_W_6 = str_reverse(dead_three_W_6);

    char* str = to_string(x, y, direction);

    res += str_match(dead_three_W_1, str);
    res += str_match(dead_three_W_2, str);
    res += str_match(dead_three_W_3, str);
    res += str_match(dead_three_W_4, str);
    res += str_match(dead_three_W_5, str);
    res += str_match(dead_three_W_6, str);

    // reverse
    res += str_match(r_dead_three_W_1, str);
    res += str_match(r_dead_three_W_4, str);
    res += str_match(r_dead_three_W_5, str);
    res += str_match(r_dead_three_W_6, str);

    // symmetry
    res -= str_match(s_dead_three_W_1, str);
    res -= str_match(s_dead_three_W_1_a, str);

    res += str_match_side(e_dead_three_W_7, str);

    free(str);
    free(r_dead_three_W_1);
    free(r_dead_three_W_4);
    free(r_dead_three_W_5);
    free(r_dead_three_W_6);

    return res;
}

int num_active_three_black(int x, int y, int direction)
{
    int res = 0;
    char* r_active_three_B_1 = str_reverse(active_three_B_1);
    char* r_active_three_forbidden_1 = str_reverse(active_three_forbidden_1);
    char* r_active_three_forbidden_2 = str_reverse(active_three_forbidden_2);

    char* r_active_three_B_2 = str_reverse(active_three_B_2);
    char* r_active_three_forbidden_3 = str_reverse(active_three_forbidden_3);
    char* r_active_three_forbidden_4 = str_reverse(active_three_forbidden_4);

    char* str = to_string(x, y, direction);
    res += str_match(active_three_B_1, str);
    res -= str_match(active_three_forbidden_1, str);
    res -= str_match(active_three_forbidden_2, str);

    res += str_match(active_three_B_2, str);
    res -= str_match(active_three_forbidden_3, str);
    res -= str_match(active_three_forbidden_4, str);

    // reverse
    res += str_match(r_active_three_B_1, str);
    res -= str_match(r_active_three_forbidden_1, str);
    res -= str_match(r_active_three_forbidden_2, str);

    res += str_match(r_active_three_B_2, str);
    res -= str_match(r_active_three_forbidden_3, str);
    res -= str_match(r_active_three_forbidden_4, str);

    // symmetry
    res -= str_match(s_active_three_B_1, str);
    res -= str_match(s_active_three_B_2, str);
    res += str_match(s_active_three_forbidden_1, str);
    res += str_match(s_active_three_forbidden_3, str);
    res += str_match(s_active_three_forbidden_4, str);

    free(str);

    free(r_active_three_B_1);
    free(r_active_three_forbidden_1);
    free(r_active_three_forbidden_2);

    free(r_active_three_B_2);
    free(r_active_three_forbidden_3);
    free(r_active_three_forbidden_4);

    return res;
}
int num_active_three_white(int x, int y, int direction)
{
    int res = 0;

    char* r_active_three_W_1 = str_reverse(active_three_W_1);
    char* r_active_three_W_2 = str_reverse(active_three_W_2);

    char* str = to_string(x, y, direction);

    res += str_match(active_three_W_1, str);
    res += str_match(active_three_W_2, str);

    // reverse
    res += str_match(r_active_three_W_1, str);
    res += str_match(r_active_three_W_2, str);

    // symmetry
    res -= str_match(s_active_three_W_1, str);
    res -= str_match(s_active_three_W_2, str);

    free(str);
    
    free(r_active_three_W_1);
    free(r_active_three_W_2);

    return res;
}

int num_active_four_black(int x, int y, int direction)
{
    int res = 0;
    char* r_active_four_forbidden = str_reverse(active_four_forbidden);

    char* str = to_string(x, y, direction);
    res += str_match(active_four_B, str);
    res -= str_match(active_four_forbidden, str);

    // reverse
    res -= str_match(r_active_four_forbidden, str);

    // symmetry
    res += str_match(s_active_four_forbidden, str);
    free(str);

    free(r_active_four_forbidden);

    return res;
}
int num_active_four_white(int x, int y, int direction)
{
    int res = 0;
    
    char* str = to_string(x, y, direction);
    res += str_match(active_four_W, str);
    free(str);
    
    return res;
}

int num_dead_four_black(int x, int y, int direction)
{
    int res = 0;

    char* r_dead_four_forbidden_1 = str_reverse(dead_four_forbidden_1);

    char* r_dead_four_B_2 = str_reverse(dead_four_B_2);
    char* r_dead_four_forbidden_2 = str_reverse(dead_four_forbidden_2);
    char* r_dead_four_forbidden_3 = str_reverse(dead_four_forbidden_3);

    char* r_dead_four_B_3 = str_reverse(dead_four_B_4);
    char* r_dead_four_forbidden_4 = str_reverse(dead_four_forbidden_4);

    char* r_dead_four_B_4 = str_reverse(dead_four_B_4);
    char* r_dead_four_B_5 = str_reverse(dead_four_B_5);

    char* str = to_string(x, y, direction);

    res += str_match(dead_four_B_1, str);
    res -= str_match(dead_four_forbidden_1, str);
    res += str_match(dead_four_B_2, str);
    res -= str_match(dead_four_forbidden_2, str);
    res -= str_match(dead_four_forbidden_3, str);
    res += str_match(dead_four_B_3, str);
    res -= str_match(dead_four_forbidden_4, str);
    res += str_match(dead_four_B_4, str);
    res += str_match(dead_four_B_5, str);

    // reverse
    res -= str_match(r_dead_four_forbidden_1, str);
    res += str_match(r_dead_four_B_2, str);
    res -= str_match(r_dead_four_forbidden_2, str);
    res -= str_match(r_dead_four_forbidden_3, str);
    res += str_match(r_dead_four_B_3, str);
    res -= str_match(r_dead_four_forbidden_4, str);
    res += str_match(r_dead_four_B_4, str);
    res += str_match(r_dead_four_B_5, str);

    // symmetry
    res += str_match(s_dead_four_forbidden_1, str);
    res += str_match(s_dead_four_forbidden_1_a, str);
    res -= str_match(s_dead_four_B_2, str);
    res -= str_match(s_dead_four_B_2_a, str);
    res += str_match(s_dead_four_forbidden_2, str);
    res += str_match(s_dead_four_forbidden_2_a, str);
    res += str_match(s_dead_four_forbidden_3, str);
    res += str_match(s_dead_four_forbidden_3_a, str);

    res += str_match_side(e_dead_four_B_6, str);
    res -= str_match_side(e_dead_four_B_6_forbidden, str);

    free(str);
    free(r_dead_four_forbidden_1);
    free(r_dead_four_B_2);
    free(r_dead_four_forbidden_2);
    free(r_dead_four_forbidden_3);
    free(r_dead_four_B_3);
    free(r_dead_four_forbidden_4);
    free(r_dead_four_B_4);
    free(r_dead_four_B_5);

    return res;
}
int num_dead_four_white(int x, int y, int direction)
{
    int res = 0;

    char* r_dead_four_W_1 = str_reverse(dead_four_W_1);
    char* r_dead_four_W_2 = str_reverse(dead_four_W_2);
    char* r_dead_four_W_3 = str_reverse(dead_four_W_3);

    char* str = to_string(x, y, direction);

    res += str_match(dead_four_W_1, str);
    res += str_match(dead_four_W_2, str);
    res += str_match(dead_four_W_3, str);

    // reverse
    res += str_match(r_dead_four_W_1, str);
    res += str_match(r_dead_four_W_2, str);
    res += str_match(r_dead_four_W_3, str);

    // symmetry
    res -= str_match(s_dead_four_W_2, str);

    res += str_match_side(e_dead_three_W_7, str);

    free(str);
    free(r_dead_four_W_1);
    free(r_dead_four_W_2);
    free(r_dead_four_W_3);

    return res;
}

int is_five_black(int x, int y, int direction)
{
    
    char* str = to_string(x, y, direction);
    if (str_match(five_forbidden, str))
    {
        free(str);
        // 触发禁手
        return -1;
    }
    if (str_match(five_B, str))
    {
        free(str);
        return 1;
    }
    free(str);

    return 0;
}
int is_five_white(int x, int y, int direction)
{ 
    char* str = to_string(x, y, direction);
    if (str_match(five_W, str))
    {
        free(str);
        return 1;
    }
    free(str);
    
    return 0;
}

int num_overline(int x, int y, int direction)
{
    int res = 0;
    
    char* str = to_string(x, y, direction);
    res += str_match(five_forbidden, str);
    
    return res;
}