#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>
#include "game_func.h"
#include "game.h"
#include "constants.h"
#include "ai.h"

extern wchar_t init_display_board_array[SIZE][SIZE + 1];
extern wchar_t display_board_array[SIZE][SIZE + 1];
extern int record_board[SIZE][SIZE];
extern int latest_x, latest_y;
extern int latest_type;
extern int next_point_x, next_point_y;

// 黑色棋子
wchar_t play1_pic = L'●'; 
wchar_t play1_current_pic = L'▲';
// 白色棋子
wchar_t play2_pic = L'○'; 
wchar_t play2_current_pic = L'△';

void init_record_board()
{
	// set record_board to zero by double loop;
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			record_board[i][j] = 0;
}
void record_to_display_array()
{
	//第一步：将init_display_board_array中记录的空棋盘，复制到display_board_array中
	//第二步：扫描record_board，当遇到非0的元素，将●或者◎复制到display_board_array的相应位置上
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			display_board_array[i][j] = init_display_board_array[i][j];
	
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (record_board[i][j] == BLACKPIECE)
				display_board_array[i][j] = play1_pic;
			else if (record_board[i][j] == WHITEPIECE)
				display_board_array[i][j] = play2_pic;
			else if (record_board[i][j] == BLACKTRIANGLE)
				display_board_array[i][j] = play1_current_pic;
			else if (record_board[i][j] == WHITETRIANGLE)
				display_board_array[i][j] = play2_current_pic;
}
void display_board()
{
	int i, j;	
	// first: clean the screen
	system("clear");
	// second: print adisplay_board
	for (i = 0; i < SIZE; i++)
	{
		if (SIZE - i >= 10)
			printf("%d", SIZE - i);
		else
			printf(" %d", SIZE - i);

		for (j = 0; j < SIZE ; j++)
			printf("%lc", display_board_array[i][j]);
		printf("\n");
	}		
	// last: print 'A, B, ...' in the last line
	char c = 'A';
	printf("  ");
	for (i = 0; i < SIZE; i++)
		printf("%c ", c++);
	printf("\n\n");
}

void drop_pieces(int type)
{
	printf("请输入你要下的棋子的坐标(e.g. H1 or h1):\n");
	while (1)
	{
		int command_x;
		char command_y;
		scanf("%c%d", &command_y, &command_x);

		// x & y coordination
		int coordinate_x = -command_x + SIZE;
		int coordinate_y;
		// uppercase letters
		if (isupper(command_y))
			coordinate_y = command_y - 'A';
		// lowercase letters
		else
			coordinate_y = command_y - 'a';
		
		if (record_board[coordinate_x][coordinate_y] == 0)
		{
			// no pieces in this position
			if (type == BLACKPIECE)
				record_board[coordinate_x][coordinate_y] = BLACKTRIANGLE;
			else if (type == WHITEPIECE)
				record_board[coordinate_x][coordinate_y] = WHITETRIANGLE;
			latest_x = coordinate_x;
			latest_y = coordinate_y;
			latest_type = type;
			getchar();
			break;
		}
		else
		{
			printf("There is already a piece in this position. Enter again!\n");
			getchar();
			continue;
		}
	}
}

int game_win()
{
	if (is_forbidden())
		return FORBIDDEN;

	// HORIZONTAL
	for (int i = 0; i < SIZE; i++)
	{
		if (is_five_black(i, 0, HORIZONTAL))
			return BLACKPIECE;
		else if (is_five_white(i, 0, HORIZONTAL))
			return WHITEPIECE;
	}
	// VERTICAL
	for (int j = 0; j < SIZE; j++)
	{
		if (is_five_black(0, j, VERTICAL))
			return BLACKPIECE;
		else if (is_five_white(0, j, VERTICAL))
			return WHITEPIECE;
	}
	// MAIN_DIAGONAL
	for (int i = 0; i < SIZE; i++)
	{
		if (is_five_black(0, i, MAIN_DIAGONAL))
			return BLACKPIECE;
		else if (is_five_white(0, i, MAIN_DIAGONAL))
			return WHITEPIECE;
	}
	for (int i = 0; i < SIZE - 1; i++)
	{
		if (is_five_black(14, i, MAIN_DIAGONAL))
			return BLACKPIECE;
		else if (is_five_white(14, i, MAIN_DIAGONAL))
			return WHITEPIECE;
	}
	// SUB_DIAGONAL
	for (int j = 0; j < SIZE; j++)
	{
		if (is_five_black(0, j, SUB_DIAGONAL))
			return BLACKPIECE;
		else if (is_five_white(0, j, SUB_DIAGONAL))
			return WHITEPIECE;
	}
	for (int j = 0; j < SIZE - 1; j++)
	{
		if (is_five_black(14, j, SUB_DIAGONAL))
			return BLACKPIECE;
		else if (is_five_white(14, j, SUB_DIAGONAL))
			return WHITEPIECE;
	}
	return 0;
}

