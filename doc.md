## 棋型的判定

本程序中使用字符串匹配算法来进行棋型的判定。

只有刚落下的棋子对场上的局势有改变，故我们只需要针对刚落下的棋子进行分析即可

### 转换成字符串

```c
char * to_string(int x, int y, int direction);
```

该函数通过调用一下四个函数来获得四个方向上的字符串

```c
char * to_string_horizontal(int x, int y);
char * to_string_vertical(int x, int y);
char * to_string_main_diagonal(int x, int y);
char * to_string_sub_diagonal(int x, int y);
```

注意：由于动态内存分配的原因，函数`to_string`应该与函数`free()`共同使用。

### 字符串匹配

```c
int str_match(char * str_s, char * str_l);
```

该函数返回字符串`str_l`中`str_s`的个数。

### 获取指定坐标棋子周围特定棋型的数目

首先我们需要定义某种特定棋型对应的字符串。

此处我们使用0代表空，1代表黑色棋子，2代表白色棋子。

如黑色活三棋型：

```c
char active_three_B_1[] = "011100\0";
char active_three_B_2[] = "011010\0";
```

我们对指定棋子周围活三的数目进行计数：

```c
int num_active_three_black(int x, int y);
```

从四个方向进行：

```c
#define HORIZONTAL 1
#define VERTICAL 2
#define MAIN_DIAGONAL 3
#define SUB_DIAGONAL 4
```

开始计数：

```c
int num_active_three_black(int x, int y)
{
	int res = 0;
    char * r_active_three_B_1 = str_reverse(active_three_B_1);
    char * r_active_three_forbidden_1 = str_reverse(active_three_forbidden_1);
    char * r_active_three_forbidden_2 = str_reverse(active_three_forbidden_2);

    char * r_active_three_B_2 = str_reverse(active_three_B_2);
    char * r_active_three_forbidden_3 = str_reverse(active_three_forbidden_3);
    char * r_active_three_forbidden_4 = str_reverse(r_active_three_forbidden_4);

    for (int direction = 1; direction <= 4; direction++)
    {
        char * str = to_string(x, y, direction);
        res += str_match(active_three_B_1, str);
        res -= str_match(active_three_forbidden_1, str);
        res -= str_match(active_three_forbidden_2, str);

        res += str_match(active_three_B_2, str);
        res -= str_match(active_three_forbidden_3, str);
        res -= str_match(active_three_forbidden_4, str);
		
        // reverse
        res += str_match(r_active_three_B_1, str);
        res -= str_match(r_active_three_forbidden_1, str);
        res -= str_match(r_active_three_forbidden_2, str);

        res += str_match(r_active_three_B_2, str);
        res -= str_match(r_active_three_forbidden_3, str);
        res -= str_match(r_active_three_forbidden_4, str);

        // symmetry
        res -= str_match(s_active_three_B_1, str);
        res -= str_match(s_active_three_B_2, str);
        res += str_match(s_active_three_forbidden_1, str);
        res += str_match(s_active_three_forbidden_3, str);
        res += str_match(s_active_three_forbidden_4, str);

        free(str);
    }

    free(r_active_three_B_1);
    free(r_active_three_forbidden_1);
    free(r_active_three_forbidden_2);

    free(r_active_three_B_2);
    free(r_active_three_forbidden_3);
    free(r_active_three_forbidden_4);

    return res;
}
```

对于某一个特定的方向：

* 首先对活三对应的棋型进行匹配，并去除假活三的情形**(forbidden)**
* 再对活三对应字符串的逆向字符串**(r)**进行匹配，并去除相应的逆向假活三的情形(如果一个棋型对应的字符串是对称的，那么不再进行逆向操作)
* 在某些特定对称情形**(s)**下，正向与逆向两次技术会导致重复计数，此时我们再去除这些特定对称情形
* 最终我们得到结果

对于活三而言，这些特殊对称情形是：

```c
char s_active_three_B_1[] = "0011100\0";
char s_active_three_forbidden_1[] = "100111001\0";
char s_active_three_B_2[] = "01011010\0";
char s_active_three_forbidden_3[] = "01011010\0";
char s_active_three_forbidden_4[] = "1010110101\0";
```

**对于其他棋型，思路类似。**
