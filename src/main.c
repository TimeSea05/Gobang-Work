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
    // 使程序能够正常输出宽字符
    setlocale(LC_ALL, "");

    init_record_board();
    record_to_display_array();
    display_board();
    
    while (1)
    {
        printf("请选择游戏模式：\n");
        printf("人人对战请输入1; 人机对战请输入2;\n");
        int mode;
        scanf("%d", &mode);
        getchar();
        if (mode == 1)  // 人人对战
        {
            person_vs_person();
            break;
        }
        else if (mode == 2) // 人机对战
        {
            person_vs_computer();
            break;
        }
        else
            printf("无法识别，请重新输入！");
    }
    
    return 0;
}