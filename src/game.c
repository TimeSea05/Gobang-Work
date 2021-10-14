#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "game.h"

#define SIZE 15
#define BLACKPIECE 1
#define BLACKTRIANGLE 3
#define WHITEPIECE 7
#define WHITETRIANGLE 9
#define EMPTY 0

#define HORIZONTAL 1
#define HORIZONTAL_INV 2
#define VERTICAL 3
#define VERTICAL_INV 4
#define MAIN_DIAGONAL 5
#define MAIN_DIAGONAL_INV 6
#define SUB_DIAGONAL 7
#define SUB_DIAGONAL_INV 8

extern int record_board[SIZE][SIZE];

// active three
char active_three_B_1[7] = "011100\0";
char active_three_forbidden_1[8] = "0111001\0";
char active_three_forbidden_2[8] = "1011100\0";

char active_three_B_2[7] = "011010\0";
char active_three_forbidden_3[8] = "1011010\0";
char active_three_forbidden_4[8] = "0110101\0";

char active_three_W_1[7] = "077700\0";
char active_three_W_2[7] = "077070\0";

// active four
char active_four_B[] = "011110\0";
char active_four_forbidden[] = "1011110\0";

char active_four_W[] = "077770\0";

// dead four
char dead_four_B_1[] = "11011\0";
char dead_four_forbidden_1[] = "111011\0";

char dead_four_B_2[] = "11101\0";
char dead_four_forbidden_2[] = "111101";
char dead_four_forbidden_3[] = "111011";

char dead_four_B_3[] = "711110\0";
char dead_four_forbidden_4[] = "7111101\0";

char dead_four_B_4[] = "10111100\0";
char dead_four_B_5[] = "10111107\0";

char dead_four_W_1[] = "77077\0";
char dead_four_W_2[] = "77707\0";
char dead_four_W_3[] = "177770\0";

// five
char five_B[] = "11111\0";
char five_forbidden[] = "111111\0";

char five_W[] = "77777\0";


