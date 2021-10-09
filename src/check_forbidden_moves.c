#include "check_forbidden_moves.h"

#define SIZE 15
#define CHARSIZE 2

#define BLACKPIECE 1
#define BLACKTRIANGLE 3
#define WHITEPIECE 7
#define WHITETRIANGLE 9

extern char init_display_board_array[SIZE][SIZE * CHARSIZE + 1];
extern char display_board_array[SIZE][SIZE * CHARSIZE + 1];
extern int record_board[SIZE][SIZE];
extern char play1_pic[];
extern char play1_current_pic[];
extern char play2_pic[];
extern char play2_current_pic[];
extern int current_pos_x;
extern int current_pos_y;
extern int previous_type;

// count the pieces horizontally
// then return the number of identical pieces around a given piece
// p1 & p2 are used to store extermities of these linked pieces
static int count_horizontally(int x, int y, int * p1, int * p2, int type)
{
    int count = 1;
    int i = y;

    while (i > 0)
        if (record_board[x][i - 1] == type || record_board[x][i - 1] == type + 2)
        {
            count++;
            i--;
        }
        else
            break;
    *p1 = i - 1;
    i = y;
    while (i < SIZE - 1)
        if (record_board[x][i + 1] == type || record_board[x][i + 1] == type + 2)
        {
            count++;
            i++;
        }
        else
            break;
    *p2 = i + 1;

    return count;
}

// count the pieces vertically
// then return the number of identical pieces around a given piece
// p1 & p2 are used to store extermities of these linked pieces
static int count_vertically(int x, int y, int * p1, int * p2, int type)
{
    int count = 1;
    int i = x;
    
    while (i > 0)
        if (record_board[i - 1][y] == type || record_board[i - 1][y] == type + 2)
        {
            count++;
            i--;
        }
        else
            break;
    *p1 = i - 1;
    i = x;
    while (i < SIZE - 1)
        if (record_board[i + 1][y] == type || record_board[i + 1][y] == type + 2)
        {
            count++;
            i++;
        }
        else
            break;
    *p2 = i + 1;

    return count;
}

// count the pieces main-diagonally
// then return the number of identical pieces around a given piece
// p1 & p2 & p3 & p4 are used to store extermities of these linked pieces
static int count_main_diagonally(int x, int y, int * p1, int * p2, int * p3, int * p4, int type)
{
    int count = 1;
    int i = x, j = y;

    while (i > 0 && j > 0)
        if (record_board[i - 1][j - 1] == type || record_board[i - 1][j - 1] == type + 2)
        {
            count++;
            i--;
            j--;
        }
        else
            break;
    *p1 = i - 1, *p3 = j - 1;
    i = x, j = y;
    while (i < SIZE - 1 && j < SIZE - 1)
        if (record_board[i + 1][j + 1] == type || record_board[i + 1][j + 1] == type + 2)
        {
            count++;
            i++;
            j++;
        }
        else
            break;
    *p2 = i + 1, *p4 = j + 1;

    return count;
}

// count the pieces sub-diagonally
// then return the number of identical pieces around a given piece
// p1 & p2 & p3 & p4 are used to store extermities of these linked pieces
static int count_sub_diagonally(int x, int y, int *p1, int * p2, int * p3, int * p4, int type)
{
    int count = 1;
    int i = x, j = y;
    
    while (i > 0 && j < SIZE - 1)
        if (record_board[i - 1][j + 1] == type || record_board[i - 1][j + 1] == type + 2)
        {
            count++;
            i--;
            j++;
        }
        else
            break;
    *p1 = i - 1, *p3 = j + 1;

    i = x, j = y;
    while (i < SIZE - 1 && j > 0)
        if (record_board[i + 1][j - 1] == type || record_board[i + 1][j - 1] == type + 2)
        {
            count++;
            i++;
            j--;
        }
        else
            break;
    *p2 = i + 1, *p4 = j - 1;

    return count;
}


int is_five_black(int x, int y)
{
    int count_h, count_v, count_md, count_sd;
    int p1, p2, p3, p4;
    count_h = count_horizontally(x, y, &p1, &p2, BLACKPIECE);
    count_v = count_vertically(x, y, &p1, &p2, BLACKPIECE);
    count_md = count_main_diagonally(x, y, &p1, &p2, &p3, &p4, BLACKPIECE);
    count_sd = count_sub_diagonally(x, y, &p1, &p2, &p3, &p4, BLACKPIECE);
    if (count_h == 5 || count_v == 5 || count_md == 5 || count_sd == 5)
        return 1;
    
    // no fives
    return 0;
}

int is_five_white(int x, int y)
{
    int count_h, count_v, count_md, count_sd;
    int p1, p2, p3, p4;
    count_h = count_horizontally(x, y, &p1, &p2, WHITEPIECE);
    count_v = count_vertically(x, y, &p1, &p2, WHITEPIECE);
    count_md = count_main_diagonally(x, y, &p1, &p2, &p3, &p4, WHITEPIECE);
    count_sd = count_sub_diagonally(x, y, &p1, &p2, &p3, &p4, WHITEPIECE);
    if (count_h == 5 || count_v == 5 || count_md == 5 || count_sd == 5)
        return 1;
    
    // no fives
    return 0;
}

int is_over_line(int x, int y)
{
    int count_h, count_v, count_md, count_sd;
    int p1, p2, p3, p4;
    count_h = count_horizontally(x, y, &p1, &p2, BLACKPIECE);
    count_v = count_vertically(x, y, &p1, &p2, BLACKPIECE);
    count_md = count_main_diagonally(x, y, &p1, &p2, &p3, &p4, BLACKPIECE);
    count_sd = count_sub_diagonally(x, y, &p1, &p2, &p3, &p4, BLACKPIECE);
    if (count_h > 5 || count_v > 5 || count_md > 5 || count_sd > 5)
        return 1;
    
    // no fives
    return 0;
}


int is_active_three_horizontal(int x, int y)
{
    int p1, p2; // these variables are used to store extremities
    int count = count_horizontally(x, y, &p1, &p2, BLACKPIECE);
    
    /********************consecutive active three********************/
    if (count == 3)
    {
        if (p1 >= 0 && p2 < SIZE)
        {
            // if one side of the active three is the edge of chess board
            // side I
            if (p1 == 0)
            {
                if (record_board[x][p1] == 0 && record_board[x][p2] == 0 && record_board[x][p2 + 1] == 0
                    && record_board[x][p2 + 2] != BLACKPIECE && record_board[x][p2 + 2] != BLACKTRIANGLE)
                    return 1;
            }
            // side II
            else if (p2 == SIZE - 1)
            {
                if (record_board[x][p2] == 0 && record_board[x][p1] == 0 && record_board[x][p1 - 1] == 0
                    && record_board[x][p1 - 2] != BLACKPIECE && record_board[x][p1 - 2] != BLACKTRIANGLE)
                    return 1;
            }
            // if the active three is in the middle of the chess board
            else if (record_board[x][p1] == 0 && record_board[x][p2] == 0)
            {
                // near side I
                if (p1 == 1)
                {
                    if (record_board[x][p1 - 1] != BLACKPIECE && record_board[x][p1 - 1] != BLACKTRIANGLE 
                        && record_board[x][p2 + 1] != BLACKPIECE && record_board[x][p2 + 1] != BLACKTRIANGLE
                        && (!((record_board[x][p1 - 1] == WHITEPIECE || record_board[x][p1 - 1] == WHITETRIANGLE)
                        && (record_board[x][p2 + 1] == WHITEPIECE || record_board[x][p2 + 1] == WHITETRIANGLE)))
                        && (!((record_board[x][p1 - 1] == WHITEPIECE || record_board[x][p1 - 1] == WHITETRIANGLE)
                        && (record_board[x][p2 + 2] == BLACKPIECE || record_board[x][p2 + 2] == BLACKTRIANGLE))))
                        return 1;
                }
                // near side II
                else if (p2 == SIZE - 2)
                {
                    if (record_board[x][p1 - 1] != BLACKPIECE && record_board[x][p1 - 1] != BLACKTRIANGLE 
                        && record_board[x][p2 + 1] != BLACKPIECE && record_board[x][p2 + 1] != BLACKTRIANGLE
                        && (!((record_board[x][p1 - 1] == WHITEPIECE || record_board[x][p1 - 1] == WHITETRIANGLE)
                        && (record_board[x][p2 + 1] == WHITEPIECE || record_board[x][p2 + 1] == WHITETRIANGLE)))
                        && (!((record_board[x][p2 + 1] == WHITEPIECE || record_board[x][p1 - 1] == WHITETRIANGLE)
                        && (record_board[x][p1 - 2] == BLACKPIECE || record_board[x][p1 - 2] == BLACKTRIANGLE))))
                        return 1;
                }
                // center
                else
                {
                    if ((record_board[x][p1 - 1] != BLACKPIECE && record_board[x][p1 - 1] != BLACKTRIANGLE
                        && record_board[x][p2 + 1] != BLACKPIECE && record_board[x][p2 + 1] != BLACKTRIANGLE)    
                        && (!((record_board[x][p1 - 1] == WHITEPIECE || record_board[x][p1 - 1] == WHITETRIANGLE)
                        && (record_board[x][p2 + 1] == WHITEPIECE || record_board[x][p2 + 1] == WHITETRIANGLE)))
                        && (!((record_board[x][p1 - 1] == WHITEPIECE || record_board[x][p1 - 1] == WHITETRIANGLE)
                        && (record_board[x][p2 + 2] == BLACKPIECE || record_board[x][p2 + 2] == BLACKTRIANGLE))) 
                        && (!((record_board[x][p1 - 2] == BLACKPIECE || record_board[x][p1 - 2] == BLACKTRIANGLE)
                        && (record_board[x][p2 + 1] == WHITEPIECE || record_board[x][p2 + 1] == WHITETRIANGLE)))
                        && (!((record_board[x][p1 - 2] == BLACKPIECE || record_board[x][p1 - 2] == BLACKTRIANGLE)
                        && (record_board[x][p2 + 2] == BLACKPIECE || record_board[x][p2 + 2] == BLACKTRIANGLE))))
                        return 1;
                }
            }
        }
    }
    /********************nonconsecutive active three********************/
    else if (count == 2)
    {
        // the other black piece is in the left of the two
        if (p1 >= 0 && record_board[x][p1] == 0 && p1 - 1 >= 0
              && (record_board[x][p1 - 1] == BLACKPIECE || record_board[x][p1 - 1] == BLACKTRIANGLE)
            && p1 - 2 >= 0 && record_board[x][p1 - 2] == 0 && p2 < SIZE && record_board[x][p2] == 0)
        {
            if (p1 - 3 >= 0)
            {
                if (record_board[x][p1 - 3] != BLACKPIECE && record_board[x][p1 - 3] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p2 + 1 < SIZE)
                    {
                        if (record_board[x][p2 + 1] != BLACKPIECE && record_board[x][p2 + 1] != BLACKTRIANGLE)
                            return 1;
                    }
                    // right side of the board
                    else
                        return 1;
                }
            }
            // left side of the board
            else if (p2 + 1 < SIZE && record_board[x][p2 + 1] != BLACKPIECE && record_board[x][p2 + 1] != BLACKTRIANGLE)
                return 1;
        }
        // the other black piece is in the right of the two
        if (p1 >= 0 && record_board[x][p1] == 0 && p2 < SIZE && record_board[x][p2] == 0 && p2 + 1 < SIZE 
            && (record_board[x][p2 + 1] == BLACKPIECE || record_board[x][p2 + 1] == BLACKTRIANGLE)
            && p2 + 2 < SIZE && record_board[x][p2 + 2] == 0)
        {
            if (p2 + 3 < SIZE)
            {
                if (record_board[x][p2 + 3] != BLACKPIECE && record_board[x][p2 + 3] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p1 - 1 >= 0)
                    {
                        if (record_board[x][p1 - 1] != BLACKPIECE && record_board[x][p1 - 1] != BLACKTRIANGLE)
                            return 1;
                    }
                    // left side of the board
                    else
                        return 1;
                }
            }
            // right side of the board
            else if (p1 - 1 >= 0 && record_board[x][p1 - 1] != BLACKPIECE && record_board[x][p1 - 1] != BLACKTRIANGLE)
                return 1;
        }

    }
    else if (count == 1)
    {
        // the other two black pieces are in the right of this piece
        if (p1 >= 0 && record_board[x][p1] == 0 && p2 < SIZE && record_board[x][p2] == 0
            && p2 + 1 < SIZE && (record_board[x][p2 + 1] == BLACKPIECE || record_board[x][p2 + 1] == BLACKTRIANGLE)
            && p2 + 2 < SIZE && (record_board[x][p2 + 2] == BLACKPIECE || record_board[x][p2 + 2] == BLACKTRIANGLE)
            && p2 + 3 < SIZE && record_board[x][p2 + 3] == 0)
        {
            if (p1 - 1 >= 0)
            {
                if (record_board[x][p1 - 1] != BLACKPIECE && record_board[x][p1 - 1] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p2 + 4 < SIZE)
                    {
                        if (record_board[x][p2 + 4] != BLACKPIECE && record_board[x][p2 + 4] != BLACKTRIANGLE)
                            return 1;
                    }
                    // right side of the board
                    else
                        return 1;
                }
            }
            else if (p2 + 4 < SIZE && record_board[x][p2 + 4] != BLACKPIECE && record_board[x][p2 + 4] != BLACKTRIANGLE)
                return 1;
        }
        // if the other two pieces is in the left of this piece
        if (p2 < SIZE && record_board[x][p2] == 0 && p1 >= 0 && record_board[x][p1] == 0
            && p1 - 1 >= 0 && (record_board[x][p1 - 1] == BLACKPIECE || record_board[x][p1 - 1] == BLACKTRIANGLE)
            && p1 - 2 >= 0 && (record_board[x][p1 - 2] == BLACKPIECE || record_board[x][p1 - 2] == BLACKTRIANGLE)
            && p1 - 3 >= 0 && record_board[x][p1 - 3] == 0)
        {
            if (p2 + 1 < SIZE)
            {
                if (record_board[x][p2 + 1] != BLACKPIECE && record_board[x][p2 + 1] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p1 - 4 >= 0)
                    {
                        if (record_board[x][p1 - 4] != BLACKPIECE && record_board[x][p1 - 4] != BLACKTRIANGLE)
                            return 1;
                    }
                    // left side of the board
                    else
                        return 1;
                }
            }
            else if (p1 - 4 >= 0 && record_board[x][p1 - 4] != BLACKPIECE && record_board[x][p1 - 4] != BLACKTRIANGLE)
                return 1;
        }
    }
    
    /********************no active three found********************/
    return 0;
}

