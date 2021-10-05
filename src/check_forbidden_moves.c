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

int is_five_black(int x, int y)
{
    int count;
    int i, j;

    // horizontal
    count = 1;
    i = y;
    while (i > 0)
        if (record_board[x][i - 1] == BLACKPIECE || record_board[x][i - 1] == BLACKTRIANGLE)
        {
            count++;
            i--;
        }
        else
            break;
    i = y;
    while (i < SIZE - 1)
        if (record_board[x][i + 1] == BLACKPIECE || record_board[x][i + 1] == BLACKTRIANGLE)
        {
            count++;
            i++;
        }
        else
            break;
    if (count == 5)
        return 1;


    // vertical
    count = 1;
    i = x;
    while (i > 0)
        if (record_board[i - 1][y] == BLACKPIECE || record_board[i - 1][y] == BLACKTRIANGLE)
        {
            count++;
            i--;    
        }
        else
            break;
    i = x;
    while (i < SIZE - 1)
        if (record_board[i + 1][y] == BLACKPIECE || record_board[i + 1][y] == BLACKTRIANGLE)
        {
            count++;
            i++;
        }
        else
            break;
    if (count == 5)
        return 1;
    
    
    // diagonal
    // main diagonal
    count = 1;
    i = x, j = y;
    while (i > 0 && j > 0)
        if (record_board[i - 1][j - 1] == BLACKPIECE || record_board[i - 1][j - 1] == BLACKTRIANGLE)
        {
            count++;
            i--;
            j--;
        }
        else
            break;
    i = x, j = y;
    while (i < SIZE - 1 && j < SIZE - 1)
        if (record_board[i + 1][j + 1] == BLACKPIECE || record_board[i + 1][j + 1] == BLACKTRIANGLE)
        {
            count++;
            i++;
            j++;
        }
        else
            break;
    if (count == 5)
        return 1;
    
    // sub diagonal
    count = 1;
    i = x, j = y;
    while (i > 0 && j < SIZE - 1)
        if (record_board[i - 1][j + 1] == BLACKPIECE || record_board[i - 1][j + 1] == BLACKTRIANGLE)
        {
            count++;
            i--;
            j++;
        }
        else
            break;
    i = x, j = y;
    while (i < SIZE - 1 && j > 0)
        if (record_board[i + 1][j - 1] == BLACKPIECE || record_board[i + 1][j - 1] == BLACKTRIANGLE)
            count++;
        else
            break;
    if (count == 5)
        return 1;
    
    // no fives
    return 0;
}

int is_five_white(int x, int y)
{
    int count;
    int i, j;

    // horizontal
    count = 1;
    i = y;
    while (i > 0)
        if (record_board[x][i - 1] == WHITEPIECE || record_board[x][i - 1] == WHITETRIANGLE)
        {
            count++;
            i--;
        }
        else
            break;
    i = y;
    while (i < SIZE - 1)
        if (record_board[x][i + 1] == WHITEPIECE || record_board[x][i + 1] == WHITETRIANGLE)
        {
            count++;
            i++;
        }
        else
            break;
    if (count >= 5)
        return 1;


    // vertical
    count = 1;
    i = x;
    while (i > 0)
        if (record_board[i - 1][y] == WHITEPIECE || record_board[i - 1][y] == WHITETRIANGLE)
        {
            count++;
            i--;    
        }
        else
            break;
    i = x;
    while (i < SIZE - 1)
        if (record_board[i + 1][y] == WHITEPIECE || record_board[i + 1][y] == WHITETRIANGLE)
        {
            count++;
            i++;
        }
        else
            break;
    if (count >= 5)
        return 1;
    
    
    // diagonal
    // main diagonal
    count = 1;
    i = x, j = y;
    while (i > 0 && j > 0)
        if (record_board[i - 1][j - 1] == WHITEPIECE || record_board[i - 1][j - 1] == WHITETRIANGLE)
        {
            count++;
            i--;
            j--;
        }
        else
            break;
    i = x, j = y;
    while (i < SIZE - 1 && j < SIZE - 1)
        if (record_board[i + 1][j + 1] == WHITEPIECE || record_board[i + 1][j + 1] == WHITETRIANGLE)
        {
            count++;
            i++;
            j++;
        }
        else
            break;
    if (count >= 5)
        return 1;
    
    // sub diagonal
    count = 1;
    i = x, j = y;
    while (i > 0 && j < SIZE - 1)
        if (record_board[i - 1][j + 1] == WHITEPIECE || record_board[i - 1][j + 1] == WHITETRIANGLE)
        {
            count++;
            i--;
            j++;
        }
        else
            break;
    i = x, j = y;
    while (i < SIZE - 1 && j > 0)
        if (record_board[i + 1][j - 1] == WHITEPIECE || record_board[i + 1][j - 1] == WHITETRIANGLE)
            count++;
        else
            break;
    if (count >= 5)
        return 1;
    
    // no fives
    return 0;
}

