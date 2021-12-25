#include "constants.h"

// 棋盘数组
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

// 显示数组
wchar_t display_board_array[SIZE][SIZE + 1];

// 记录数组
int record_board[SIZE][SIZE];

// 最后放置棋子的位置
int latest_x = -1, latest_y = -1;

// AI将要放置棋子的位置
int next_point_x = 0, next_point_y = 0;

// 记录下棋顺序的数组
int pos_x_arr[SIZE * SIZE], pos_y_arr[SIZE * SIZE];
// 指向最后一次落子位置的指针
int p_pos_arr = -1;

// 记录棋子所在的范围，避免无效的字符串比较
int leftest = SIZE, rightest = -1;
int uppest = SIZE, downest = -1;
int md_leftest_up = SIZE, md_rightest_up = -1, md_leftest_down = SIZE, md_rightest_down = -1;
int sd_leftest_up = SIZE, sd_rightest_up = -1, sd_leftest_down = SIZE, sd_rightest_down = -1;

// 剪枝次数
int prune_times = 0;