int is_forbidden()
{
	for (int x = 0; x < SIZE; x++)
		for (int y = 0; y < SIZE; y++)
			if (record_board[x][y] == BLACKPIECE || record_board[x][y] == BLACKTRIANGLE)
			{
				int active_three = 0;
				int dead_four = 0;
				int active_four = 0;
				int overline = 0;
				
				for (int direction = 1; direction <= 4; direction++)
				{
					if (is_five_black(x, y, direction))
						return 0;
					if (num_active_three_black(x, y, direction))
						active_three++;
					if (num_dead_four_black(x, y, direction) + num_active_four_black(x, y, direction) > 1)
						active_four++;
					if (num_overline(x, y, direction))
						overline++;
				}

				if (active_three > 1)
					return 1;
				if (dead_four + active_four > 1)
					return 1;
				if (overline)
					return 1;
			}
	return 0;
}

void person_vs_person()
{
	while (1)
	{
		if (latest_x != -1 && latest_y != -1)
			record_board[latest_x][latest_y] = WHITEPIECE;
		drop_pieces(BLACKPIECE);
		record_to_display_array();
		display_board();
		if (game_win() == FORBIDDEN)
		{
			printf("黑棋触犯禁手，白棋胜利！\n");
			break;
		}
		else if (game_win() == BLACKPIECE)
		{
			printf("黑棋胜利！\n");
			break;
		}

		record_board[latest_x][latest_y] = BLACKPIECE;
		drop_pieces(WHITEPIECE);
		record_to_display_array();
		display_board();
		if (game_win() == WHITEPIECE)
		{
			printf("白棋胜利！\n");
			break;
		}
	}
}
void person_vs_computer()
{
	printf("请输入玩家选择哪一方(黑棋(B/b) 白棋(W/w)):\n");
	char mode;
	scanf("%c", &mode);
	getchar();
	if (toupper(mode) == 'B')
	{
		while(1)
		{
			if (latest_x != -1 && latest_y != -1)
				record_board[latest_x][latest_y] = WHITEPIECE;
			drop_pieces(BLACKPIECE);
			record_to_display_array();
			display_board();
			if (game_win() == FORBIDDEN)
				printf("黑棋触犯禁手，白棋胜利！\n");
			else if (game_win() == BLACKPIECE)
			{
				printf("黑棋胜利！\n");
				break;
			}
			alpha_beta_prune(DEPTH, 1, -INT_MAX, INT_MAX, WHITEPIECE);
			record_board[next_point_x][next_point_y] = WHITETRIANGLE;
			record_board[latest_x][latest_y] = BLACKPIECE;
			latest_x = next_point_x, latest_y = next_point_y;
			record_to_display_array();
			display_board();
			if (game_win() == WHITEPIECE)
			{
				printf("白棋胜利!\n");
				break;
			}
		}
	}
	else if (toupper(mode) == 'W')
	{
		record_board[7][7] = BLACKPIECE;
		record_to_display_array();
		display_board(); 
		while(1)
		{
			if (latest_x != -1 && latest_y != -1)
				record_board[latest_x][latest_y] = BLACKPIECE;
			drop_pieces(WHITEPIECE);
			record_to_display_array();
			display_board();
			if (game_win() == WHITEPIECE)
			{
				printf("白棋胜利！\n");
				break;
			}
			alpha_beta_prune(DEPTH, 1, -INT_MAX, INT_MAX, BLACKPIECE);
			record_board[next_point_x][next_point_y] = BLACKTRIANGLE;
			record_board[latest_x][latest_y] = WHITEPIECE;
			latest_x = next_point_x, latest_y = next_point_y;
			record_to_display_array();
			display_board();
			if (game_win() == BLACKPIECE)
			{
				printf("黑棋胜利!\n");
				break;
			}
		}
	}
}