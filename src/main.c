#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "game_functions.h"
#include "game.h"
#include "ai.h"

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
                break;
            default:
                printf("Enter again!\n");
                break;
        }
        printf("Black or white piece? (B/W)\n");
        if (game_win())
            break;
    }
    int res = evaluate(latest_x - 1, latest_y + 1, 1);
    printf("%d\n", res);
    return 0;
}