int is_active_three_vertical(int x, int y)
{
    int p1, p2; // these variables are used to store extremities
    int count = count_vertically(x, y, &p1, &p2, BLACKPIECE);

    /********************consecutive active three********************/
    if (count == 3)
    {
        if (p1 >= 0 && p2 < SIZE)
        {
            // if one side of the active three is the edge of chess board
            // side I
            if (p1 == 0)
            {
                if (record_board[p1][y] == 0 && record_board[p2][y] == 0 && record_board[p2 + 1][y] == 0
                    && record_board[p2 + 2][y] != BLACKPIECE && record_board[p2 + 2][y] != BLACKTRIANGLE)   
                    return 1;
            }
            // side II
            else if (p2 == SIZE - 1)
            {
                if (record_board[p2][y] == 0 && record_board[p1][y] == 0 && record_board[p1 - 1][y] == 0
                    && record_board[p1 - 2][y] != BLACKPIECE && record_board[p1 - 2][y] != BLACKTRIANGLE)
                    return 1;
            }
            // if the active three is in the middle of the chess board
            else if (record_board[p1][y] == 0 && record_board[p2][y] == 0)
            {
                // near side I
                if (p1 == 1)
                {
                    if (record_board[p1 - 1][y] != BLACKPIECE && record_board[p1 - 1][y] != BLACKTRIANGLE 
                        && record_board[p2 + 1][y] != BLACKPIECE && record_board[p2 + 1][y] != BLACKTRIANGLE
                        && (!((record_board[p1 - 1][y] == WHITEPIECE || record_board[p1 - 1][y] == WHITETRIANGLE)
                        && (record_board[p2 + 1][y] == WHITEPIECE || record_board[p2 + 1][y] == WHITETRIANGLE)))
                        && (!((record_board[p1 - 1][y] == WHITEPIECE || record_board[p1 - 1][y] == WHITETRIANGLE)
                        && (record_board[p2 + 2][y] == BLACKPIECE || record_board[p2 + 2][y] == BLACKTRIANGLE))))
                        return 1;
                }
                // near side II
                else if (p2 == SIZE - 2)
                {
                    if (record_board[p1 - 1][y] != BLACKPIECE && record_board[p1 - 1][y] != BLACKTRIANGLE 
                        && record_board[p2 + 1][y] != BLACKPIECE && record_board[p2 + 1][y] != BLACKTRIANGLE
                        && (!((record_board[p1 - 1][y] == WHITEPIECE || record_board[p1 - 1][y] == WHITETRIANGLE)
                        && (record_board[p2 + 1][y] == WHITEPIECE || record_board[p2 + 1][y] == WHITETRIANGLE)))
                        && (!((record_board[p2 + 1][y] == WHITEPIECE || record_board[p2 + 1][y] == WHITETRIANGLE)
                        && (record_board[p1 - 2][y] == BLACKPIECE || record_board[p1 - 2][y] == BLACKTRIANGLE))))
                        return 1;
                }
                // center
                else
                {
                    if ((record_board[p1 - 1][y] != BLACKPIECE && record_board[p1 - 1][y] != BLACKTRIANGLE
                        && record_board[p2 + 1][y] != BLACKPIECE && record_board[p2 + 1][y] != BLACKTRIANGLE)    
                        && (!((record_board[p1 - 1][y] == WHITEPIECE || record_board[p1 - 1][y] == WHITETRIANGLE)
                        && (record_board[p2 + 1][y] == WHITEPIECE || record_board[p2 + 1][y] == WHITETRIANGLE)))
                        && (!((record_board[p1 - 1][y] == WHITEPIECE || record_board[p1 - 1][y] == WHITETRIANGLE)
                        && (record_board[p2 + 2][y] == BLACKPIECE || record_board[p2 + 2][y] == BLACKTRIANGLE)))
                        && (!((record_board[p1 - 2][y] == BLACKPIECE || record_board[p1 - 2][y] == BLACKTRIANGLE)
                        && (record_board[p2 + 1][y] == WHITEPIECE || record_board[p2 + 1][y] == WHITETRIANGLE)))
                        && (!((record_board[p1 - 2][y] == BLACKPIECE || record_board[p1 - 2][y] == BLACKTRIANGLE)
                        && (record_board[p2 + 2][y] == BLACKPIECE || record_board[p2 + 2][y] == BLACKTRIANGLE))))
                        return 1;
                }
            }
        }
    }

    /********************nonconsecutive active three********************/
    else if (count == 2)
    {
        // the other black piece is in the upside of the two
        if (p1 >= 0 && record_board[p1][y] == 0 && p1 - 1 >= 0
            && (record_board[p1 - 1][y] == BLACKPIECE || record_board[p1 - 1][y] == BLACKTRIANGLE)
            && p1 - 2 >= 0 && record_board[p1 - 2][y] == 0 && p2 < SIZE && record_board[p2][y] == 0)
        {
            if (p1 - 3 >= 0)
            {
                if (record_board[p1 - 3][y] != BLACKPIECE && record_board[p1 - 3][y] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p2 + 1 < SIZE)
                    {
                        if (record_board[p2 + 1][y] != BLACKPIECE && record_board[p2 + 1][y] != BLACKTRIANGLE)
                            return 1;
                    }
                    // bottom of the board
                    else
                        return 1;
                }
            }
            // top of the board
            else if (p2 + 1 < SIZE && record_board[p2 + 1][y] != BLACKPIECE && record_board[p2 + 1][y] != BLACKTRIANGLE)
                return 1;
        }
        // the other black piece is in the downside of the two
        if (p1 >= 0 && record_board[p1][y] == 0 && p2 < SIZE && record_board[p2][y] == 0 && p2 + 1 < SIZE 
            && (record_board[p2 + 1][y] == BLACKPIECE || record_board[p2 + 1][y] == BLACKTRIANGLE)
            && p2 + 2 < SIZE && record_board[p2 + 2][y] == 0)
        {
            if (p2 + 3 < SIZE)
            {
                if (record_board[p2 + 3][y] != BLACKPIECE && record_board[p2 + 3][y] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p1 - 1 >= 0)
                    {
                        if (record_board[p1 - 1][y] != BLACKPIECE && record_board[p1 - 1][y] != BLACKTRIANGLE)
                            return 1;
                    }
                    // top of the board
                    else
                        return 1;
                }
            }
            // bottom of the board
            else if (p1 - 1 >= 0 && record_board[p1 - 1][y] != BLACKPIECE && record_board[p1 - 1][y] != BLACKTRIANGLE)
                return 1;
        }

    }
    else if (count == 1)
    {
        // the other two black pieces are in the upside of this piece
        if (p1 >= 0 && record_board[p1][y] == 0 && p2 < SIZE && record_board[p2][y] == 0
            && p2 + 1 < SIZE && (record_board[p2 + 1][y] == BLACKPIECE || record_board[p2 + 1][y] == BLACKTRIANGLE)
            && p2 + 2 < SIZE && (record_board[p2 + 2][y] == BLACKPIECE || record_board[p2 + 2][y] == BLACKTRIANGLE)
            && p2 + 3 < SIZE && record_board[p2 + 3][y] == 0)
        {
            if (p1 - 1 >= 0)
            {
                if (record_board[p1 - 1][y] != BLACKPIECE && record_board[p1 - 1][y] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p2 + 4 < SIZE)
                    {
                        if (record_board[p2 + 4][y] != BLACKPIECE && record_board[p2 + 4][y] != BLACKTRIANGLE)
                            return 1;
                    }
                    // top of the board
                    else
                        return 1;
                }
            }
            // bottom of the board
            else if (p2 + 4 < SIZE && record_board[p2 + 4][y] != BLACKPIECE && record_board[p2 + 4][y] != BLACKTRIANGLE)
                return 1;
        }
        // if the other two pieces is in the downside of this piece
        if (p2 < SIZE && record_board[p2][y] == 0 && p1 >= 0 && record_board[p1][y] == 0
            && p1 - 1 >= 0 && (record_board[p1 - 1][y] == BLACKPIECE || record_board[p1 - 1][y] == BLACKTRIANGLE)
            && p1 - 2 >= 0 && (record_board[p1 - 2][y] == BLACKPIECE || record_board[p1 - 2][y] == BLACKTRIANGLE)
            && p1 - 3 >= 0 && record_board[p1 - 3][y] == 0)
        {
            if (p2 + 1 < SIZE)
            {
                if (record_board[p2 + 1][y] != BLACKPIECE && record_board[p2 + 1][y] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p1 - 4 >= 0)
                    {
                        if (record_board[p1 - 4][y] != BLACKPIECE && record_board[p1 - 4][y] != BLACKTRIANGLE)
                            return 1;
                    }
                    // top of the board
                    else
                        return 1;
                }
            }
            // bottom of the board
            else if (p1 - 4 >= 0 && record_board[p1 - 4][y] != BLACKPIECE && record_board[p1 - 4][y] != BLACKTRIANGLE)
                return 1;
        }
    }

    /********************no active three found********************/
    return 0;
}

