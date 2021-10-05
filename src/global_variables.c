#define SIZE 15
#define CHARSIZE 2

// the board uses GBK coding
// each Chinese character occupies two bytes
char init_display_board_array[SIZE][CHARSIZE * SIZE + 1] =
{
	"���өөөөөөөөөөөөө�",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"���۩۩۩۩۩۩۩۩۩۩۩۩۩�"
};

// this array is used to show the board(along with pieces)
char display_board_array[SIZE][SIZE * CHARSIZE + 1];

// this array is used to record the board(along with pieces)
int record_board[SIZE][SIZE];

// black pieces
char play1_pic[] = "��"; 
char play1_current_pic[] = "��";
// white pieces
char play2_pic[] = "��"; 
char play2_current_pic[] = "��";

// the position of the piece placed just now
int current_pos_x = -1, current_pos_y = -1;

// the type of previous pieces
// -1 for no pieces 
// 0 for black pieces && 1 for white pieces
int previous_type = -1;