// transfer current game situation to string
char * to_string_horizontal(int x, int y)
{
    char * string_h = (char *)malloc(15);
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
    return string_h;
}
char * to_string_horizontal_inv(int x, int y)
{
    char * string_h_inv = (char *)malloc(15);
    for (int i = SIZE - 1, j = 0; i >= 0; i--, j++)
    {
        if (record_board[x][i] == EMPTY)
            string_h_inv[j] = '0';
        else if (record_board[x][i] == BLACKPIECE || record_board[x][i] == BLACKTRIANGLE)
            string_h_inv[j] = '1';
        else if (record_board[x][i] == WHITEPIECE || record_board[x][i] == WHITETRIANGLE)
            string_h_inv[j] = '7';
    }
    strcat(string_h_inv, "\0");
    return string_h_inv;
}
char * to_string_vertical(int x, int y)
{
    char * string_v = (char *)malloc(15);
    for (int i = 0; i < SIZE; i++)
    {
        if (record_board[i][y] == EMPTY)
            string_v[i] = '0';
        else if (record_board[i][y] == BLACKPIECE || record_board[i][y] == BLACKTRIANGLE)
            string_v[i] = '1';
        else if (record_board[i][y] == WHITEPIECE || record_board[i][y] == WHITEPIECE)
            string_v[i] = '7';
    }
    strcat(string_v, "\0");
    return string_v;
}
char * to_string_vertical_inv(int x, int y)
{
    char * string_v_inv = (char *)malloc(15);
    for (int i = SIZE - 1, j = 0; i >= 0; i--, j++)
    {
        if (record_board[i][y] == EMPTY)
            string_v_inv[j] = '0';
        else if (record_board[i][y] == BLACKPIECE || record_board[i][y] == BLACKTRIANGLE)
            string_v_inv[j] = '1';
        else if (record_board[i][y] == WHITEPIECE || record_board[i][y] == WHITETRIANGLE)
            string_v_inv[j] = '7';
    }
    strcat(string_v_inv, "\0");
    return string_v_inv;
}
char * to_string_main_diagonal(int x, int y)
{
    int length = 15 - abs(x - y);
    char * string_md = (char *)malloc(length);
    if (x < y)
        for (int i = 0; i < length; i++)
        {
            if (record_board[i][y - x + i] == EMPTY)
                string_md[i] = '0';
            else if (record_board[i][y - x + i] == BLACKPIECE
                    || record_board[i][y - x + i] == BLACKTRIANGLE)
                string_md[i] = '1';
            else if (record_board[i][y - x + i] == WHITEPIECE
                    || record_board[i][y - x + i] == WHITETRIANGLE)
                string_md[i] = '1';
        }
    else
        for (int i = 0; i < length; i++)
        {
            if (record_board[x - y + i][i] == EMPTY)
                string_md[i] = '0';
            else if (record_board[x - y + i][i] == BLACKPIECE
                    || record_board[x - y + i][i] == BLACKTRIANGLE)
                string_md[i] = '1';
            else if (record_board[x - y + i][i] == WHITEPIECE
                    || record_board[x - y + i][i] == WHITETRIANGLE)
                string_md[i] = '1';
        }
    strcat(string_md, "\0");
    return string_md;
}
char * to_string_main_diagonal_inv(int x, int y)
{
    int length = 15 - abs(x - y);
    char * string_md_inv = (char *)malloc(length);
    if (x < y)
        for (int i = length - 1, j = 0; i >= 0; i--, j++)
        {
            if (record_board[i][y - x + i] == EMPTY)
                string_md_inv[j] = '0';
            else if (record_board[i][y - x + i] == BLACKPIECE
                    || record_board[i][y - x + i] == BLACKTRIANGLE)
                string_md_inv[j] = '1';
            else if (record_board[i][y - x + i] == WHITEPIECE
                    || record_board[i][y - x + i] == WHITETRIANGLE)
                string_md_inv[j] = '1';
        }
    else
        for (int i = length - 1, j = 0; i >= 0; i--, j++)
        {
            if (record_board[x - y + i][i] == EMPTY)
                string_md_inv[j] = '0';
            else if (record_board[x - y + i][i] == BLACKPIECE
                    || record_board[x - y + i][i] == BLACKTRIANGLE)
                string_md_inv[j] = '1';
            else if (record_board[x - y + i][i] == WHITEPIECE
                    || record_board[x - y + i][i] == WHITETRIANGLE)
                string_md_inv[j] = '1';
        }
    strcat(string_md_inv, "\0");
    return string_md_inv;
}
char * to_string_sub_diagonal(int x, int y)
{
    int length;
    if (x + y < 15)
    {  
        length = x + y + 1;
        char * string_sd = (char *)malloc(length);
        for (int i = 0; i < length; i++)
        {
            if (record_board[length - 1 - i][i] == EMPTY)
                string_sd[i] = '0';
            else if (record_board[length - 1 - i][i] == BLACKPIECE
                    || record_board[length - 1 - i][i] == BLACKTRIANGLE)
                string_sd[i] = '1';
            else if (record_board[length - 1 - i][i] == WHITEPIECE
                    || record_board[length - 1 - i][i] == WHITETRIANGLE)
                string_sd[i] = '7';
        }
        strcat(string_sd, "\0");
        return string_sd;
    }
    else
    {
        length = (15 - x) + (15 - y) - 1;
        char * string_sd = (char *)malloc(length);
        for (int i = 0; i < length; i++)
        {
            if (record_board[SIZE - 1 - i][x + y + 1 - SIZE + i] == EMPTY)
                string_sd[i] = '0';
            else if (record_board[SIZE - 1 - i][x + y + 1 - SIZE + i] == BLACKPIECE
                    || record_board[SIZE - 1 - i][x + y + 1 - SIZE + i] == BLACKTRIANGLE)
                string_sd[i] = '1';
            else if (record_board[SIZE - 1 - i][x + y + 1 - SIZE + i] == WHITEPIECE
                    || record_board[SIZE - 1 - i][x + y + 1 - SIZE + i] == WHITETRIANGLE)
                string_sd[i] = '7';
        }
        strcat(string_sd, "\0");
        return string_sd;
    }
    return NULL;
}
char * to_string_sub_diagonal_inv(int x, int y)
{
    int length;
    if (x + y < 15)
    {  
        length = x + y + 1;
        char * string_sd_inv = (char *)malloc(length);
        for (int i = length - 1, j = 0; i >= 0; i--, j++)
        {
            if (record_board[length - 1 - i][i] == EMPTY)
                string_sd_inv[j] = '0';
            else if (record_board[length - 1 - i][i] == BLACKPIECE
                    || record_board[length - 1 - i][i] == BLACKTRIANGLE)
                string_sd_inv[j] = '1';
            else if (record_board[length - 1 - i][i] == WHITEPIECE
                    || record_board[length - 1 - i][i] == WHITETRIANGLE)
                string_sd_inv[j] = '7';
        }
        strcat(string_sd_inv, "\0");
        return string_sd_inv;
    }
    else
    {
        length = (15 - x) + (15 - y) - 1;
        char * string_sd_inv = (char *)malloc(length);
        for (int i = length - 1, j = 0; i >= 0; i--, j++)
        {
            if (record_board[SIZE - 1 - i][x + y + 1 - SIZE + i] == EMPTY)
                string_sd_inv[j] = '0';
            else if (record_board[SIZE - 1 - i][x + y + 1 - SIZE + i] == BLACKPIECE
                    || record_board[SIZE - 1 - i][x + y + 1 - SIZE + i] == BLACKTRIANGLE)
                string_sd_inv[j] = '1';
            else if (record_board[SIZE - 1 - i][x + y + 1 - SIZE + i] == WHITEPIECE
                    || record_board[SIZE - 1 - i][x + y + 1 - SIZE + i] == WHITETRIANGLE)
                string_sd_inv[j] = '7';
        }
        strcat(string_sd_inv, "\0");
        return string_sd_inv;
    }
    return NULL;
}