int is_active_three_main_diagonal(int x, int y)
{
    int p1, p2, p3, p4; // these variables are used to store extremities
    int count = count_main_diagonally(x, y, &p1, &p2, &p3, &p4, BLACKPIECE);

    /********************consecutive active three********************/
    if (count == 3)
    {
        if (p1 >= 0 && p3 >= 0 && p2 < SIZE && p4 < SIZE)
        {
            // if one side of the active three is the edge of chess board
            // side I
            if (p1 == 0 || p3 == 0)
            {
                // no side I & side II
                if (p2 < SIZE - 1 && p4 < SIZE - 1)
                {
                    // side I case I
                    if (p2 == SIZE - 2 || p4 == SIZE - 2)
                    {
                        if (record_board[p1][p3] == 0 && record_board[p2][p4] == 0 && record_board[p2 + 1][p4 + 1] == 0)
                            return 1;
                    }
                    // side I case II
                    else
                        if (record_board[p1][p3] == 0 && record_board[p2][p4] == 0 && record_board[p2 + 1][p4 + 1] == 0
                            && record_board[p2 + 2][p4 + 2] != BLACKPIECE && record_board[p2 + 2][p4 + 2] != BLACKTRIANGLE)
                            return 1;
                }
            }
            // side II
            else if (p2 == SIZE - 1 || p4 == SIZE - 1)
            {
                // side II case I
                if (p1 == 1 || p2 == 1)
                {
                    if (record_board[p2][p4] == 0 && record_board[p1][p3] == 0 && record_board[p1 - 1][p3 - 1] == 0)
                        return 1;
                }
                // side II case II
                else
                    if (record_board[p1][p3] == 0 && record_board[p2][p4] == 0 && record_board[p1 - 1][p3 - 1] == 0
                        && record_board[p1 - 2][p3 - 2] != BLACKPIECE && record_board[p1 - 2][p3 - 2] != BLACKTRIANGLE)
                        return 1;
            }
            // if the active three is in the middle of the chess board
            else if (record_board[p1][p3] == 0 && record_board[p2][p4] == 0)
            {
                // near side I
                if (p1 == 1 || p3 == 1)
                {
                    // near side I & near side II
                    if (p2 == SIZE - 2 || p4 == SIZE - 2)
                    {
                        if (record_board[p1 - 1][p3 - 1] != BLACKPIECE && record_board[p2 + 1][p4 + 1] != BLACKTRIANGLE
                            && record_board[p2 + 1][p4 + 1] != BLACKPIECE && record_board[p2 + 1][p4 + 1] != BLACKTRIANGLE
                            && (!((record_board[p1 - 1][p3 - 1] == WHITEPIECE || record_board[p1 - 1][p3 - 1] == WHITETRIANGLE)
                            && (record_board[p2 + 1][p4 + 1] == WHITEPIECE || record_board[p2 + 1][p4 + 1] == WHITETRIANGLE))))
                            return 1;
                    }
                    // near side I
                    else
                    {
                        if (record_board[p1 - 1][p3 - 1] != BLACKPIECE && record_board[p2 + 1][p4 + 1] != BLACKTRIANGLE
                            && record_board[p2 + 1][p4 + 1] != BLACKPIECE && record_board[p2 + 1][p4 + 1] != BLACKTRIANGLE
                            && (!((record_board[p1 - 1][p3 - 1] == WHITEPIECE || record_board[p1 - 1][p3 - 1] == WHITETRIANGLE)
                            && (record_board[p2 + 1][p4 + 1] == WHITEPIECE || record_board[p2 + 1][p4 + 1] == WHITETRIANGLE)))
                            && (!((record_board[p1 - 1][p3 - 1] == WHITEPIECE || record_board[p1 - 1][p3 - 1] == WHITETRIANGLE)
                            && (record_board[p2 + 2][p4 + 2] == BLACKPIECE || record_board[p2 + 2][p4 + 2] == BLACKTRIANGLE))))
                            return 1;
                    }
                }
                // near side II
                else if (p2 == SIZE - 2 && p4 == SIZE - 2)
                {
                    if (record_board[p1 - 1][p3 - 1] != BLACKPIECE && record_board[p2 + 1][p4 + 1] != BLACKTRIANGLE
                        && record_board[p2 + 1][p4 + 1] != BLACKPIECE && record_board[p2 + 1][p4 + 1] != BLACKTRIANGLE
                        && (!((record_board[p1 - 1][p3 - 1] == WHITEPIECE || record_board[p1 - 1][p3 - 1] == WHITETRIANGLE)
                        && (record_board[p2 + 1][p4 + 1] == WHITEPIECE || record_board[p2 + 1][p4 + 1] == WHITETRIANGLE)))
                        && (!((record_board[p1 - 2][p3 - 2] == BLACKPIECE || record_board[p1 - 2][p3 - 2] == BLACKTRIANGLE)
                        && (record_board[p2 + 1][p4 + 1] == WHITEPIECE || record_board[p2 + 1][p4 + 1] == WHITETRIANGLE))))
                        return 1;
                }
                // center
                else
                {
                    if (record_board[p1 - 1][p3 - 1] != BLACKPIECE && record_board[p2 + 1][p4 + 1] != BLACKTRIANGLE
                        && record_board[p2 + 1][p4 + 1] != BLACKPIECE && record_board[p2 + 1][p4 + 1] != BLACKTRIANGLE
                        && (!((record_board[p1 - 1][p3 - 1] == WHITEPIECE || record_board[p1 - 1][p3 - 1] == WHITETRIANGLE)
                        && (record_board[p2 + 1][p4 + 1] == WHITEPIECE || record_board[p2 + 1][p4 + 1] == WHITETRIANGLE)))
                        && (!((record_board[p1 - 2][p3 - 2] == BLACKPIECE || record_board[p1 - 2][p3 - 2] == BLACKTRIANGLE)
                        && (record_board[p2 + 2][p4 + 2] == BLACKPIECE || record_board[p2 + 2][p4 + 2] == BLACKTRIANGLE)))
                        && (!((record_board[p1 - 1][p3 - 1] == WHITEPIECE || record_board[p1 - 1][p3 - 1] == WHITETRIANGLE)
                        && (record_board[p2 + 2][p4 + 2] == BLACKPIECE || record_board[p2 + 2][p4 + 2] == BLACKTRIANGLE)))
                        && (!((record_board[p1 - 2][p3 - 2] == BLACKPIECE || record_board[p1 - 1][p3 - 1] == BLACKTRIANGLE)
                        && (record_board[p2 + 1][p4 + 1] == WHITEPIECE || record_board[p2 + 1][p4 + 1] == WHITETRIANGLE))))
                        return 1;
                }
            }
        }
    }

    /********************nonconsecutive active three********************/
    else if (count == 2)
    {
        // the other black piece is in the top left of the two
        if (p1 >= 0 && p3 >= 0 && record_board[p1][p3] == 0 
            && p1 - 1 >= 0 && p3 - 1 >= 0
            && (record_board[p1 - 1][p3 - 1] == BLACKPIECE || record_board[p1 - 1][p3 - 1] == BLACKTRIANGLE)
            && p1 - 2 >= 0 && p3 - 2 >= 0 && record_board[p1 - 2][p3 - 2] == 0
            && p2 < SIZE && p4 < SIZE && record_board[p2][p4] == 0)
        {
            if (p1 - 3 >= 0 && p3 - 3 >= 0)
            {
                if (record_board[p1 - 3][p3 - 3] != BLACKPIECE && record_board[p1 - 3][p3 - 3] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p2 + 1 < SIZE && p4 + 1 < SIZE)
                    {
                        if (record_board[p2 + 1][p4 + 1] != BLACKPIECE && record_board[p2 + 1][p4 + 1] != BLACKTRIANGLE)
                            return 1;
                    }
                    // bottom right of the board
                    else
                        return 1;
                }
            }
            // top left corner of the board
            else if (p2 + 1 < SIZE && p4 + 1 < SIZE 
                     && record_board[p2 + 1][p4 + 1] != BLACKPIECE && record_board[p2 + 1][p4 + 1] != BLACKTRIANGLE)
                return 1;
        }
        // the other black piece is in the bottom right corner of the two
        if (p1 >= 0 && p3 >= 0 && record_board[p1][p3] == 0 
            && p2 < SIZE && p4 < SIZE && record_board[p2][p4] == 0
            && p2 + 1 < SIZE && p4 + 1 < SIZE
            && (record_board[p2 + 1][p4 + 1] == BLACKPIECE || record_board[p2 + 1][p4 + 1] == BLACKTRIANGLE)
            && p2 + 2 < SIZE && p4 + 2 < SIZE && record_board[p2 + 2][p4 + 2] == 0)
        {
            if (p2 + 3 < SIZE && p4 + 3 < SIZE)
            {
                if (record_board[p2 + 3][p4 + 3] != BLACKPIECE && record_board[p2 + 3][p4 + 3] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p1 - 1 >= 0 && p3 - 1 >= 0)
                    {
                        if (record_board[p1 - 1][p3 - 1] != BLACKPIECE && record_board[p1 - 1][p3 - 1] != BLACKTRIANGLE)
                            return 1;
                    }
                    // top left corner of the board
                    else
                        return 1;
                }
            }
            // bottom right corner of the board
            else if (p1 - 1 >= 0  && p3 - 1 >= 0 
                     && record_board[p1 - 1][p3 - 1] != BLACKPIECE && record_board[p1 - 1][p3 - 1] != BLACKTRIANGLE)
                return 1;
        }

    }
    else if (count == 1)
    {
        // the other two black pieces are in the top left of this piece
        if (p1 >= 0 && p3 >= 0 && record_board[p1][p3] == 0 
            && p2 < SIZE && p4 < SIZE && record_board[p2][p4] == 0
            && p2 + 1 < SIZE && p4 + 1 < SIZE 
            && (record_board[p2 + 1][p4 + 1] == BLACKPIECE || record_board[p2 + 1][p4 + 1] == BLACKTRIANGLE)
            && p2 + 2 < SIZE && p4 + 2 < SIZE
            && (record_board[p2 + 2][p4 + 2] == BLACKPIECE || record_board[p2 + 2][p4 + 2] == BLACKTRIANGLE)
            && p2 + 3 < SIZE && p4 + 3 < SIZE && record_board[p2 + 3][p4 + 3] == 0)
        {
            if (p1 - 1 >= 0 && p3 - 1 >= 0)
            {
                if (record_board[p1 - 1][p3 - 1] != BLACKPIECE && record_board[p1 - 1][p3 - 1] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p2 + 4 < SIZE && p4 + 4 < SIZE)
                    {
                        if (record_board[p2 + 4][p4 + 4] != BLACKPIECE && record_board[p2 + 4][p4 + 4] != BLACKTRIANGLE)
                            return 1;
                    }
                    // top left of the board
                    else
                        return 1;
                }
            }
            // bottom right of the board
            else if (p2 + 4 < SIZE  && p4 + 4 < SIZE 
                     && record_board[p2 + 4][p4 + 4] != BLACKPIECE && record_board[p2 + 4][p4 + 4] != BLACKTRIANGLE)
                return 1;
        }
        // if the other two pieces is in the bottom right of this piece
        if (p2 < SIZE && p4 < SIZE && record_board[p2][p4] == 0 
            && p1 >= 0 && p3 >= 0 && record_board[p1][p3] == 0
            && p1 - 1 >= 0 && p3 - 1 >= 0
            && (record_board[p1 - 1][p3 - 1] == BLACKPIECE || record_board[p1 - 1][p3 - 1] == BLACKTRIANGLE)
            && p1 - 2 >= 0 && p3 - 2 >= 0
            && (record_board[p1 - 2][p3 - 2] == BLACKPIECE || record_board[p1 - 2][p3 - 2] == BLACKTRIANGLE)
            && p1 - 3 >= 0 && p3 - 3 >= 0 && record_board[p1 - 3][p3 - 3] == 0)
        {
            if (p2 + 1 < SIZE && p4 + 1 < SIZE)
            {
                if (record_board[p2 + 1][p4 + 1] != BLACKPIECE && record_board[p2 + 1][p4 + 1] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p1 - 4 >= 0 && p3 - 4 >= 0)
                    {
                        if (record_board[p1 - 4][p3 - 4] != BLACKPIECE && record_board[p1 - 4][p3 - 4] != BLACKTRIANGLE)
                            return 1;
                    }
                    // top left of the board
                    else
                        return 1;
                }
            }
            // bottom right of the board
            else if (p1 - 4 >= 0 && p3 - 4 >= 0
                     && record_board[p1 - 4][p3 - 4] != BLACKPIECE && record_board[p1 - 4][p3 - 4] != BLACKTRIANGLE)
                return 1;
        }
    }
    
    /********************no active three found********************/
    return 0;
}

