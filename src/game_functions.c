#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "game_functions.h"

#define SIZE 15
#define CHARSIZE 2

#define BLACKPIECE 1
#define BLACKTRIANGLE 3
#define WHITEPIECE 7
#define WHITETRIANGLE 9

// the board uses GBK coding
// each Chinese character occupies two bytes
char init_display_board_array[SIZE][CHARSIZE * SIZE + 1] =
{
	"┏┯┯┯┯┯┯┯┯┯┯┯┯┯┓",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┗┷┷┷┷┷┷┷┷┷┷┷┷┷┛"
};

// this array is used to show the board(along with pieces)
char display_board_array[SIZE][SIZE * CHARSIZE + 1];
// this array is used to record the board(along with pieces)
int record_board[SIZE][SIZE];

// the position of the piece placed just now
int lastest_x = -1, lastest_y = -1;

// the type of previous pieces
// -1 for no pieces 
// 0 for black pieces && 1 for white pieces
int lastest_type = -1;

// black pieces
char play1_pic[] = "●"; 
char play1_current_pic[] = "▲";
// white pieces
char play2_pic[] = "○"; 
char play2_current_pic[] = "△";

// the position of the piece placed just now
int latest_x = -1, latest_y = -1;

// the type of previous pieces
// -1 for no pieces 
// 0 for black pieces && 1 for white pieces
int latest_type = -1;

// initialize the chess board
void init_record_board()
{
	// set record_board to zero by double loop
	int i, j;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			record_board[i][j] = 0;
}

// initialize adisplay_board according to record_board
void record_to_display_array()
{
	//第一步：将init_display_board_array中记录的空棋盘，复制到display_board_array中
	//第二步：扫描record_board，当遇到非0的元素，将●或者◎复制到display_board_array的相应位置上
	//注意：display_board_array所记录的字符是中文字符，每个字符占2个字节。●和◎也是中文字符，每个也占2个字节。
	int i, j;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < CHARSIZE * SIZE; j++)
			display_board_array[i][j] = init_display_board_array[i][j];
	
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (record_board[i][j] == BLACKPIECE)
			{
				display_board_array[i][CHARSIZE * j] = play1_pic[0];
				display_board_array[i][CHARSIZE * j + 1] = play1_pic[1];
			}
			else if (record_board[i][j] == WHITEPIECE)
			{
				display_board_array[i][CHARSIZE * j] = play2_pic[0];
				display_board_array[i][CHARSIZE * j + 1] = play2_pic[1];
			}
			else if (record_board[i][j] == BLACKTRIANGLE)
			{
				display_board_array[i][CHARSIZE * j] = play1_current_pic[0];
				display_board_array[i][CHARSIZE * j + 1] = play1_current_pic[1];
			}
			else if (record_board[i][j] == WHITETRIANGLE)
			{
				display_board_array[i][CHARSIZE * j] = play2_current_pic[0];
				display_board_array[i][CHARSIZE * j + 1] = play2_current_pic[1];
			}
		}
	}
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

		for (j = 0; j < SIZE * CHARSIZE + 1; j++)
			printf("%c", display_board_array[i][j]);
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
// type: 0 for black pieces, 1 for white pieces
void drop_pieces(int type)
{
	// if the game has begun, then change triangles to round pieces
	if (latest_x != -1 && latest_y != -1)
		record_board[latest_x][latest_y] = 1 + latest_type * 6;
	
	printf("请输入要下的棋子坐标(e.g. H1 or h1):\n");

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
			record_board[coordinate_x][coordinate_y] = BLACKTRIANGLE + type * 6;
			latest_x = coordinate_x;
			latest_y = coordinate_y;
			latest_type = type;
			getchar();
			break;
		}
		else
		{
			printf("此位置已被其他棋子占用！请重新输入：\n");
			getchar();
			continue;
		}
	}
}

// detect winnership
int check_for_winnership()
{
	// 横着
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j <= SIZE - 5; j++)
			if (record_board[i][j] != 0)
			{
				int index = j;
				while (++index < j + 5)
				{
					if (record_board[i][index] != record_board[i][j]
						&& abs(record_board[i][index] - record_board[i][j]) != 2)
						break;
				}
				if (index == j + 5 && record_board[i][j] < 5)
					return 1;	// 黑棋
				else if (index == j + 5 && record_board[i][j] > 5)
					return 7;	// 白棋
				else
					j = index - 1;
			}
	// 竖着
	for (int j = 0; j < SIZE; j++)
		for (int i = 0; i <= SIZE - 5; i++)
			if (record_board[i][j] != 0)
			{
				int index = i;
				while (++index < i + 5)
				{
					if (record_board[index][j] != record_board[i][j]
						&& abs(record_board[index][j] - record_board[i][j]) != 2)
						break;
				}
				if (index == i + 5 && record_board[i][j] < 5)
					return 1;
				else if (index == i + 5 && record_board[i][j] > 5)
					return 7;
				else
					i = index - 1;
			}
	// 斜着
	// 主对角线
	for (int i = 0; i <= SIZE - 5; i++)
		for (int j = 0; j <= SIZE - 5; j++)
			if (record_board[i][j] != 0)
			{
				int count = 1;
				while (record_board[i + count][j + count] == record_board[i][j]
					   || abs(record_board[i + count][j + count] - record_board[i][j]) == 2)
					count++;
				if (count == 5 && record_board[i][j] < 5)
					return 1;
				else if (count == 5 && record_board[i][j] > 5)
					return 7;
			}
	// 次对角线
	for (int i = 4; i < SIZE; i++)
		for (int j = 0; j <= SIZE - 5; j++)
			if (record_board[i][j] != 0)
			{
				int count = 1;
				while (record_board[i - count][j + count] == record_board[i][j]
					   || abs(record_board[i - count][j + count] - record_board[i][j]) == 2)
					count++;
				if (count == 5 && record_board[i][j] < 5)
					return 1;
				else if (count == 5 && record_board[i][j] > 5)
					return 7;
			}
	
	return 0;
}
