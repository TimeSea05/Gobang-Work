#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "game_functions.h"
#include "game.h"

extern int latest_x, latest_y;

int main()
{
    
    init_record_board();
    record_to_display_array();
    display_board();
    
    char command;
    printf("Black or white piece? (B/W)\n");
    while (scanf("%c", &command) != EOF)
    {
        getchar();
        switch(command)
        {
            case 'B':
                drop_pieces(0);
                record_to_display_array();
                display_board();
                break;
            case 'W':
                drop_pieces(1);
                record_to_display_array();
                display_board();
            default:
                printf("Enter again!\n");
        }
        printf("Black or white piece? (B/W)\n");
    }

    int num = num_active_four_black(latest_x, latest_y);
    printf("%d\n", num);
    return 0;
}