int is_active_three_sub_diagonal(int x, int y)
{
    int p1, p2, p3, p4; // these variables are used to store extremities
    int count = count_sub_diagonally(x, y, &p1, &p2, &p3, &p4, BLACKPIECE);

    /********************consecutive active three********************/
    if (count == 3)
    {
        if (p1 >= 0 && p4 >= 0 && p2 < SIZE && p3 < SIZE)
        {
            // if one side of the active three is the edge of chess board
            // side I
            if (p1 == 0 || p3 == SIZE - 1)
            {
                // no side I & side II
                if (p2 < SIZE - 1 || p4 > 0)
                {
                    // side I case I
                    if (p2 == SIZE - 2 || p4 == 1)
                    {
                        if (record_board[p1][p3] == 0 && record_board[p2][p4] == 0 && record_board[p2 + 1][p4 - 1] == 0)
                            return 1;
                    }
                    // side I case II
                    else
                    {
                        if (record_board[p1][p3] == 0 && record_board[p2][p4] == 0 && record_board[p2 + 1][p4 - 1] == 0
                            && record_board[p2 + 2][p4 - 2] != BLACKPIECE && record_board[p2 + 2][p4 - 2] != BLACKTRIANGLE)
                            return 1;
                    }
                }
            }
            // side II
            else if (p2 == SIZE - 1 || p4 == 0)
            {
                // side II case I
                if (p1 == 1 || p3 == SIZE - 2)
                {
                    if (record_board[p2][p4] == 0 && record_board[p1][p3] == 0 && record_board[p1 - 1][p3 + 1] == 0)
                        return 1;
                }
                // side II case II
                else
                {
                    if (record_board[p2][p4] == 0 && record_board[p1][p3] == 0 && record_board[p1 - 1][p3 + 1] == 0
                        && record_board[p1 - 2][p3 + 2] != BLACKPIECE && record_board[p1 - 2][p3 + 2] != BLACKTRIANGLE)
                        return 1;
                }
            }
            // if the active three is in the middle of the chess board
            else if (record_board[p1][p3] == 0 && record_board[p2][p4] == 0)
            {
                // near side I
                if (p2 == SIZE - 2 || p4 == 1)
                {
                    // near side I & near side II
                    if (p1 == 1 || p3 == SIZE - 2)
                    {
                        if (record_board[p1 - 1][p3 + 1] != BLACKPIECE && record_board[p1 - 1][p3 + 1] != BLACKTRIANGLE
                            && record_board[p2 + 1][p4 - 1] != BLACKPIECE && record_board[p2 + 1][p4 - 1] != BLACKTRIANGLE
                            && (!((record_board[p1 - 1][p3 + 1] == WHITEPIECE || record_board[p1 - 1][p3 + 1] == WHITETRIANGLE)
                            && (record_board[p2 + 1][p4 - 1] == WHITEPIECE || record_board[p2 + 1][p4 - 1] == WHITETRIANGLE))))
                            return 1;
                    }
                    // near side I
                    else
                    {
                        if (record_board[p1 - 1][p3 + 1] != BLACKPIECE && record_board[p1 - 1][p3 + 1] != BLACKTRIANGLE
                            && record_board[p2 + 1][p4 - 1] != BLACKPIECE && record_board[p2 + 1][p4 - 1] != BLACKTRIANGLE
                            && (!((record_board[p1 - 1][p3 + 1] == WHITEPIECE || record_board[p1 - 1][p3 + 1] == WHITETRIANGLE)
                            && (record_board[p2 + 1][p4 - 1] == WHITEPIECE || record_board[p2 + 1][p4 - 1] == WHITETRIANGLE)))
                            && (!((record_board[p1 - 2][p3 + 2] == BLACKPIECE || record_board[p1 - 2][p3 + 2] == BLACKTRIANGLE)
                            && (record_board[p2 + 1][p4 - 1] == WHITEPIECE || record_board[p2 + 1][p4 - 1] == WHITETRIANGLE))))
                            return 1;
                    }
                }
                // near side II
                else if (p1 == 1 || p3 == SIZE - 2)
                {
                    if (record_board[p1 - 1][p3 + 1] != BLACKPIECE && record_board[p1 - 1][p3 + 1] != BLACKTRIANGLE
                        && record_board[p2 + 1][p4 - 1] != BLACKPIECE && record_board[p2 + 1][p4 - 1] != BLACKTRIANGLE
                        && (!((record_board[p1 - 1][p3 + 1] == WHITEPIECE || record_board[p1 - 1][p3 + 1] == WHITETRIANGLE)
                        && (record_board[p2 + 1][p4 - 1] == WHITEPIECE || record_board[p2 + 1][p4 - 1] == WHITETRIANGLE)))
                        && (!((record_board[p1 - 1][p3 + 1] == WHITEPIECE || record_board[p1 - 1][p3 + 1] == WHITETRIANGLE)
                        && (record_board[p2 + 2][p4 - 2] == BLACKPIECE || record_board[p2 + 1][p4 - 1] == BLACKTRIANGLE))))
                            return 1;
                }
                // center
                else
                {
                    if (record_board[p1 - 1][p3 + 1] != BLACKPIECE && record_board[p1 - 1][p3 + 1] != BLACKTRIANGLE
                        && record_board[p2 + 1][p4 - 1] != BLACKPIECE && record_board[p2 + 1][p4 - 1] != BLACKTRIANGLE
                        && (!((record_board[p1 - 1][p3 + 1] == WHITEPIECE || record_board[p1 - 1][p3 + 1] == WHITETRIANGLE)
                        && (record_board[p2 + 1][p4 - 1] == WHITEPIECE || record_board[p2 + 1][p4 - 1] == WHITETRIANGLE)))
                        && (!((record_board[p1 - 2][p3 + 2] == BLACKPIECE || record_board[p1 - 2][p3 + 2] == BLACKTRIANGLE)
                        && (record_board[p2 + 2][p4 - 2] == BLACKPIECE || record_board[p2 + 2][p4 - 2] == BLACKTRIANGLE)))
                        && (!((record_board[p1 - 1][p3 + 1] == WHITEPIECE || record_board[p1 - 1][p3 + 1] == WHITETRIANGLE)
                        && (record_board[p2 + 2][p4 - 2] == BLACKPIECE || record_board[p2 + 1][p4 - 1] == BLACKTRIANGLE)))
                        && (!((record_board[p1 - 1][p3 + 1] == WHITEPIECE || record_board[p1 - 1][p3 + 1] == WHITETRIANGLE)
                        && (record_board[p2 + 2][p4 - 2] == BLACKPIECE || record_board[p2 + 2][p4 - 2] == BLACKTRIANGLE))))
                            return 1;
                }    
            }
        }
    }

    /********************nonconsecutive active three********************/
    else if (count == 2)
    {
        // the other black piece is in the top right of the two
        if (p1 >= 0 && p3 < SIZE && record_board[p1][p3] == 0 
            && p1 - 1 >= 0 && p3 + 1 < SIZE
            && (record_board[p1 - 1][p3 + 1] == BLACKPIECE || record_board[p1 - 1][p3 + 1] == BLACKTRIANGLE)
            && p1 - 2 >= 0 && p3 + 2 < SIZE && record_board[p1 - 2][p3 + 2] == 0
            && p2 < SIZE && p4 >= 0 && record_board[p2][p4] == 0)
        {
            if (p1 - 3 >= 0 && p3 + 3 < SIZE)
            {
                if (record_board[p1 - 3][p3 + 3] != BLACKPIECE && record_board[p1 - 3][p3 + 3] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p2 + 1 < SIZE && p4 - 1 >= 0)
                    {
                        if (record_board[p2 + 1][p4 - 1] != BLACKPIECE && record_board[p2 + 1][p4 - 1] != BLACKTRIANGLE)
                            return 1;
                    }
                    // bottom left of the board
                    else
                        return 1;
                }
            }
            // top right corner of the board
            else if (p2 + 1 < SIZE && p4 - 1 >= 0 
                     && record_board[p2 + 1][p4 - 1] != BLACKPIECE && record_board[p2 + 1][p4 - 1] != BLACKTRIANGLE)
                return 1;
        }
        // the other black piece is in the bottom left corner of the two
        if (p1 >= 0 && p3 < SIZE && record_board[p1][p3] == 0 
            && p2 < SIZE && p4 >= 0 && record_board[p2][p4] == 0
            && p2 + 1 < SIZE && p4 - 1 >= 0
            && (record_board[p2 + 1][p4 - 1] == BLACKPIECE || record_board[p2 + 1][p4 - 1] == BLACKTRIANGLE)
            && p2 + 2 < SIZE && p4 - 2 >= 0 && record_board[p2 + 2][p4 - 2] == 0)
        {
            if (p2 + 3 < SIZE && p4 - 3 >= 0)
            {
                if (record_board[p2 + 3][p4 - 3] != BLACKPIECE && record_board[p2 + 3][p4 - 3] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p1 - 1 >= 0 && p3 + 1 < SIZE)
                    {
                        if (record_board[p1 - 1][p3 + 1] != BLACKPIECE && record_board[p1 - 1][p3 - 1] != BLACKTRIANGLE)
                            return 1;
                    }
                    // top right corner of the board
                    else
                        return 1;
                }
            }
            // bottom left corner of the board
            else if (p1 - 1 >= 0  && p3 + 1 < SIZE 
                     && record_board[p1 - 1][p3 + 1] != BLACKPIECE && record_board[p1 - 1][p3 + 1] != BLACKTRIANGLE)
                return 1;
        }

    }
    else if (count == 1)
    {
        // the other two black pieces are in the top right of this piece
        if (p1 >= 0 && p3 < SIZE && record_board[p1][p3] == 0 
            && p2 < SIZE && p4 >= 0 && record_board[p2][p4] == 0
            && p2 + 1 < SIZE && p4 - 1 >= 0 
            && (record_board[p2 + 1][p4 - 1] == BLACKPIECE || record_board[p2 + 1][p4 - 1] == BLACKTRIANGLE)
            && p2 + 2 < SIZE && p4 - 2 >= 0
            && (record_board[p2 + 2][p4 - 2] == BLACKPIECE || record_board[p2 + 2][p4 - 2] == BLACKTRIANGLE)
            && p2 + 3 < SIZE && p4 - 3 >= 0 && record_board[p2 + 3][p4 - 3] == 0)
        {
            if (p1 - 1 >= 0 && p3 + 1 < SIZE)
            {
                if (record_board[p1 - 1][p3 + 1] != BLACKPIECE && record_board[p1 - 1][p3 + 1] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p2 + 4 < SIZE && p4 - 4 >= 0)
                    {
                        if (record_board[p2 + 4][p4 - 4] != BLACKPIECE && record_board[p2 + 4][p4 - 4] != BLACKTRIANGLE)
                            return 1;
                    }
                    // top right of the board
                    else
                        return 1;
                }
            }
            // bottom left of the board
            else if (p2 + 4 < SIZE  && p4 - 4 >= 0 
                     && record_board[p2 + 4][p4 - 4] != BLACKPIECE && record_board[p2 + 4][p4 - 4] != BLACKTRIANGLE)
                return 1;
        }
        // if the other two pieces is in the bottom left of this piece
        if (p2 < SIZE && p4 >= 0 && record_board[p2][p4] == 0 
            && p1 >= 0 && p3 < SIZE && record_board[p1][p3] == 0
            && p1 - 1 >= 0 && p3 + 1 < SIZE
            && (record_board[p1 - 1][p3 + 1] == BLACKPIECE || record_board[p1 - 1][p3 + 1] == BLACKTRIANGLE)
            && p1 - 2 >= 0 && p3 + 2 < SIZE
            && (record_board[p1 - 2][p3 + 2] == BLACKPIECE || record_board[p1 - 2][p3 + 2] == BLACKTRIANGLE)
            && p1 - 3 >= 0 && p3 + 3 < SIZE && record_board[p1 - 3][p3 + 3] == 0)
        {
            if (p2 + 1 < SIZE && p4 - 1 >= 0)
            {
                if (record_board[p2 + 1][p4 - 1] != BLACKPIECE && record_board[p2 + 1][p4 - 1] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p1 - 4 >= 0 && p3 + 4 < SIZE)
                    {
                        if (record_board[p1 - 4][p3 + 4] != BLACKPIECE && record_board[p1 - 4][p3 + 4] != BLACKTRIANGLE)
                            return 1;
                    }
                    // top right of the board
                    else
                        return 1;
                }
            }
            // bottom left of the board
            else if (p1 - 4 >= 0 && p3 + 4 >= 0
                     && record_board[p1 - 4][p3 + 4] != BLACKPIECE && record_board[p1 - 4][p3 + 4] != BLACKTRIANGLE)
                return 1;
        }
    }
    /********************no active three found********************/
    return 0;
}

int is_over_one_active_three(int x, int y)
{
    int res = 0;
    res += is_active_three_horizontal(x, y);
    res += is_active_three_vertical(x, y);
    res += is_active_three_main_diagonal(x, y);
    res += is_active_three_sub_diagonal(x, y);

    if (res > 1)
        return 1;
    return 0;
}


int is_four_horizontal(int x, int y)
{
    int p1, p2; // these variables are used to store extremities
    int count = count_horizontally(x, y, &p1, &p2, BLACKPIECE);

    /********************consecutive four********************/
    if (count == 4)
    {
        // left side of the board
        if (p1 == -1)
        {
            if (record_board[x][p2] == 0 && record_board[x][p2 + 1] != BLACKPIECE && record_board[x][p2 + 1] != BLACKTRIANGLE)
                return 1;
        }
        // right side of the board
        else if (p2 == SIZE)
        {
            if (record_board[x][p1] == 0 && record_board[x][p1 - 1] != BLACKPIECE && record_board[x][p1 - 1] != BLACKPIECE)
                return 1;
        }
        // in the middle of the board
        else
        {
            if (!((record_board[x][p1] == WHITEPIECE || record_board[x][p1] == WHITETRIANGLE)
                && (record_board[x][p2] == WHITEPIECE || record_board[x][p2] == WHITETRIANGLE)))
            {
                // near left side of the board
                if (p1 == 0)
                {
                    if ((record_board[x][p1] == WHITEPIECE || record_board[x][p1] == WHITETRIANGLE) && record_board[x][p2] == 0 
                        && record_board[x][p2 + 1] != BLACKPIECE && record_board[x][p2 + 1] != BLACKTRIANGLE)
                        return 1;
                    else if ((record_board[x][p2] == WHITEPIECE || record_board[x][p2] == WHITETRIANGLE) && record_board[x][p1] == 0)
                        return 1;
                    else if (record_board[x][p1] == 0 && record_board[x][p2] == 0)
                        return 1;
                }
                // near right side of the board
                else if (p2 == SIZE - 1)
                {
                    if ((record_board[x][p2] == WHITEPIECE || record_board[x][p2] == WHITETRIANGLE) && record_board[x][p1] == 0
                        && record_board[x][p1 - 1] != BLACKPIECE && record_board[x][p1 - 1] != BLACKTRIANGLE)
                        return 1;
                    else if ((record_board[x][p2] == WHITEPIECE || record_board[x][p2] == WHITETRIANGLE) && record_board[x][p2] == 0)
                        return 1;
                    else if (record_board[x][p2] == 0 && record_board[x][p1] == 0)
                        return 1;
                }
                // center of the board
                else
                {
                    if ((!((record_board[x][p1] == WHITEPIECE || record_board[x][p1] == WHITETRIANGLE)
                        && (record_board[x][p2] == WHITEPIECE || record_board[x][p2] == WHITETRIANGLE)))
                        && (!((record_board[x][p1 - 1] == BLACKPIECE || record_board[x][p1 - 1] == BLACKTRIANGLE)
                        && (record_board[x][p2 + 1] == BLACKPIECE || record_board[x][p2 + 1] == BLACKTRIANGLE)))
                        && (!((record_board[x][p1] == WHITEPIECE || record_board[x][p1] == WHITETRIANGLE)
                        && (record_board[x][p2 + 1] == BLACKPIECE || record_board[x][p2 + 1] == BLACKTRIANGLE)))
                        && (!((record_board[x][p1 - 1] == BLACKPIECE || record_board[x][p1 - 1] == BLACKTRIANGLE)
                        && (record_board[x][p2] == WHITEPIECE || record_board[x][p2] == WHITETRIANGLE))))
                        return 1;
                }
            }
        }
    }

    /********************nonconsecutive four********************/
    else if (count == 3)
    {
        // the other piece is in the left of the three
        if (p1 >= 0 && record_board[x][p1] == 0 
            && p1 - 1 >= 0 && (record_board[x][p1 - 1] == BLACKPIECE || record_board[x][p1 - 1] == BLACKTRIANGLE))
        {
            if (p1 - 2 >= 0)
            {
                if (record_board[x][p1 - 2] != BLACKPIECE && record_board[x][p1 - 2] != BLACKTRIANGLE)
                    return 1;
            }
            // left side of the board
            else 
                return 1;
        }
        // the other piece is in the right side of the piece
        else if (p2 < SIZE && record_board[x][p2] == 0
                 && p2 + 1 < SIZE && (record_board[x][p2 + 1] == BLACKPIECE || record_board[x][p2 + 1] == BLACKTRIANGLE))
        {
            if (p2 + 2 < SIZE)
            {
                if (record_board[x][p2 + 2] != BLACKPIECE && record_board[x][p2 + 2] != BLACKTRIANGLE)
                    return 1;
            }
            else
                return 1;
        }
    }

    else if (count == 1)
    {
        // the other three pieces is in the right of this piece
        if (p2 < SIZE && record_board[x][p2] == 0
            && p2 + 1 < SIZE && (record_board[x][p2 + 1] == BLACKPIECE || record_board[x][p2 + 1] == BLACKTRIANGLE)
            && p2 + 2 < SIZE && (record_board[x][p2 + 2] == BLACKPIECE || record_board[x][p2 + 2] == BLACKTRIANGLE)
            && p2 + 3 < SIZE && (record_board[x][p2 + 3] == BLACKPIECE || record_board[x][p2 + 3] == BLACKTRIANGLE))
        {
            if (p1 >= 0)
            {
                if (record_board[x][p1] != BLACKPIECE && record_board[x][p1] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p2 + 4 < SIZE)
                    {
                        if (record_board[x][p2 + 4] != BLACKPIECE && record_board[x][p2 + 4] != BLACKTRIANGLE)
                            return 1;
                    }
                    // right side of the board
                    else
                        return 1;
                }
            }
            // left side of the board
            else if (p2 + 4 < SIZE && record_board[x][p2 + 4] != BLACKPIECE && record_board[x][p2 + 4] != BLACKTRIANGLE)
                return 1;
        }
        // the other three pieces is in the left of this piece
        else if (p1 >= 0 && record_board[x][p1] == 0
                && p1 - 1 >= 0 && (record_board[x][p1 - 1] == BLACKPIECE || record_board[x][p1 - 1] == BLACKTRIANGLE)
                && p1 - 2 >= 0 && (record_board[x][p1 - 2] == BLACKPIECE || record_board[x][p1 - 2] == BLACKTRIANGLE)
                && p1 - 3 >= 0 && (record_board[x][p1 - 3] == BLACKPIECE || record_board[x][p1 - 3] == BLACKTRIANGLE))
        {
            if (p1 - 4 >= 0)
            {
                if (record_board[x][p1 - 4] != BLACKPIECE && record_board[x][p1 - 4] != BLACKTRIANGLE)
                {
                    if (p2 < SIZE)
                    {
                        if (record_board[x][p2] != BLACKPIECE && record_board[x][p2] != BLACKTRIANGLE)
                            return 1;
                    }
                    else
                        return 1;
                }
            }
            else if (p2 < SIZE && record_board[x][p2] != BLACKPIECE && record_board[x][p2] != BLACKTRIANGLE)
                return 1;
        }
    }
    else if (count == 2)
    {
        // the other two pieces is in the left of these two pieces
        if (p1 >= 0 && record_board[x][p1] == 0
            && p1 - 1 >= 0 && (record_board[x][p1 - 1] == BLACKPIECE || record_board[x][p1 - 1] == BLACKTRIANGLE)
            && p1 - 2 >= 0 && (record_board[x][p1 - 2] == BLACKPIECE || record_board[x][p1 - 2] == BLACKTRIANGLE))
        {
            if (p1 - 3 >= 0)
            {
                if (record_board[x][p1 - 3] != BLACKPIECE && record_board[x][p1 - 3] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p2 < SIZE)
                    {
                        if (record_board[x][p2] != BLACKPIECE && record_board[x][p2] != BLACKTRIANGLE)
                            return 1;
                    }
                    // right side of the board
                    else
                        return 1;
                }
            }
            // left side of the board
            else if (p2 < SIZE && record_board[x][p2] != BLACKPIECE && record_board[x][p2] != BLACKTRIANGLE)
                return 1;
        }
        // the other two pieces is in the right side of these two pieces
        if (p2 < SIZE && record_board[x][p2] == 0
            && p2 + 1 < SIZE && (record_board[x][p2 + 1] == BLACKPIECE || record_board[x][p2 + 1] == BLACKTRIANGLE)
            && p2 + 2 >= 0 && (record_board[x][p2 + 2] == BLACKPIECE || record_board[x][p2 + 2] == BLACKTRIANGLE))
        {
            if (p2 + 3 < SIZE)
            {
                if (record_board[x][p2 + 3] != BLACKPIECE && record_board[x][p2 + 3] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p1 >= 0)
                    {
                        if (record_board[x][p1] != BLACKPIECE && record_board[x][p1] != BLACKTRIANGLE)
                            return 1;
                    }
                    // left side of the board
                    else
                        return 1;
                }
            }
            // right side of the board
            else if (p1 >= 0 && record_board[x][p1] != BLACKPIECE && record_board[x][p1] != BLACKTRIANGLE)
                return 1;
        }
    }

    /********** no fours found**********/
    return 0;
}