int is_over_line(int x, int y)
{
    int count;
    int i, j;

    // horizontal
    count = 1;
    i = y;
    while (i > 0)
        if (record_board[x][i - 1] == BLACKPIECE || record_board[x][i - 1] == BLACKTRIANGLE)
        {
            count++;
            i--;
        }
        else
            break;
    i = y;
    while (i < SIZE - 1)
        if (record_board[x][i + 1] == BLACKPIECE || record_board[x][i + 1] == BLACKTRIANGLE)
        {
            count++;
            i++;
        }
        else
            break;
    if (count > 5)
        return 1;


    // vertical
    count = 1;
    i = x;
    while (i > 0)
        if (record_board[i - 1][y] == BLACKPIECE || record_board[i - 1][y] == BLACKTRIANGLE)
        {
            count++;
            i--;    
        }
        else
            break;
    i = x;
    while (i < SIZE - 1)
        if (record_board[i + 1][y] == BLACKPIECE || record_board[i + 1][y] == BLACKTRIANGLE)
        {
            count++;
            i++;
        }
        else
            break;
    if (count > 5)
        return 1;
    
    
    // diagonal
    // main diagonal
    count = 1;
    i = x, j = y;
    while (i > 0 && j > 0)
        if (record_board[i - 1][j - 1] == BLACKPIECE || record_board[i - 1][j - 1] == BLACKTRIANGLE)
        {
            count++;
            i--;
            j--;
        }
        else
            break;
    i = x, j = y;
    while (i < SIZE - 1 && j < SIZE - 1)
        if (record_board[i + 1][j + 1] == BLACKPIECE || record_board[i + 1][j + 1] == BLACKTRIANGLE)
        {
            count++;
            i++;
            j++;
        }
        else
            break;
    if (count > 5)
        return 1;
    
    // sub diagonal
    count = 1;
    i = x, j = y;
    while (i > 0 && j < SIZE - 1)
        if (record_board[i - 1][j + 1] == BLACKPIECE || record_board[i - 1][j + 1] == BLACKTRIANGLE)
        {
            count++;
            i--;
            j++;
        }
        else
            break;
    i = x, j = y;
    while (i < SIZE - 1 && j > 0)
        if (record_board[i + 1][j - 1] == BLACKPIECE || record_board[i + 1][j - 1] == BLACKTRIANGLE)
            count++;
        else
            break;
    if (count > 5)
        return 1;
    
    // no overlines
    return 0;
}


