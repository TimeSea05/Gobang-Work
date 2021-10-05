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

extern char init_display_board_array[SIZE][SIZE * CHARSIZE + 1];
extern char display_board_array[SIZE][SIZE * CHARSIZE + 1];
extern int record_board[SIZE][SIZE];
extern char play1_pic[];
extern char play1_current_pic[];
extern char play2_pic[];
extern char play2_current_pic[];
extern int current_pos_x;
extern int current_pos_y;
extern int previous_type;

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
	//��һ������init_display_board_array�м�¼�Ŀ����̣����Ƶ�display_board_array��
	//�ڶ�����ɨ��record_board����������0��Ԫ�أ�������ߡ��Ƶ�display_board_array����Ӧλ����
	//ע�⣺display_board_array����¼���ַ��������ַ���ÿ���ַ�ռ2���ֽڡ���͡�Ҳ�������ַ���ÿ��Ҳռ2���ֽڡ�
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
	if (current_pos_x != -1 && current_pos_y != -1)
		record_board[current_pos_x][current_pos_y] = 1 + previous_type * 6;
	
	printf("������Ҫ�µ���������(e.g. H1 or h1):\n");

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
			current_pos_x = coordinate_x;
			current_pos_y = coordinate_y;
			previous_type = type;
			getchar();
			break;
		}
		else
		{
			printf("��λ���ѱ���������ռ�ã����������룺\n");
			getchar();
			continue;
		}
	}
}

// detect winnership
int check_for_winnership()
{
	// ����
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
					return 1;	// ����
				else if (index == j + 5 && record_board[i][j] > 5)
					return 7;	// ����
				else
					j = index - 1;
			}
	// ����
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
	// б��
	// ���Խ���
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
	// �ζԽ���
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
