#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "game_func.h"
#include "game.h"
#include "constants.h"

extern wchar_t init_display_board_array[SIZE][SIZE + 1];
extern wchar_t display_board_array[SIZE][SIZE + 1];
extern int record_board[SIZE][SIZE];
extern int latest_x, latest_y;
extern int latest_type;

// black pieces
wchar_t play1_pic = L'●'; 
wchar_t play1_current_pic = L'▲';
// white pieces
wchar_t play2_pic = L'○'; 
wchar_t play2_current_pic = L'△';

// initialize the chess board
void init_record_board()
{
	// set record_board to zero by double loop;
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			record_board[i][j] = 0;
}

// initialize adisplay_board according to record_board
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

// show the board(along with pieces)
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

// drop pieces

void drop_pieces(int type)
{
	printf("Please enter the position of the piece(e.g. H1 or h1):\n");
	while (1)
	{
		// input the position that you gonna put pieces in 
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
				record_board[coordinate_x][coordinate_y] = WHITEPIECE;
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

// detect winnership
int game_win()
{
	if (is_five_black(latest_x, latest_y) == -1)
		return FORBIDDEN;
	else if (is_five_black(latest_x, latest_y) == 1)
		return BLACKPIECE;
	else if (is_five_white(latest_x, latest_y))
		return WHITEPIECE;
	return 0;
}