int is_active_three_horizontal(int x, int y)
{
    
    int count;  // 记录指定棋子周围相同棋子的数量
    int i;
    // these variables are used to store extremities
    int p1, p2;

    // horizontal
    count = 1;
    i = y;
    while (i > 0)
        if (record_board[x][i - 1] == BLACKPIECE || record_board[x][i - 1] == BLACKTRIANGLE)
        {
            count++;
            i--;
        }
        else
            break;
    p1 = i - 1;
    i = y;
    while (i < SIZE - 1)
        if (record_board[x][i + 1] == BLACKPIECE || record_board[x][i + 1] == BLACKTRIANGLE)
        {
            count++;
            i++;
        }
        else
            break;
    p2 = i + 1;

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
                    && record_board[x][p2 + 2] != BLACKPIECE && record_board[x][p2 + 2] != BLACKTRIANGLE)   // modified here: 20210913
                    return 1;
            }
            // side II
            else if (p2 == SIZE - 1)
            {
                if (record_board[x][p2] == 0 && record_board[x][p1] == 0 && record_board[x][p1 - 1] == 0
                    && record_board[x][p1 - 2] != BLACKPIECE && record_board[x][p1 - 2] != BLACKTRIANGLE)   // modified here: 20210913
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
    int count;  // 记录指定棋子周围相同棋子的数量
    int i;
    // these variables are used to store extremities
    int p1, p2;

    // vertical 
    count = 1;
    i = x;
    while (i > 0)
        if (record_board[i - 1][y] == BLACKPIECE || record_board[i - 1][y] == BLACKTRIANGLE)
        {
            count++;
            i--;
        }
        else
            break;
    p1 = i - 1;
    i = x;
    while (i < SIZE - 1)
        if (record_board[i + 1][y] == BLACKPIECE || record_board[i + 1][y] == BLACKTRIANGLE)
        {
            count++;
            i++;
        }
        else
            break;
    p2 = i + 1;

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
    int count;  // 记录指定棋子周围相同棋子的数量
    int i, j;
    // these variables are used to store extremities
    int p1, p2, p3, p4;

    // diagonal
    // main diagonal
    count = 1;
    i = x, j = y;
    while (i > 0 && j > 0)
        if (record_board[i - 1][j - 1] == BLACKPIECE || record_board[i - 1][j - 1] == BLACKTRIANGLE)
        {
            count++;
            i--;
            j--;
        }
        else
            break;
    p1 = i - 1, p3 = j - 1;
    i = x, j = y;
    while (i < SIZE - 1 && j < SIZE - 1)
        if (record_board[i + 1][j + 1] == BLACKPIECE || record_board[i + 1][j + 1] == BLACKTRIANGLE)
        {
            count++;
            i++;
            j++;
        }
        else
            break;
    p2 = i + 1, p4 = j + 1;

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
    int count;  // 记录指定棋子周围相同棋子的数量
    int i, j;
    // these variables are used to store extremities
    int p1, p2, p3, p4;

    count = 1;
    i = x, j = y;
    while (i > 0 && j < SIZE - 1)
        if (record_board[i - 1][j + 1] == BLACKPIECE || record_board[i - 1][j + 1] == BLACKTRIANGLE)
        {
            count++;
            i--;
            j++;
        }
        else
            break;
    p1 = i - 1, p3 = j + 1;
    i = x, j = y;
    while (i < SIZE - 1 && j > 0)
        if (record_board[i + 1][j - 1] == BLACKPIECE || record_board[i + 1][j - 1] == BLACKTRIANGLE)
        {
            count++;
            i++;
            j--;
        }
        else
            break;
    p2 = i + 1, p4 = j - 1;

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

int is_over_two_active_threes(int x, int y)
{
    int count_active_three = 0;
    count_active_three += is_active_three_horizontal(x, y);
    count_active_three += is_active_three_vertical(x, y);
    count_active_three += is_active_three_main_diagonal(x, y);
    count_active_three += is_active_three_sub_diagonal(x, y);

    if (count_active_three > 1)
        return 1;
    else
        return 0;
}


int is_four_horizontal(int x, int y)
{
    int count;  // 记录指定棋子周围相同棋子的数量
    int i;
    // these variables are used to store extremities
    int p1, p2;

    // horizontal
    count = 1;
    i = y;
    while (i > 0)
        if (record_board[x][i - 1] == BLACKPIECE || record_board[x][i - 1] == BLACKTRIANGLE)
        {
            count++;
            i--;
        }
        else
            break;
    p1 = i - 1;
    i = y;
    while (i < SIZE - 1)
        if (record_board[x][i + 1] == BLACKPIECE || record_board[x][i + 1] == BLACKTRIANGLE)
        {
            count++;
            i++;
        }
        else
            break;
    p2 = i + 1;

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
    int count;  // 记录指定棋子周围相同棋子的数量
    int i;
    // these variables are used to store extremities
    int p1, p2;

    // vertical 
    count = 1;
    i = x;
    while (i > 0)
        if (record_board[i - 1][y] == BLACKPIECE || record_board[i - 1][y] == BLACKTRIANGLE)
        {
            count++;
            i--;
        }
        else
            break;
    p1 = i - 1;
    i = x;
    while (i < SIZE - 1)
        if (record_board[i + 1][y] == BLACKPIECE || record_board[i + 1][y] == BLACKTRIANGLE)
        {
            count++;
            i++;
        }
        else
            break;
    p2 = i + 1;

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
    int count;  // 记录指定棋子周围相同棋子的数量
    int i, j;
    // these variables are used to store extremities
    int p1, p2, p3, p4;

    // diagonal
    // main diagonal
    count = 1;
    i = x, j = y;
    while (i > 0 && j > 0)
        if (record_board[i - 1][j - 1] == BLACKPIECE || record_board[i - 1][j - 1] == BLACKTRIANGLE)
        {
            count++;
            i--;
            j--;
        }
        else
            break;
    p1 = i - 1, p3 = j - 1;
    i = x, j = y;
    while (i < SIZE - 1 && j < SIZE - 1)
        if (record_board[i + 1][j + 1] == BLACKPIECE || record_board[i + 1][j + 1] == BLACKTRIANGLE)
        {
            count++;
            i++;
            j++;
        }
        else
            break;
    p2 = i + 1, p4 = j + 1;

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
                    {
                        if (!((record_board[p1][p3] == WHITEPIECE || record_board[p1][p3] == WHITETRIANGLE)
                            && (record_board[p2][p4] == WHITEPIECE || record_board[p2][p4] == WHITETRIANGLE)))
                            return 1;
                    }
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
    int count;  // 记录指定棋子周围相同棋子的数量
    int i, j;
    // these variables are used to store extremities
    int p1, p2, p3, p4;

    count = 1;
    i = x, j = y;
    while (i > 0 && j < SIZE - 1)
        if (record_board[i - 1][j + 1] == BLACKPIECE || record_board[i - 1][j + 1] == BLACKTRIANGLE)
        {
            count++;
            i--;
            j++;
        }
        else
            break;
    p1 = i - 1, p3 = j + 1;
    i = x, j = y;
    while (i < SIZE - 1 && j > 0)
        if (record_board[i + 1][j - 1] == BLACKPIECE || record_board[i + 1][j - 1] == BLACKTRIANGLE)
        {
            count++;
            i++;
            j--;
        }
        else
            break;
    p2 = i + 1, p4 = j - 1;

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
                    {
                        if (!((record_board[p1][p3] == WHITEPIECE || record_board[p1][p3] == WHITETRIANGLE)
                            && (record_board[p2][p4] == WHITEPIECE || record_board[p2][p4] == WHITETRIANGLE)))
                            return 1;
                    }
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
