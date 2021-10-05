# 对count = 1情形的解释

## 1. 基本单元

**空黑黑空黑空** || **空黑空黑黑空**(无论是horizontal还是vertical还是diagonal)

​            <font color="red">p1</font>   <font color="red">p2</font>      <font color="red">p1</font>   <font color="red">p2</font>    

这是**count=1**情形最重要的基本单元，如果该基本单元不存在，那么必然不可能形成活三

## 2. 情形分析

此处以horizontal为例，vertical&diagonal类似

### 棋盘左端

|空黑黑空黑空	or	|空黑空黑黑空

基本单元的左侧是棋盘边界，基本单元右侧不能为黑色棋子

### 棋盘右端

空黑黑空黑空|	or	空黑空黑黑空|

基本单元的右侧是棋盘边界，基本单元左侧不能为黑色棋子

### 棋盘中间

对于在中间的情形(针对第一种情形，第二种情形类似)，如果

* 1.左边放置黑色棋子: 	形成四	这种操作是被禁止的

* 2.右边放置黑色棋子:	

  如果此时白棋让黑棋一手，那么黑棋有三种位置可以选择

  - 下在最左边的空里面 那么白棋只要下在中间的空中，那么黑棋就不能形成五连
  - 下在中间的空里面 那么白棋只要放在最左边的空中，那么黑棋要是再下到最右边的空中，形成长连禁手
  - 下载最左边的空里面 无意义

- 3.左右都放置黑色棋子 显然不能构成活三

通过上面的分析，我们能够得出，在棋盘中间的时候，基本单元左右两侧都不能有棋子

不难得出，基本单元左右两侧是白棋子或者空都构成活三

## 3.代码示例

```c
if (count == 1)
    {
        // the other two black pieces are in the right of this piece
        if (p1 >= 0 && record_board[x][p1] == 0 && p2 < SIZE && record_board[x][p2] == 0
            && p2 + 1 < SIZE && (record_board[x][p2 + 1] == BLACKPIECE || record_board[x][p2 + 1] == BLACKTRIANGLE)
            && p2 + 2 < SIZE && (record_board[x][p2 + 2] == BLACKPIECE || record_board[x][p2 + 2] == BLACKTRIANGLE)
            && p2 + 3 < SIZE && record_board[x][p2 + 3] == 0)
        {
            if (p1 - 1 >= 0)
            {
                if (record_board[x][p1 - 1] != BLACKPIECE && record_board[x][p1 - 1] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p2 + 4 < SIZE)
                    {
                        if (record_board[x][p2 + 4] != BLACKPIECE && record_board[x][p2 + 4] != BLACKTRIANGLE)
                            return 1;
                    }
                    // right side of the board
                    else
                        return 1;
                }
            }
            else if (p2 + 4 < SIZE && record_board[x][p2 + 4] != BLACKPIECE && record_board[x][p2 + 4] != BLACKTRIANGLE)
                return 1;
        }
        // if the other two pieces is in the left of this piece
        if (p2 < SIZE && record_board[x][p2] == 0 && p1 >= 0 && record_board[x][p1] == 0
            && p1 - 1 >= 0 && (record_board[x][p1 - 1] == BLACKPIECE || record_board[x][p1 - 1] == BLACKTRIANGLE)
            && p1 - 2 >= 0 && (record_board[x][p1 - 2] == BLACKPIECE || record_board[x][p1 - 2] == BLACKTRIANGLE)
            && p1 - 3 >= 0 && record_board[x][p1 - 3] == 0)
        {
            if (p2 + 1 < SIZE)
            {
                if (record_board[x][p2 + 1] != BLACKPIECE && record_board[x][p2 + 1] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p1 - 4 >= 0)
                    {
                        if (record_board[x][p1 - 4] != BLACKPIECE && record_board[x][p1 - 4] != BLACKTRIANGLE)
                            return 1;
                    }
                    // left side of the board
                    else
                        return 1;
                }
            }
            else if (p1 - 4 >= 0 && record_board[x][p1 - 4] != BLACKPIECE && record_board[x][p1 - 4] != BLACKTRIANGLE)
                return 1;
        }
    }
```



