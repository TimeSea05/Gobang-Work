#include "constants.h"

// the board uses GBK coding
// each Chinese character occupies two bytes
char init_display_board_array[SIZE][CHARSIZE * SIZE + 1] =
{
	"©³©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©·",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©»©Û©Û©Û©Û©Û©Û©Û©Û©Û©Û©Û©Û©Û©¿"
};

// this array is used to show the board(along with pieces)
char display_board_array[SIZE][SIZE * CHARSIZE + 1];
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