char * to_string(int x, int y, int direction)
{
    switch(direction)
    {
        case HORIZONTAL:
            return to_string_horizontal(x, y);
        case HORIZONTAL_INV:
            return to_string_horizontal_inv(x, y);
        case VERTICAL:
            return to_string_vertical(x, y);
        case VERTICAL_INV:
            return to_string_vertical_inv(x, y);
        case MAIN_DIAGONAL:
            return to_string_main_diagonal(x, y);
        case MAIN_DIAGONAL_INV:
            return to_string_main_diagonal_inv(x, y);
        case SUB_DIAGONAL:
            return to_string_sub_diagonal(x, y);
        case SUB_DIAGONAL_INV:
            return to_string_sub_diagonal_inv(x, y);
        default:
            return NULL;
    }
}

int str_match(char * str_s, char * str_l)
{
    int len_str_s = strlen(str_s), len_str_l = strlen(str_l);
    int i, j;
    for (i = 0; i < len_str_l; i++)
    {
        for (j = 0; j < len_str_s; j++)
        {
            if (i + j >= len_str_l || str_s[j] != str_l[i + j])
                break;
        }
        if (j == len_str_s)
            return 1;
    }
    return 0;
}

int match_active_three_black(int x, int y, int direction)
{
    char * str = to_string(x, y, direction);
    if (str_match(active_three_B_1, str))
    {
        if (!str_match(active_three_forbidden_1, str)
            && !str_match(active_three_forbidden_2, str))
        {
            free(str);
            return 1;
        }
    }
    else if (str_match(active_three_B_2, str))
    {
        if (!str_match(active_three_forbidden_3, str)
            && !str_match(active_three_forbidden_4, str))
        {
            free(str);
            return 1;
        }
    }
    free(str);
    return 0;
}
int num_active_three_black(int x, int y)
{
    int res = 0;
    for (int direction = 1; direction <= 7; direction += 2)
        if (match_active_three_black(x, y, direction))
            res++;
        else if (match_active_three_black(x, y, direction + 1))
            res++;
    return res;
}
int match_active_three_white(int x, int y, int direction)
{
    char * str = to_string(x, y, direction);
    if (str_match(active_three_W_1, str))
    {
        free(str);
        return 1;
    }
    else if (str_match(active_three_W_2, str))
    {
        free(str);
        return 1;
    }
    free(str);
    return 0;
}
int num_active_three_white(int x, int y)
{
    int res = 0;
    for (int direction = 1; direction <= 7; direction += 2)
        if (match_active_three_white(x, y, direction))
            res++;
        else if (match_active_three_white(x, y, direction + 1))
            res++;
    return res;
}