int is_four_vertical(int x, int y)
{
    int p1, p2; // these variables are used to store extremities
    int count = count_vertically(x, y, &p1, &p2, BLACKPIECE);

    /********************consecutive four********************/
    if (count == 4)
    {
        // top of the board
        if (p1 == -1)
        {
            if (record_board[p2][y] == 0 && record_board[p2 + 1][y] != BLACKPIECE && record_board[p2 + 1][y] != BLACKTRIANGLE)
                return 1;
        }
        // bottom of the board
        else if (p2 == SIZE)
        {
            if (record_board[p1][y] == 0 && record_board[p1 - 1][y] != BLACKPIECE && record_board[p1 - 1][y] != BLACKPIECE)
                return 1;
        }
        // in the middle of the board
        else
        {
            if (!((record_board[p1][y] == WHITEPIECE || record_board[p1][y] == WHITETRIANGLE)
                && (record_board[p2][y] == WHITEPIECE || record_board[p2][y] == WHITETRIANGLE)))
            {
                // near top of the board
                if (p1 == 0)
                {
                    if ((record_board[p1][y] == WHITEPIECE || record_board[p1][y] == WHITETRIANGLE) && record_board[p2][y] == 0 
                        && record_board[p2 + 1][y] != BLACKPIECE && record_board[p2 + 1][y] != BLACKTRIANGLE)
                        return 1;
                    else if ((record_board[p2][y] == WHITEPIECE || record_board[p2][y] == WHITETRIANGLE) && record_board[p1][y] == 0)
                        return 1;
                    else if (record_board[p1][y] == 0 && record_board[p2][y] == 0)
                        return 1;
                }
                // near bottom of the board
                else if (p2 == SIZE - 1)
                {
                    if ((record_board[p2][y] == WHITEPIECE || record_board[p2][y] == WHITETRIANGLE) && record_board[p1][y] == 0
                        && record_board[p1 - 1][y] != BLACKPIECE && record_board[p1 - 1][y] != BLACKTRIANGLE)
                        return 1;
                    else if ((record_board[p2][y] == WHITEPIECE || record_board[p2][y] == WHITETRIANGLE) && record_board[p2][y] == 0)
                        return 1;
                    else if (record_board[p2][y] == 0 && record_board[p1][y] == 0)
                        return 1;
                }
                // center of the board
                else
                {
                    if ((!((record_board[p1][y] == WHITEPIECE || record_board[p1][y] == WHITETRIANGLE)
                        && (record_board[p2][y] == WHITEPIECE || record_board[p2][y] == WHITETRIANGLE)))
                        && (!((record_board[p1 - 1][y] == BLACKPIECE || record_board[p1 - 1][y] == BLACKTRIANGLE)
                        && (record_board[p2 + 1][y] == BLACKPIECE || record_board[p2 + 1][y] == BLACKTRIANGLE)))
                        && (!((record_board[p1][y] == WHITEPIECE || record_board[p1][y] == WHITETRIANGLE)
                        && (record_board[p2 + 1][y] == BLACKPIECE || record_board[p2 + 1][y] == BLACKTRIANGLE)))
                        && (!((record_board[p1 - 1][y] == BLACKPIECE || record_board[p1 - 1][y] == BLACKTRIANGLE)
                        && (record_board[p2][y] == WHITEPIECE || record_board[p2][y] == WHITETRIANGLE))))
                        return 1;
                }
            }
        }
    }

    /********************nonconsecutive four********************/
    else if (count == 3)
    {
        // the other piece is in the top of the three
        if (p1 >= 0 && record_board[p1][y] == 0 
            && p1 - 1 >= 0 && (record_board[p1 - 1][y] == BLACKPIECE || record_board[p1 - 1][y] == BLACKTRIANGLE))
        {
            if (p1 - 2 >= 0)
            {
                if (record_board[p1 - 2][y] != BLACKPIECE && record_board[p1 - 2][y] != BLACKTRIANGLE)
                    return 1;
            }
            // top of the board
            else 
                return 1;
        }
        // the other piece is in the bottom of the piece
        else if (p2 < SIZE && record_board[p2][y] == 0
                 && p2 + 1 < SIZE && (record_board[p2 + 1][y] == BLACKPIECE || record_board[p2 + 1][y] == BLACKTRIANGLE))
        {
            if (p2 + 2 < SIZE)
            {
                if (record_board[p2 + 2][y] != BLACKPIECE && record_board[p2 + 2][y] != BLACKTRIANGLE)
                    return 1;
            }
            else
                return 1;
        }
    }

    else if (count == 1)
    {
        // the other three pieces is in the right of this piece
        if (p2 < SIZE && record_board[p2][y] == 0
            && p2 + 1 < SIZE && (record_board[p2 + 1][y] == BLACKPIECE || record_board[p2 + 1][y] == BLACKTRIANGLE)
            && p2 + 2 < SIZE && (record_board[p2 + 2][y] == BLACKPIECE || record_board[p2 + 2][y] == BLACKTRIANGLE)
            && p2 + 3 < SIZE && (record_board[p2 + 3][y] == BLACKPIECE || record_board[p2 + 3][y] == BLACKTRIANGLE))
        {
            if (p1 >= 0)
            {
                if (record_board[p1][y] != BLACKPIECE && record_board[p1][y] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p2 + 4 < SIZE)
                    {
                        if (record_board[p2 + 4][y] != BLACKPIECE && record_board[p2 + 4][y] != BLACKTRIANGLE)
                            return 1;
                    }
                    // bottom of the board
                    else
                        return 1;
                }
            }
            // left side of the board
            else if (p2 + 4 < SIZE && record_board[p2 + 4][y] != BLACKPIECE && record_board[p2 + 4][y] != BLACKTRIANGLE)
                return 1;
        }
        // the other three pieces is in the left of this piece
        else if (p1 >= 0 && record_board[p1][y] == 0
                && p1 - 1 >= 0 && (record_board[p1 - 1][y] == BLACKPIECE || record_board[p1 - 1][y] == BLACKTRIANGLE)
                && p1 - 2 >= 0 && (record_board[p1 - 2][y] == BLACKPIECE || record_board[p1 - 2][y] == BLACKTRIANGLE)
                && p1 - 3 >= 0 && (record_board[p1 - 3][y] == BLACKPIECE || record_board[p1 - 3][y] == BLACKTRIANGLE))
        {
            if (p1 - 4 >= 0)
            {
                if (record_board[p1 - 4][y] != BLACKPIECE && record_board[p1 - 4][y] != BLACKTRIANGLE)
                {
                    if (p2 < SIZE)
                    {
                        if (record_board[p2][y] != BLACKPIECE && record_board[p2][y] != BLACKTRIANGLE)
                            return 1;
                    }
                    else
                        return 1;
                }
            }
            else if (p2 < SIZE && record_board[p2][y] != BLACKPIECE && record_board[p2][y] != BLACKTRIANGLE)
                return 1;
        }
    }
    else if (count == 2)
    {
        // the other two pieces is in the left of these two pieces
        if (p1 >= 0 && record_board[p1][y] == 0
            && p1 - 1 >= 0 && (record_board[p1 - 1][y] == BLACKPIECE || record_board[p1 - 1][y] == BLACKTRIANGLE)
            && p1 - 2 >= 0 && (record_board[p1 - 2][y] == BLACKPIECE || record_board[p1 - 2][y] == BLACKTRIANGLE))
        {
            if (p1 - 3 >= 0)
            {
                if (record_board[p1 - 3][y] != BLACKPIECE && record_board[p1 - 3][y] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p2 < SIZE)
                    {
                        if (record_board[p2][y] != BLACKPIECE && record_board[p2][y] != BLACKTRIANGLE)
                            return 1;
                    }
                    // bottom of the board
                    else
                        return 1;
                }
            }
            // left side of the board
            else if (p2 < SIZE && record_board[p2][y] != BLACKPIECE && record_board[p2][y] != BLACKTRIANGLE)
                return 1;
        }
        // the other two pieces is in the bottom of these two pieces
        if (p2 < SIZE && record_board[p2][y] == 0
            && p2 + 1 < SIZE && (record_board[p2 + 1][y] == BLACKPIECE || record_board[p2 + 1][y] == BLACKTRIANGLE)
            && p2 + 2 >= 0 && (record_board[p2 + 2][y] == BLACKPIECE || record_board[p2 + 2][y] == BLACKTRIANGLE))
        {
            if (p2 + 3 < SIZE)
            {
                if (record_board[p2 + 3][y] != BLACKPIECE && record_board[p2 + 3][y] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p1 >= 0)
                    {
                        if (record_board[p1][y] != BLACKPIECE && record_board[p1][y] != BLACKTRIANGLE)
                            return 1;
                    }
                    // top of the board
                    else
                        return 1;
                }
            }
            // bottom of the board
            else if (p1 >= 0 && record_board[p1][y] != BLACKPIECE && record_board[p1][y] != BLACKTRIANGLE)
                return 1;
        }
    }

    /********** no fours found**********/
    return 0;
}

