#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "game_functions.h"
#include "check_forbidden_moves.h"

#define SIZE 15
#define CHARSIZE 2

extern char init_display_board_array[SIZE][SIZE * CHARSIZE + 1];
extern char display_board_array[SIZE][SIZE * CHARSIZE + 1];
extern int record_board[SIZE][SIZE];
extern int current_pos_x;
extern int current_pos_y;

int main()
{
    /* test program */
    init_record_board();
    record_to_display_array();
    display_board();
    
    int num_white, num_black;
    printf("Please enter the numbers of white pieces and black pieces:\n");
    scanf("%d%d", &num_white, &num_black);
    getchar();
    for (int i = 0; i < num_black - 1; i++)
    {
        drop_pieces(0);
        record_to_display_array();
        display_board();
    }
    for (int i = 0; i < num_white; i++)
    {
        drop_pieces(1);
        record_to_display_array();
        display_board();
    }
    drop_pieces(0);
    record_to_display_array();
    display_board();
    if (is_four_horizontal(current_pos_x, current_pos_y))
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}