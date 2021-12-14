#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "game_func.h"
#include "game.h"
#include "constants.h"
#include "ai.h"

extern wchar_t init_display_board_array[SIZE][SIZE + 1];
extern wchar_t display_board_array[SIZE][SIZE + 1];
extern int record_board[SIZE][SIZE];
extern int latest_x, latest_y;
extern int next_point_x, next_point_y;
extern int pos_x_arr[SIZE * SIZE], pos_y_arr[SIZE * SIZE];
extern int p_pos_arr;

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

int drop_pieces(int type, int game_mode)
{
	printf("请输入你要下的棋子的坐标(e.g. H1 or h1):\n");
	while (1)
	{
		char command[7];
		scanf("%s", command);
		if (!strcmp(command, "regret"))
		{
			regret(game_mode);
			return 1;
		}
		else
		{
			// 将输入转化为程序内部的坐标值
			int val_x = command[1] - '0';
			if (command[2] != '\0')
				val_x = val_x * 10 + command[2] - '0';
			int coordinate_x = -val_x + SIZE;
			int coordinate_y;
			if (isupper(command[0]))
				coordinate_y = command[0] - 'A';
			else
				coordinate_y = command[0]- 'a';
			if (coordinate_x >= SIZE || coordinate_x < 0 || coordinate_y >= SIZE || coordinate_y < 0)
			{
				printf("位置越界！请重新输入：\n");
				continue;
			}

			// 只有指定位置为空时才允许落子
			if (record_board[coordinate_x][coordinate_y] == EMPTY)
			{
				if (type == BLACKPIECE)
					record_board[coordinate_x][coordinate_y] = BLACKTRIANGLE;
				else if (type == WHITEPIECE)
					record_board[coordinate_x][coordinate_y] = WHITETRIANGLE;
				latest_x = coordinate_x, latest_y = coordinate_y;
				p_pos_arr++;
				pos_x_arr[p_pos_arr] = latest_x, pos_y_arr[p_pos_arr] = latest_y;
				getchar();
				break;
			}
			else
			{
				printf("这里已经有棋子了！请重新输入：\n");
				getchar();
				continue;
			}
		}
	}
	return 0;
}

void regret(int game_mode)
{
	if (game_mode == PERSON_VS_PERSON)
	{
		record_board[pos_x_arr[p_pos_arr]][pos_y_arr[p_pos_arr]] = EMPTY;
		p_pos_arr--;
		latest_x = pos_x_arr[p_pos_arr], latest_y = pos_y_arr[p_pos_arr];
	}
	else if (game_mode == PERSON_VS_COMPUTER)
	{
		// 需要拿掉人的棋子和机器下的棋子
		record_board[pos_x_arr[p_pos_arr]][pos_y_arr[p_pos_arr]] = EMPTY;
		p_pos_arr--;
		record_board[pos_x_arr[p_pos_arr]][pos_y_arr[p_pos_arr]] = EMPTY;
		p_pos_arr--;
		latest_x = pos_x_arr[p_pos_arr], latest_y = pos_y_arr[p_pos_arr];
	}
	// 将最后一步的棋子变成三角形
	if (record_board[latest_x][latest_y] == BLACKPIECE)
		record_board[latest_x][latest_y] = BLACKTRIANGLE;
	else if (record_board[latest_x][latest_y] == WHITEPIECE)
		record_board[latest_x][latest_y] = WHITETRIANGLE;
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
	// 扫描整个棋盘，只对黑色棋子位置进行判定
	for (int x = 0; x < SIZE; x++)
		for (int y = 0; y < SIZE; y++)
			if (record_board[x][y] == BLACKPIECE || record_board[x][y] == BLACKTRIANGLE)
			{
				// 各种可能触犯禁手的棋型的总数
				int active_three = 0;
				int dead_four = 0;
				int active_four = 0;
				int overline = 0;
				
				for (int direction = 1; direction <= 4; direction++)
				{
					// 只要形成五连禁手就会失效
					if (is_five_black(x, y, direction))
						return 0;
					if (num_active_three_black(x, y, direction))
						active_three++;
					if (num_dead_four_black(x, y, direction))
						dead_four++;
					if (num_active_four_black(x, y, direction))
						active_four++;
					if (num_overline(x, y, direction))
						overline++;
				}
				// 双活三
				if (active_three > 1)
					return 1;
				// 双四
				if (dead_four + active_four > 1)
					return 1;
				// 长连
				if (overline)
					return 1;
			}
	return 0;
}

void person_vs_person()
{
	while (1)
	{
		// 首先黑棋落子
		if (latest_x != -1 && latest_y != -1)
			record_board[latest_x][latest_y] = WHITEPIECE;
		drop_pieces(BLACKPIECE, PERSON_VS_PERSON);
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

		// 此后白棋落子
		drop_pieces(WHITEPIECE, PERSON_VS_PERSON);
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
	char chess_color;
	scanf("%c", &chess_color);
	getchar();
	if (toupper(chess_color) == 'B')
	{
		while(1)
		{
			// 玩家落子
			if (latest_x != -1 && latest_y != -1)
				record_board[latest_x][latest_y] = WHITEPIECE;
			if (drop_pieces(BLACKPIECE, PERSON_VS_COMPUTER))
			{
				record_to_display_array();
				display_board();
				continue;
			}
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

			// AI落子
			min_max_search(DEPTH, 1, -INT_MAX, INT_MAX, WHITEPIECE, 1);
			record_board[next_point_x][next_point_y] = WHITETRIANGLE;
			record_board[latest_x][latest_y] = BLACKPIECE;
			latest_x = next_point_x, latest_y = next_point_y;
			p_pos_arr++;
			pos_x_arr[p_pos_arr] = latest_x, pos_y_arr[p_pos_arr] = latest_y;
			record_to_display_array();
			display_board();
			printf("机器落子的位置为: %c%d\n", latest_y + 'A', SIZE - latest_x);
			if (game_win() == WHITEPIECE)
			{
				printf("白棋胜利!\n");
				break;
			}
		}
	}
	else if (toupper(chess_color) == 'W')
	{
		// 黑棋首先在棋盘中央落子
		record_board[7][7] = BLACKPIECE;
		record_to_display_array();
		display_board(); 

		while(1)
		{
			// 玩家落子
			if (latest_x != -1 && latest_y != -1)
				record_board[latest_x][latest_y] = BLACKPIECE;
			if (drop_pieces(WHITEPIECE, PERSON_VS_COMPUTER))
			{
				record_to_display_array();
				display_board();
				continue;
			}
			record_to_display_array();
			display_board();
			if (game_win() == WHITEPIECE)
			{
				printf("白棋胜利！\n");
				break;
			}

			// AI落子
			min_max_search(DEPTH, 1, -INT_MAX, INT_MAX, BLACKPIECE, 0.2);
			record_board[next_point_x][next_point_y] = BLACKTRIANGLE;
			record_board[latest_x][latest_y] = WHITEPIECE;
			latest_x = next_point_x, latest_y = next_point_y;
			p_pos_arr++;
			pos_x_arr[p_pos_arr] = latest_x, pos_y_arr[p_pos_arr] = latest_y;
			record_to_display_array();
			display_board();
			printf("机器落子的位置为: %c%d\n", latest_y + 'A', SIZE - latest_x);
			if (game_win() == BLACKPIECE)
			{
				printf("黑棋胜利!\n");
				break;
			}
		}
	}
}