int is_four_main_diagonal(int x, int y)
{
    int p1, p2, p3, p4; // these variables are used to store extremities
    int count = count_main_diagonally(x, y, &p1, &p2, &p3, &p4, BLACKPIECE);

    /********************consecutive four********************/
    if (count == 4)
    {
        // top left of the board
        if (p1 == -1 || p3 == -1)
        {   
            // special case I
            if (p2 != SIZE && p4 != SIZE && record_board[p2][p4] == 0)
            {
                if (p2 + 1 < SIZE && p4 + 1 < SIZE)
                {
                    if (record_board[p2 + 1][p4 + 1] != BLACKPIECE && record_board[p2 + 1][p4 + 1] != BLACKTRIANGLE)
                        return 1;
                }
                else
                    return 1;
            }
        }
        // bottom right of the board
        else if (p2 == SIZE || p4 == SIZE)
        {
            if (record_board[p1][p3] == 0)
            {
                if (p1 - 1 >= 0 && p3 - 1 >= 0)
                {
                    if (record_board[p1 - 1][p3 - 1] != BLACKPIECE && record_board[p1 - 1][p3 - 1] != BLACKPIECE)
                        return 1;
                }
                else
                    return 1;
            }
        }
        // in the middle of the board
        else
        {
            if (!((record_board[p1][p3] == WHITEPIECE || record_board[p1][p3] == WHITETRIANGLE)
                && (record_board[p2][p4] == WHITEPIECE || record_board[p2][p4] == WHITETRIANGLE)))
            {
                // near top left of the board
                if (p1 == 0 || p3 == 0)
                {
                    // special case II
                    if (p2 == SIZE - 1 || p4 == SIZE - 1)
                        return 1;
                    else
                    {
                        if ((record_board[p1][p3] == WHITEPIECE || record_board[p1][p3] == WHITETRIANGLE) && record_board[p2][p4] == 0 
                            && record_board[p2 + 1][p4 + 1] != BLACKPIECE && record_board[p2 + 1][p4 + 1] != BLACKTRIANGLE)
                            return 1;
                        else if ((record_board[p2][p4] == WHITEPIECE || record_board[p2][p4] == WHITETRIANGLE) && record_board[p1][p3] == 0)
                            return 1;
                        else if (record_board[p1][p3] == 0 && record_board[p2][p4] == 0)
                            return 1;
                    }
                }
                // near bottom right of the board
                else if (p2 == SIZE - 1 || p4 == SIZE - 1)
                {
                    if ((record_board[p2][p4] == WHITEPIECE || record_board[p2][p4] == WHITETRIANGLE) && record_board[p1][p3] == 0
                        && record_board[p1 - 1][p3 - 1] != BLACKPIECE && record_board[p1 - 1][p3 - 1] != BLACKTRIANGLE)
                        return 1;
                    else if ((record_board[p2][p4] == WHITEPIECE || record_board[p2][p4] == WHITETRIANGLE) && record_board[p2][p4] == 0)
                        return 1;
                    else if (record_board[p2][p4] == 0 && record_board[p1][p3] == 0)
                        return 1;
                }
                // center of the board
                else
                {
                    if ((!((record_board[p1][p3] == WHITEPIECE || record_board[p1][p3] == WHITETRIANGLE)
                        && (record_board[p2][p4] == WHITEPIECE || record_board[p2][p4] == WHITETRIANGLE)))
                        && (!((record_board[p1 - 1][p3 - 1] == BLACKPIECE || record_board[p1 - 1][p3 - 1] == BLACKTRIANGLE)
                        && (record_board[p2 + 1][p4 + 1] == BLACKPIECE || record_board[p2 + 1][p4 + 1] == BLACKTRIANGLE)))
                        && (!((record_board[p1][p3] == WHITEPIECE || record_board[p1][p3] == WHITETRIANGLE)
                        && (record_board[p2 + 1][p4 + 1] == BLACKPIECE || record_board[p2 + 1][p4 + 1] == BLACKTRIANGLE)))
                        && (!((record_board[p1 - 1][p3 - 1] == BLACKPIECE || record_board[p1 - 1][p3 - 1] == BLACKTRIANGLE)
                        && (record_board[p2][p4] == WHITEPIECE || record_board[p2][p4] == WHITETRIANGLE))))
                        return 1;
                }
            }
        }
    }

    /********************nonconsecutive four********************/
    else if (count == 3)
    {
        // the other piece is in the left of the three
        if (p1 >= 0 && p3 >= 0 && record_board[p1][p3] == 0 
            && p1 - 1 >= 0 && p3 - 1 >= 0 
            && (record_board[p1 - 1][p3 - 1] == BLACKPIECE || record_board[p1 - 1][p3 - 1] == BLACKTRIANGLE))
        {
            if (p1 - 2 >= 0 && p3 - 2 >= 0)
            {
                if (record_board[p1 - 2][p3 - 2] != BLACKPIECE && record_board[p1 - 2][p3 - 2] != BLACKTRIANGLE)
                    return 1;
            }
            // top left of the board
            else 
                return 1;
        }
        // the other piece is in the bottom right of the piece
        else if (p2 < SIZE && p4 < SIZE && record_board[p2][p4] == 0
                 && p2 + 1 < SIZE && p4 + 1 < SIZE
                 && (record_board[p2 + 1][p4 + 1] == BLACKPIECE || record_board[p2 + 1][p4 + 1] == BLACKTRIANGLE))
        {
            if (p2 + 2 < SIZE && p4 + 2 < SIZE)
            {
                if (record_board[p2 + 2][p4 + 2] != BLACKPIECE && record_board[p2 + 2][p4 + 2] != BLACKTRIANGLE)
                    return 1;
            }
            else
                return 1;
        }
    }

    else if (count == 1)
    {
        // the other three pieces is in the right of this piece
        if (p2 < SIZE && p4 < SIZE && record_board[p2][p4] == 0
            && p2 + 1 < SIZE  && p4 + 1 < SIZE
            && (record_board[p2 + 1][p4 + 1] == BLACKPIECE || record_board[p2 + 1][p4 + 1] == BLACKTRIANGLE)
            && p2 + 2 < SIZE && p4 + 2 < SIZE
            && (record_board[p2 + 2][p4 + 2] == BLACKPIECE || record_board[p2 + 2][p4 + 2] == BLACKTRIANGLE)
            && p2 + 3 < SIZE && p4 + 3 < SIZE
            && (record_board[p2 + 3][p4 + 3] == BLACKPIECE || record_board[p2 + 3][p4 + 3] == BLACKTRIANGLE))
        {
            if (p1 >= 0 && p3 >= 0)
            {
                if (record_board[p1][p3] != BLACKPIECE && record_board[p1][p3] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p2 + 4 < SIZE && p4 + 4 < SIZE)
                    {
                        if (record_board[p2 + 4][p4 + 4] != BLACKPIECE && record_board[p2 + 4][p4 + 4] != BLACKTRIANGLE)
                            return 1;
                    }
                    // bottom right of the board
                    else
                        return 1;
                }
            }
            // top left of the board
            else if (p2 + 4 < SIZE && p4 + 4 < SIZE
                    && record_board[p2 + 4][p4 + 4] != BLACKPIECE && record_board[p2 + 4][p4 + 4] != BLACKTRIANGLE)
                return 1;
        }
        // the other three pieces is in the left of this piece
        else if (p1 >= 0 && p3 >= 0 && record_board[p1][p3] == 0
                && p1 - 1 >= 0 && p3 - 1 >= 0
                && (record_board[p1 - 1][p3 - 1] == BLACKPIECE || record_board[p1 - 1][p3 - 1] == BLACKTRIANGLE)
                && p1 - 2 >= 0 && p3 - 2 >= 0
                && (record_board[p1 - 2][p3 - 2] == BLACKPIECE || record_board[p1 - 2][p3 - 2] == BLACKTRIANGLE)
                && p1 - 3 >= 0 && p3 - 3 >= 0
                && (record_board[p1 - 3][p3 - 3] == BLACKPIECE || record_board[p1 - 3][p3 - 3] == BLACKTRIANGLE))
        {
            if (p1 - 4 >= 0 && p3 - 4 >= 0)
            {
                if (record_board[p1 - 4][p3 - 4] != BLACKPIECE && record_board[p1 - 4][p3 - 4] != BLACKTRIANGLE)
                {
                    if (p2 < SIZE && p4 < SIZE)
                    {
                        if (record_board[p2][p4] != BLACKPIECE && record_board[p2][p4] != BLACKTRIANGLE)
                            return 1;
                    }
                    else
                        return 1;
                }
            }
            else if (p2 < SIZE && p4 < SIZE
                    && record_board[p2][p4] != BLACKPIECE && record_board[p2][p4] != BLACKTRIANGLE)
                return 1;
        }
    }
    else if (count == 2)
    {
        // the other two pieces is in the left of these two pieces
        if (p1 >= 0 && p3 >= 0 && record_board[p1][p3] == 0
            && p1 - 1 >= 0 && p3 - 1 >= 0
            && (record_board[p1 - 1][p3 - 1] == BLACKPIECE || record_board[p1 - 1][p3 - 1] == BLACKTRIANGLE)
            && p1 - 2 >= 0 && p3 - 2 >= 0
            && (record_board[p1 - 2][p3 - 2] == BLACKPIECE || record_board[p1 - 2][p3 - 2] == BLACKTRIANGLE))
        {
            if (p1 - 3 >= 0 && p3 - 3 >= 0)
            {
                if (record_board[p1 - 3][p3 - 3] != BLACKPIECE && record_board[p1 - 3][p3 - 3] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p2 < SIZE && p4 < SIZE)
                    {
                        if (record_board[p2][p4] != BLACKPIECE && record_board[p2][p4] != BLACKTRIANGLE)
                            return 1;
                    }
                    // bottom right of the board
                    else
                        return 1;
                }
            }
            // top left of the board
            else if (p2 < SIZE && p4 < SIZE
                    && record_board[p2][p4] != BLACKPIECE && record_board[p2][p4] != BLACKTRIANGLE)
                return 1;
        }
        // the other two pieces is in the bottom right of these two pieces
        if (p2 < SIZE && p4 < SIZE && record_board[p2][p4] == 0
            && p2 + 1 < SIZE && p4 + 1 < SIZE
            && (record_board[p2 + 1][p4 + 1] == BLACKPIECE || record_board[p2 + 1][p4 + 1] == BLACKTRIANGLE)
            && p2 + 2 >= 0 && p4 + 2 >= 0
            && (record_board[p2 + 2][p4 + 2] == BLACKPIECE || record_board[p2 + 2][p4 + 2] == BLACKTRIANGLE))
        {
            if (p2 + 3 < SIZE && p4 + 3 < SIZE)
            {
                if (record_board[p2 + 3][p4 + 3] != BLACKPIECE && record_board[p2 + 3][p4 + 3] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p1 >= 0 && p3 >= 0)
                    {
                        if (record_board[p1][p3] != BLACKPIECE && record_board[p1][p3] != BLACKTRIANGLE)
                            return 1;
                    }
                    // top left of the board
                    else
                        return 1;
                }
            }
            // bottom right of the board
            else if (p1 >= 0 && p3 >= 0
                && record_board[p1][p3] != BLACKPIECE && record_board[p1][p3] != BLACKTRIANGLE)
                return 1;
        }
    }

    /********** no fours found**********/
    return 0;
}