int match_active_four_black(int x, int y, int direction)
{
    char * str = to_string(x, y, direction);
    if (str_match(active_four_B, str) && !str_match(active_four_forbidden, str))
    {
        free(str);
        return 1;
    }
    free(str);
    return 0;
}
int num_active_four(int x, int y)
{
    int res = 0;
    for (int direction = 1; direction <= 7; direction += 2)
        if (match_active_four_black(x, y, direction))
            res++;
        else if (match_active_four_black(x, y, direction + 1))
            res++;
    return res;
}
int match_active_four_white(int x, int y, int direction)
{
    char * str = to_string(x, y, direction);
    if (str_match(active_four_W, str))
    {
        free(str);
        return 1;
    }
    free(str);
    return 0;
}
int num_active_four_white(int x, int y)
{
    int res = 0;
    for (int direction = 1; direction <= 7; direction += 2)
        if (match_active_four_white(x, y, direction))
            res++;
        else if (match_active_four_white(x, y, direction + 1))
            res++;
    return res;
}

int match_dead_four_black(int x, int y, int direction)
{
    char * str = to_string(x, y, direction);
    if (str_match(dead_four_B_1, str) && !str_match(dead_four_forbidden_1, str))
    {
        free(str);
        return 1;
    }
    else if (str_match(dead_four_B_2, str) && !str_match(dead_four_forbidden_2, str)
            && str_match(dead_four_forbidden_3, str))
    {
        free(str);
        return 1;
    }
    else if (str_match(dead_four_B_3, str) && !str_match(dead_four_forbidden_4, str))
    {
        free(str);
        return 1;
    }
    else if (str_match(dead_four_B_4, str) || str_match(dead_four_B_5, str))
    {
        free(str);
        return 1;
    }
    free(str);
    return 1;
}
int num_dead_four_black(int x, int y)
{
    int res = 0;
    for (int direction = 1; direction <= 7; direction += 2)
        if (match_dead_four_black(x, y, direction + 1))
            res++;
        else if (match_dead_four_black(x, y, direction + 1))
            res++;
    return res;
}
int match_dead_four_white(int x, int y, int direction)
{
    char * str = to_string(x, y, direction);
    if (str_match(dead_four_W_1, str) || str_match(dead_four_W_2, str)
        || str_match(dead_four_W_3, str))
    {
        free(str);
        return 1;
    }
    free(str);
    return 0;
}
int num_dead_four_white(int x, int y)
{
    int res = 0;
    for (int direction = 1; direction <= 7; direction += 2)
        if (match_dead_four_white(x, y, direction))
            res++;
        else if (match_active_four_white(x, y, direction + 1))
            res++;
    return res;
}

int is_five_black(int x, int y)
{
    for (int direction = 1; direction <= 7; direction += 2)
    {
        char * str = to_string(x, y, direction);
        if (str_match(five_B, str) && !str_match(five_forbidden, str))
        {
            free(str);
            return 1;
        }
        free(str);
    }
    return 0;
}
int is_five_white(int x, int y)
{
    for (int direction = 1; direction <= 7; direction += 2)
    {
        char * str = to_string(x, y, direction);
        if (str_match(five_W, str))
        {
            free(str);
            return 1;
        }
        free(str);
    }
    return 1;
}