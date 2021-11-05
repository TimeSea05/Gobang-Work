#include "constants.h"

// the board
wchar_t init_display_board_array[SIZE][SIZE + 1] =
{
	{L'┏',L'┯',L'┯',L'┯',L'┯',L'┯',L'┯',L'┯',L'┯',L'┯',L'┯',L'┯',L'┯',L'┯',L'┓'},
	{L'┠',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┨'},
	{L'┠',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┨'},
	{L'┠',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┨'},
	{L'┠',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┨'},
	{L'┠',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┨'},
	{L'┠',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┨'},
	{L'┠',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┨'},
	{L'┠',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┨'},
	{L'┠',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┨'},
	{L'┠',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┨'},
	{L'┠',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┨'},
	{L'┠',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┨'},
	{L'┠',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┼',L'┨'},
	{L'┗',L'┷',L'┷',L'┷',L'┷',L'┷',L'┷',L'┷',L'┷',L'┷',L'┷',L'┷',L'┷',L'┷',L'┛'}
};

// this array is used to show the board(along with pieces)
wchar_t display_board_array[SIZE][SIZE + 1];

// this array is used to record the board(along with pieces)
int record_board[SIZE][SIZE];

// the position of the piece placed just now
int latest_x = -1, latest_y = -1;

// the type of previous pieces
// -1 for no pieces 
// 0 for black pieces && 1 for white pieces
int latest_type = -1;

// where AI is going to put its next piece
int next_point_x = 0, next_point_y = 0;