int is_four_sub_diagonal(int x, int y)
{
    int p1, p2, p3, p4; // these variables are used to store extremities
    int count = count_sub_diagonally(x, y, &p1, &p2, &p3, &p4, BLACKPIECE);

    /********************consecutive four********************/
    if (count == 4)
    {
        // top right of the board
        if (p1 == -1 || p3 == SIZE)
        {   
            // special case I
            if (p2 != SIZE && p4 != -1 && record_board[p2][p4] == 0)
            {
                if (p2 + 1 < SIZE && p4 - 1 >= 0)
                {
                    if (record_board[p2 + 1][p4 - 1] != BLACKPIECE && record_board[p2 + 1][p4 - 1] != BLACKTRIANGLE)
                        return 1;
                }
                else
                    return 1;
            }
        }
        // bottom left of the board
        else if (p2 == SIZE || p4 == -1)
        {
            if (record_board[p1][p3] == 0)
            {
                if (p1 - 1 >= 0 && p3 + 1 < SIZE)
                {
                    if (record_board[p1 - 1][p3 + 1] != BLACKPIECE && record_board[p1 - 1][p3 + 1] != BLACKPIECE)
                        return 1;
                }
                else
                    return 1;
            }
        }
        // in the middle of the board
        else
        {
            if (!((record_board[p1][p3] == WHITEPIECE || record_board[p1][p3] == WHITETRIANGLE)
                && (record_board[p2][p4] == WHITEPIECE || record_board[p2][p4] == WHITETRIANGLE)))
            {
                // near top right of the board
                if (p1 == 0 || p3 == SIZE - 1)
                {
                    // special case II
                    if (p2 == SIZE - 1 || p4 == 0)
                        return 1;
                    else
                    {
                        if ((record_board[p1][p3] == WHITEPIECE || record_board[p1][p3] == WHITETRIANGLE) && record_board[p2][p4] == 0 
                            && record_board[p2 + 1][p4 - 1] != BLACKPIECE && record_board[p2 + 1][p4 - 1] != BLACKTRIANGLE)
                            return 1;
                        else if ((record_board[p2][p4] == WHITEPIECE || record_board[p2][p4] == WHITETRIANGLE) && record_board[p1][p3] == 0)
                            return 1;
                        else if (record_board[p1][p3] == 0 && record_board[p2][p4] == 0)
                            return 1;
                    }
                }
                // near bottom left of the board
                else if (p2 == SIZE - 1 || p4 == 0)
                {
                    if ((record_board[p2][p4] == WHITEPIECE || record_board[p2][p4] == WHITETRIANGLE) && record_board[p1][p3] == 0
                        && record_board[p1 - 1][p3 + 1] != BLACKPIECE && record_board[p1 - 1][p3 + 1] != BLACKTRIANGLE)
                        return 1;
                    else if ((record_board[p2][p4] == WHITEPIECE || record_board[p2][p4] == WHITETRIANGLE) && record_board[p2][p4] == 0)
                        return 1;
                    else if (record_board[p2][p4] == 0 && record_board[p1][p3] == 0)
                        return 1;
                }
                // center of the board
                else
                {
                    if ((!((record_board[p1][p3] == WHITEPIECE || record_board[p1][p3] == WHITETRIANGLE)
                        && (record_board[p2][p4] == WHITEPIECE || record_board[p2][p4] == WHITETRIANGLE)))
                        && (!((record_board[p1 - 1][p3 + 1] == BLACKPIECE || record_board[p1 - 1][p3 + 1] == BLACKTRIANGLE)
                        && (record_board[p2 + 1][p4 - 1] == BLACKPIECE || record_board[p2 + 1][p4 - 1] == BLACKTRIANGLE)))
                        && (!((record_board[p1][p3] == WHITEPIECE || record_board[p1][p3] == WHITETRIANGLE)
                        && (record_board[p2 + 1][p4 - 1] == BLACKPIECE || record_board[p2 + 1][p4 - 1] == BLACKTRIANGLE)))
                        && (!((record_board[p1 - 1][p3 + 1] == BLACKPIECE || record_board[p1 - 1][p3 + 1] == BLACKTRIANGLE)
                        && (record_board[p2][p4] == WHITEPIECE || record_board[p2][p4] == WHITETRIANGLE))))
                        return 1;
                }
            }
        }
    }

    /********************nonconsecutive four********************/
    else if (count == 3)
    {
        // the other piece is in the left of the three
        if (p1 >= 0 && p3 < SIZE && record_board[p1][p3] == 0 
            && p1 - 1 >= 0 && p3 + 1 < SIZE 
            && (record_board[p1 - 1][p3 + 1] == BLACKPIECE || record_board[p1 - 1][p3 + 1] == BLACKTRIANGLE))
        {
            if (p1 - 2 >= 0 && p3 + 2 < SIZE)
            {
                if (record_board[p1 - 2][p3 + 2] != BLACKPIECE && record_board[p1 - 2][p3 + 2] != BLACKTRIANGLE)
                    return 1;
            }
            // top right of the board
            else 
                return 1;
        }
        // the other piece is in the bottom left of the piece
        else if (p2 < SIZE && p4 >= 0 && record_board[p2][p4] == 0
                 && p2 + 1 < SIZE && p4 - 1 >= 0
                 && (record_board[p2 + 1][p4 - 1] == BLACKPIECE || record_board[p2 + 1][p4 - 1] == BLACKTRIANGLE))
        {
            if (p2 + 2 < SIZE && p4 - 2 >= 0)
            {
                if (record_board[p2 + 2][p4 - 2] != BLACKPIECE && record_board[p2 + 2][p4 - 2] != BLACKTRIANGLE)
                    return 1;
            }
            else
                return 1;
        }
    }

    else if (count == 1)
    {
        // the other three pieces is in the right of this piece
        if (p2 < SIZE && p4 >= 0 && record_board[p2][p4] == 0
            && p2 + 1 < SIZE  && p4 - 1 >= 0
            && (record_board[p2 + 1][p4 - 1] == BLACKPIECE || record_board[p2 + 1][p4 - 1] == BLACKTRIANGLE)
            && p2 + 2 < SIZE && p4 - 2 >= 0
            && (record_board[p2 + 2][p4 - 2] == BLACKPIECE || record_board[p2 + 2][p4 - 2] == BLACKTRIANGLE)
            && p2 + 3 < SIZE && p4 - 3 >= 0
            && (record_board[p2 + 3][p4 - 3] == BLACKPIECE || record_board[p2 + 3][p4 - 3] == BLACKTRIANGLE))
        {
            if (p1 >= 0 && p3 < SIZE)
            {
                if (record_board[p1][p3] != BLACKPIECE && record_board[p1][p3] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p2 + 4 < SIZE && p4 - 4 >= 0)
                    {
                        if (record_board[p2 + 4][p4 - 4] != BLACKPIECE && record_board[p2 + 4][p4 - 4] != BLACKTRIANGLE)
                            return 1;
                    }
                    // bottom left of the board
                    else
                        return 1;
                }
            }
            // top right of the board
            else if (p2 + 4 < SIZE && p4 - 4 >= 0
                    && record_board[p2 + 4][p4 - 4] != BLACKPIECE && record_board[p2 + 4][p4 - 4] != BLACKTRIANGLE)
                return 1;
        }
        // the other three pieces is in the left of this piece
        else if (p1 >= 0 && p3 < SIZE && record_board[p1][p3] == 0
                && p1 - 1 >= 0 && p3 + 1 < SIZE
                && (record_board[p1 - 1][p3 + 1] == BLACKPIECE || record_board[p1 - 1][p3 + 1] == BLACKTRIANGLE)
                && p1 - 2 >= 0 && p3 + 2 < SIZE
                && (record_board[p1 - 2][p3 + 2] == BLACKPIECE || record_board[p1 - 2][p3 + 2] == BLACKTRIANGLE)
                && p1 - 3 >= 0 && p3 + 3 < SIZE
                && (record_board[p1 - 3][p3 + 3] == BLACKPIECE || record_board[p1 - 3][p3 + 3] == BLACKTRIANGLE))
        {
            if (p1 - 4 >= 0 && p3 + 4 < SIZE)
            {
                if (record_board[p1 - 4][p3 + 4] != BLACKPIECE && record_board[p1 - 4][p3 + 4] != BLACKTRIANGLE)
                {
                    if (p2 < SIZE && p4 >= 0)
                    {
                        if (record_board[p2][p4] != BLACKPIECE && record_board[p2][p4] != BLACKTRIANGLE)
                            return 1;
                    }
                    else
                        return 1;
                }
            }
            else if (p2 < SIZE && p4 >= 0
                    && record_board[p2][p4] != BLACKPIECE && record_board[p2][p4] != BLACKTRIANGLE)
                return 1;
        }
    }
    else if (count == 2)
    {
        // the other two pieces is in the left of these two pieces
        if (p1 >= 0 && p3 < SIZE && record_board[p1][p3] == 0
            && p1 - 1 >= 0 && p3 + 1 < SIZE
            && (record_board[p1 - 1][p3 + 1] == BLACKPIECE || record_board[p1 - 1][p3 + 1] == BLACKTRIANGLE)
            && p1 - 2 >= 0 && p3 + 2 < SIZE
            && (record_board[p1 - 2][p3 + 2] == BLACKPIECE || record_board[p1 - 2][p3 + 2] == BLACKTRIANGLE))
        {
            if (p1 - 3 >= 0 && p3 + 3 < SIZE)
            {
                if (record_board[p1 - 3][p3 + 3] != BLACKPIECE && record_board[p1 - 3][p3 + 3] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p2 < SIZE && p4 >= 0)
                    {
                        if (record_board[p2][p4] != BLACKPIECE && record_board[p2][p4] != BLACKTRIANGLE)
                            return 1;
                    }
                    // bottom left of the board
                    else
                        return 1;
                }
            }
            // top right of the board
            else if (p2 < SIZE && p4 >= 0
                    && record_board[p2][p4] != BLACKPIECE && record_board[p2][p4] != BLACKTRIANGLE)
                return 1;
        }
        // the other two pieces is in the bottom left of these two pieces
        if (p2 < SIZE && p4 >= 0 && record_board[p2][p4] == 0
            && p2 + 1 < SIZE && p4 - 1 >= 0
            && (record_board[p2 + 1][p4 - 1] == BLACKPIECE || record_board[p2 + 1][p4 - 1] == BLACKTRIANGLE)
            && p2 + 2 < SIZE && p4 - 2 >= 0
            && (record_board[p2 + 2][p4 - 2] == BLACKPIECE || record_board[p2 + 2][p4 - 2] == BLACKTRIANGLE))
        {
            if (p2 + 3 < SIZE && p4 - 3 >= 0)
            {
                if (record_board[p2 + 3][p4 - 3] != BLACKPIECE && record_board[p2 + 3][p4 - 3] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p1 >= 0 && p3 < SIZE)
                    {
                        if (record_board[p1][p3] != BLACKPIECE && record_board[p1][p3] != BLACKTRIANGLE)
                            return 1;
                    }
                    // top right of the board
                    else
                        return 1;
                }
            }
            // bottom left of the board
            else if (p1 >= 0 && p3 < SIZE
                && record_board[p1][p3] != BLACKPIECE && record_board[p1][p3] != BLACKTRIANGLE)
                return 1;
        }
    }

    /********** no fours found**********/
    return 0;
}

int is_over_one_four(int x, int y)
{
    int res = 0;
    if (is_four_horizontal(x, y))
        res++;
    if (is_four_vertical(x, y))
        res++;
    if (is_four_main_diagonal(x, y))
        res++;
    if (is_four_sub_diagonal(x, y))
        res++;
    if (res > 1)
        return 1;
    return 0;
}

