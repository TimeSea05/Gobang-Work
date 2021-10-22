#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "game_func.h"
#include "game.h"
#include "ai.h"
#include "constants.h"

extern int latest_x, latest_y;
extern int next_point_x, next_point_y;
extern int record_board[SIZE][SIZE];

int main()
{
    init_record_board();
    record_to_display_array();
    display_board();
    
    while(1)
    {
        drop_pieces(0);
        record_to_display_array();
        display_board();
        if (game_win())
            break;
         negative_max(WHITEPIECE, 3, -99999999, 99999999);
        record_board[next_point_x][next_point_y] = WHITEPIECE;
        latest_x = next_point_x, latest_y = next_point_y;
        record_to_display_array();
        display_board();
        if (game_win())
            break;
    }
    return 0;
}