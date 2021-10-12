#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "game_functions.h"
#include "check_forbidden_move.h"

#define SIZE 15
#define CHARSIZE 2

#define HORIZONTAL 1
#define HORIZONTAL_INV 2
#define VERTICAL 3
#define VERTICAL_INV 4
#define MAIN_DIAGONAL 5
#define MAIN_DIAGONAL_INV 6
#define SUB_DIAGONAL 7
#define SUB_DIAGONAL_INV 8

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
    
    char * string = to_string(current_pos_x, current_pos_y, HORIZONTAL);
    printf("%s\n", string);
    free(string);
    return 0;
}