int is_two_fours_in_one_line(int x, int y)
{
    int count_h, count_v, count_md, count_sd;
    int p1, p2, p3, p4;

    // horizontal
    count_h = count_horizontally(x, y, &p1, &p2, BLACKPIECE);
    if (count_h == 3)
    {
        if (p1 - 1 >= 0 && p2 + 1 < SIZE && record_board[x][p1] == 0 && record_board[x][p2] == 0
            && (record_board[x][p1 - 1] == BLACKPIECE || record_board[x][p1 - 1] == BLACKTRIANGLE)
            && (record_board[x][p2 + 1] == BLACKPIECE || record_board[x][p2 + 1] == BLACKTRIANGLE))
        {
            if (p1 - 2 >= 0)
            {
                if (record_board[x][p1 - 2] != BLACKPIECE && record_board[x][p1 - 2] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p2 + 2 < SIZE)
                    {
                        if (record_board[x][p2 + 2] != BLACKPIECE && record_board[x][p2 + 2] != BLACKTRIANGLE)
                            return 1;
                    }
                    // right side of the board
                    else
                        return 1;
                }
            }
            // left side of the board
            else if (record_board[x][p2 + 2] != BLACKPIECE && record_board[x][p2 + 2] != BLACKTRIANGLE)
                return 1;

        }
    }
    else if (count_h == 2)
    {
        if (p1 - 2 >= 0 && p2 + 2 < SIZE && record_board[x][p1] == 0 && record_board[x][p2] == 0
            && (record_board[x][p1 - 1] == BLACKPIECE || record_board[x][p1 - 1] == BLACKTRIANGLE)
            && (record_board[x][p2 + 1] == BLACKPIECE || record_board[x][p2 + 1] == BLACKTRIANGLE)
            && (record_board[x][p1 - 2] == BLACKPIECE || record_board[x][p1 - 2] == BLACKTRIANGLE)
            && (record_board[x][p2 + 2] == BLACKPIECE || record_board[x][p2 + 2] == BLACKTRIANGLE))
        {
            if (p1 - 3 >= 0)
            {
                if (record_board[x][p1 - 3] != BLACKPIECE && record_board[x][p1 - 3] != BLACKTRIANGLE)
                {
                    // center of the board
                    if (p2 + 3 < SIZE)
                    {
                        if (record_board[x][p2 + 3] != BLACKPIECE && record_board[x][p2 + 3] != BLACKTRIANGLE)
                            return 1;
                    }
                    // right side of the board
                    else
                        return 1;
                }
            }
            // left side of the board
            else if (record_board[x][p2 + 3] != BLACKPIECE && record_board[x][p2 + 3] != BLACKTRIANGLE)
                return 1;
        }
    }
    else if (count_h == 1)
    {
        if (p1 - 3 >= 0 && p2 + 3 < SIZE && record_board[x][p1] == 0 && record_board[x][p2] == 0
            && (record_board[x][p1 - 1] == BLACKPIECE || record_board[x][p1 - 1] == BLACKTRIANGLE)
            && (record_board[x][p2 + 1] == BLACKPIECE || record_board[x][p2 + 1] == BLACKTRIANGLE)
            && (record_board[x][p1 - 2] == BLACKPIECE || record_board[x][p1 - 2] == BLACKTRIANGLE)
            && (record_board[x][p2 + 2] == BLACKPIECE || record_board[x][p2 + 2] == BLACKTRIANGLE)
            && (record_board[x][p1 - 3] == BLACKPIECE || record_board[x][p1 - 3] == BLACKTRIANGLE)
            && (record_board[x][p2 + 3] == BLACKPIECE || record_board[x][p2 + 3] == BLACKTRIANGLE))
        {
            if (p1 - 4 >= 0)
            {
                if (record_board[x][p1 - 4] != BLACKPIECE && record_board[x][p1 - 4] != BLACKTRIANGLE)
                {
                    // center of the board
                    if (p2 + 4 < SIZE)
                    {
                        if (record_board[x][p2 + 4] != BLACKPIECE && record_board[x][p2 + 4] != BLACKTRIANGLE)
                            return 1;
                    }
                    // right side of the board
                    else
                        return 1;
                }
            }
            // left side of the board
            else if (record_board[x][p2 + 4] != BLACKPIECE && record_board[x][p2 + 4] != BLACKTRIANGLE)
                return 1;
        }
    }

    // vertical
    count_v = count_vertically(x, y, &p1, &p2, BLACKPIECE);
    if (count_v == 3)
    {
        if (p1 - 1 >= 0 && p2 + 1 < SIZE && record_board[p1][y] == 0 && record_board[p2][y] == 0
            && (record_board[p1 - 1][y] == BLACKPIECE || record_board[p1 - 1][y] == BLACKTRIANGLE)
            && (record_board[p2 + 1][y] == BLACKPIECE || record_board[p2 + 1][y] == BLACKTRIANGLE))
        {
            if (p1 - 2 >= 0)
            {
                if (record_board[p1 - 2][y] != BLACKPIECE && record_board[p1 - 2][y] != BLACKTRIANGLE)
                {
                    // center of the board
                    if (p2 + 2 < SIZE)
                    {
                        if (record_board[p2 + 2][y] != BLACKPIECE && record_board[p2 + 2][y] != BLACKTRIANGLE)
                            return 1;
                    }
                    // bottom of the board
                    else
                        return 1;
                }
            }
            // top of the board
            else if (record_board[p2 + 2][y] != BLACKPIECE && record_board[p2 + 2][y] != BLACKTRIANGLE)
                return 1;
        }
    }
    else if (count_v == 2)
    {
        if (p1 - 2 >= 0 && p2 + 2 < SIZE && record_board[p1][y] == 0 && record_board[p2][y] == 0
            && (record_board[p1 - 1][y] == BLACKPIECE || record_board[p1 - 1][y] == BLACKTRIANGLE)
            && (record_board[p2 + 1][y] == BLACKPIECE || record_board[p2 + 1][y] == BLACKTRIANGLE)
            && (record_board[p1 - 2][y] == BLACKPIECE || record_board[p1 - 2][y] == BLACKTRIANGLE)
            && (record_board[p2 + 2][y] == BLACKPIECE || record_board[p2 + 2][y] == BLACKTRIANGLE))
        {
            if (p1 - 3 >= 0)
            {
                if (record_board[p1 - 3][y] != BLACKPIECE && record_board[p1 - 3][y] != BLACKTRIANGLE)
                {
                    // center of the board
                    if (p2 + 3 < SIZE)
                    {
                        if (record_board[p2 + 3][y] != BLACKPIECE && record_board[p2 + 3][y] != BLACKTRIANGLE)
                            return 1;
                    }
                    // bottom of the board
                    else
                        return 1;
                }
            }
            // top of the board
            else if (record_board[p2 + 3][y] != BLACKPIECE && record_board[p2 + 3][y] != BLACKTRIANGLE)
                return 1;
        }
    }
    else if (count_v == 1)
    {
        if (p1 - 3 >= 0 && p2 + 3 < SIZE && record_board[p1][y] == 0 && record_board[p2][y] == 0
            && (record_board[p1 - 1][y] == BLACKPIECE || record_board[p1 - 1][y] == BLACKTRIANGLE)
            && (record_board[p2 + 1][y] == BLACKPIECE || record_board[p2 + 1][y] == BLACKTRIANGLE)
            && (record_board[p1 - 2][y] == BLACKPIECE || record_board[p1 - 2][y] == BLACKTRIANGLE)
            && (record_board[p2 + 2][y] == BLACKPIECE || record_board[p2 + 2][y] == BLACKTRIANGLE)
            && (record_board[p1 - 3][y] == BLACKPIECE || record_board[p1 - 3][y] == BLACKTRIANGLE)
            && (record_board[p2 + 3][y] == BLACKPIECE || record_board[p2 + 3][y] == BLACKTRIANGLE))
        {
            if (p1 - 4 >= 0)
            {
                if (record_board[p1 - 4][y] != BLACKPIECE && record_board[p1 - 4][y] != BLACKTRIANGLE)
                {
                    // center of the board
                    if (p2 + 4 < SIZE)
                    {
                        if (record_board[p2 + 4][y] != BLACKPIECE && record_board[p2 + 4][y] != BLACKTRIANGLE)
                            return 1;
                    }
                    // bottom of the board
                    else
                        return 1;
                }
            }
            // top of the board
            else if (record_board[p2 + 4][y] != BLACKPIECE && record_board[p2 + 4][y] != BLACKTRIANGLE)
                return 1;
        }
    }

    count_md = count_main_diagonally(x, y, &p1, &p2, &p3, &p4, BLACKPIECE);
        if (count_md == 3)
    {
        if (p1 - 1 >= 0 && p2 + 1 < SIZE && p3 - 1 >= 0 && p4 + 1 < SIZE
            && record_board[p1][p3] == 0 && record_board[p2][p4] == 0
            && (record_board[p1 - 1][p3 - 1] == BLACKPIECE || record_board[p1 - 1][p3 - 1] == BLACKTRIANGLE)
            && (record_board[p2 + 1][p4 + 1] == BLACKPIECE || record_board[p2 + 1][p4 + 1] == BLACKTRIANGLE))
        {
            if (p1 - 2 >= 0 && p3 - 1 >= 0)
            {
                if (record_board[p1 - 2][p3 - 2] != BLACKPIECE && record_board[p1 - 2][p3 - 2] != BLACKTRIANGLE)
                {
                    // center of the board
                    if (p2 + 2 < SIZE && p4 + 2 < SIZE)
                    {
                        if (record_board[p2 + 2][p4 + 2] != BLACKPIECE && record_board[p2 + 2][p4 + 2] != BLACKTRIANGLE)
                            return 1;
                    }
                    // bottom right of the board
                    else
                        return 1;
                }
            }
            // top left of the board
            else if (record_board[p2 + 2][p4 + 2] != BLACKPIECE && record_board[p2 + 2][p4 + 2] != BLACKTRIANGLE)
                return 1;

        }
    }
    else if (count_md == 2)
    {
        if (p1 - 2 >= 0 && p2 + 2 < SIZE && p3 - 2 >= 0 && p4 + 2 < SIZE
            && record_board[p1][p3] == 0 && record_board[p2][p4] == 0
            && (record_board[p1 - 1][p3 - 1] == BLACKPIECE || record_board[p1 - 1][p3 - 1] == BLACKTRIANGLE)
            && (record_board[p2 + 1][p4 + 1] == BLACKPIECE || record_board[p2 + 1][p4 + 1] == BLACKTRIANGLE)
            && (record_board[p1 - 2][p3 - 2] == BLACKPIECE || record_board[p1 - 2][p3 - 2] == BLACKTRIANGLE)
            && (record_board[p2 + 2][p4 + 2] == BLACKPIECE || record_board[p2 + 2][p4 + 2] == BLACKTRIANGLE))
        {
            if (p1 - 3 >= 0 && p3 - 3 >= 0)
            {
                if (record_board[p1 - 3][p3 - 3] != BLACKPIECE && record_board[p1 - 3][p3 - 3] != BLACKTRIANGLE)
                {
                    // center of the board
                    if (p2 + 3 < SIZE && p4 + 3 < SIZE)
                    {
                        if (record_board[p2 + 3][p4 + 3] != BLACKPIECE && record_board[p2 + 3][p4 + 3] != BLACKTRIANGLE)
                            return 1;
                    }
                    // bottom right of the board
                    else
                        return 1;
                }
            }
            // top left of the board
            else if (record_board[p2 + 3][p4 + 3] != BLACKPIECE && record_board[p2 + 3][p4 + 3] != BLACKTRIANGLE)
                return 1;
        }
    }
    else if (count_md == 1)
    {
        if (p1 - 3 >= 0 && p2 + 3 < SIZE && p3 - 3 >= 0 && p4 + 3 < SIZE
            && record_board[p1][p3] == 0 && record_board[p2][p4] == 0
            && (record_board[p1 - 1][p3 - 1] == BLACKPIECE || record_board[p1 - 1][p3 - 1] == BLACKTRIANGLE)
            && (record_board[p2 + 1][p4 + 1] == BLACKPIECE || record_board[p2 + 1][p4 + 1] == BLACKTRIANGLE)
            && (record_board[p1 - 2][p3 - 2] == BLACKPIECE || record_board[p1 - 2][p3 - 2] == BLACKTRIANGLE)
            && (record_board[p2 + 2][p4 + 2] == BLACKPIECE || record_board[p2 + 2][p4 + 2] == BLACKTRIANGLE)
            && (record_board[p1 - 3][p3 - 3] == BLACKPIECE || record_board[p1 - 3][p3 - 3] == BLACKTRIANGLE)
            && (record_board[p2 + 3][p4 + 3] == BLACKPIECE || record_board[p2 + 3][p4 + 3] == BLACKTRIANGLE))
        {
            if (p1 - 4 >= 0 && p3 - 4 >= 0)
            {
                if (record_board[p1 - 4][p3 - 4] != BLACKPIECE && record_board[p1 - 4][p3 - 4] != BLACKTRIANGLE)
                {
                    // center of the board
                    if (p2 + 4 < SIZE && p4 + 4 < SIZE)
                    {
                        if (record_board[p2 + 4][p4 + 4] != BLACKPIECE && record_board[p2 + 4][p4 + 4] != BLACKTRIANGLE)
                            return 1;
                    }
                    // bottom right of the board
                    else
                        return 1;
                }
            }
            // top left of the board
            else if (record_board[p2 + 4][p4 + 4] != BLACKPIECE && record_board[p2 + 4][p4 + 4] != BLACKTRIANGLE)
                return 1;
        }
    }

    count_sd = count_sub_diagonally(x, y, &p1, &p2, &p3, &p4, BLACKPIECE);
    if (count_sd == 3)
    {
        if (p1 - 1 >= 0 && p2 + 1 < SIZE && p3 + 1 < SIZE && p4 - 1 >= 0
            && record_board[p1][p3] == 0 && record_board[p2][p4] == 0
            && (record_board[p1 - 1][p3 + 1] == BLACKPIECE || record_board[p1 - 1][p3 + 1] == BLACKTRIANGLE)
            && (record_board[p2 + 1][p4 - 1] == BLACKPIECE || record_board[p2 + 1][p4 - 1] == BLACKTRIANGLE))
        {
            if (p1 - 2 >= 0 && p3 + 2 < SIZE)
            {
                if (record_board[p1 - 2][p3 + 2] != BLACKPIECE && record_board[p1 - 2][p3 + 2] != BLACKTRIANGLE)
                {
                    // center of the board
                    if (p2 + 2 < SIZE && p4 - 2 >= 0)
                    {
                        if (record_board[p2 + 2][p4 - 2] != BLACKPIECE && record_board[p2 + 2][p4 - 2] != BLACKTRIANGLE)
                            return 1;
                    }
                    // bottom left of the board
                    else
                        return 1;
                }
            }
            // top right of the board
            else if (record_board[p2 + 2][p4 - 2] != BLACKPIECE && record_board[p2 + 2][p4 - 2] != BLACKTRIANGLE)
                return 1;

        }
    }
    else if (count_sd == 2)
    {
        if (p1 - 2 >= 0 && p2 + 2 < SIZE && p3 + 2 < SIZE && p4 - 2 >= 0
            && record_board[p1][p3] == 0 && record_board[p2][p4] == 0
            && (record_board[p1 - 1][p3 + 1] == BLACKPIECE || record_board[p1 - 1][p3 + 1] == BLACKTRIANGLE)
            && (record_board[p2 + 1][p4 - 1] == BLACKPIECE || record_board[p2 + 1][p4 - 1] == BLACKTRIANGLE)
            && (record_board[p1 - 2][p3 + 2] == BLACKPIECE || record_board[p1 - 2][p3 + 2] == BLACKTRIANGLE)
            && (record_board[p2 + 2][p4 - 2] == BLACKPIECE || record_board[p2 + 2][p4 - 2] == BLACKTRIANGLE))
        {
            if (p1 - 3 >= 0 && p3 + 3 < SIZE)
            {
                if (record_board[p1 - 3][p3 + 3] != BLACKPIECE && record_board[p1 - 3][p3 + 3] != BLACKTRIANGLE)
                {
                    // center of the board
                    if (p2 + 3 < SIZE && p4 - 3 >= 0)
                    {
                        if (record_board[p2 + 3][p4 - 3] != BLACKPIECE && record_board[p2 + 3][p4 - 3] != BLACKTRIANGLE)
                            return 1;
                    }
                    // bottom left of the board
                    else
                        return 1;
                }
            }
            // top right of the board
            else if (record_board[p2 + 3][p4 - 3] != BLACKPIECE && record_board[p2 + 3][p4 - 3] != BLACKTRIANGLE)
                return 1;
        }
    }
    else if (count_sd == 1)
    {
        if (p1 - 3 >= 0 && p2 + 3 < SIZE && p3 + 3 < SIZE && p4 - 3 >= 0
            && record_board[p1][p3] == 0 && record_board[p2][p4] == 0
            && (record_board[p1 - 1][p3 + 1] == BLACKPIECE || record_board[p1 - 1][p3 + 1] == BLACKTRIANGLE)
            && (record_board[p2 + 1][p4 - 1] == BLACKPIECE || record_board[p2 + 1][p4 - 1] == BLACKTRIANGLE)
            && (record_board[p1 - 2][p3 + 2] == BLACKPIECE || record_board[p1 - 2][p3 + 2] == BLACKTRIANGLE)
            && (record_board[p2 + 2][p4 - 2] == BLACKPIECE || record_board[p2 + 2][p4 - 2] == BLACKTRIANGLE)
            && (record_board[p1 - 3][p3 + 3] == BLACKPIECE || record_board[p1 - 3][p3 + 3] == BLACKTRIANGLE)
            && (record_board[p2 + 3][p4 - 3] == BLACKPIECE || record_board[p2 + 3][p4 - 3] == BLACKTRIANGLE))
        {
            if (p1 - 4 >= 0 && p3 + 4 < SIZE)
            {
                if (record_board[p1 - 4][p3 + 4] != BLACKPIECE && record_board[p1 - 4][p3 + 4] != BLACKTRIANGLE)
                {
                    // center of the board
                    if (p2 + 4 < SIZE && p4 - 4 >= 0)
                    {
                        if (record_board[p2 + 4][p4 - 4] != BLACKPIECE && record_board[p2 + 4][p4 - 4] != BLACKTRIANGLE)
                            return 1;
                    }
                    // bottom left of the board
                    else
                        return 1;
                }
            }
            // top right of the board
            else if (record_board[p2 + 4][p4 - 4] != BLACKPIECE && record_board[p2 + 4][p4 - 4] != BLACKTRIANGLE)
                return 1;
        }
    }
    return 0;
}

int is_forbidden_move()
{
    for (int x = 0; x < SIZE; x++)
        for (int y = 0; y < SIZE; y++)
            if (record_board[x][y] == BLACKPIECE || record_board[x][y] == BLACKTRIANGLE)
            {   
                if (is_five_black(x, y))
                    return 0;

                int res = 0;
                res += is_over_line(x, y);
                res += is_over_one_active_three(x, y);
                res += is_over_one_four(x, y);
                res += is_two_fours_in_one_line(x, y);
                if (res > 0)
                    return 1;
            }
    return 0;
}
