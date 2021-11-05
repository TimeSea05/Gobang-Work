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
        if (latest_x != -1 && latest_y != -1)
            record_board[latest_x][latest_y] = WHITEPIECE;
        drop_pieces(BLACKPIECE);
        record_to_display_array();
        display_board();
        if (game_win() == FORBIDDEN)
            printf("White wins!\n");
        else if (game_win() == BLACKPIECE)
        {
            printf("Black wins!\n");
            break;
        }
        negative_max(WHITEPIECE, DEPTH, -99999999, 99999999);
        record_board[next_point_x][next_point_y] = WHITETRIANGLE;
        record_board[latest_x][latest_y] = BLACKPIECE;
        latest_x = next_point_x, latest_y = next_point_y;
        record_to_display_array();
        display_board();
        if (game_win() == WHITEPIECE)
        {
            printf("White wins!\n");
            break;
        }
    }
    return 0;
}