# 对count = 2情形的解释

## 1. 基本单元

**空黑黑空黑空** || **空黑空黑黑空**(无论是horizontal还是vertical还是diagonal)

<font color="red">p1</font>       <font color="red">p2</font>                     <font color="red">p1</font>       <font color="red">p2</font>    

这是**count=2**情形最重要的基本单元，如果该基本单元不存在，那么必然不可能形成活三

## 2. 情形分析

此处以horizontal为例，vertical & diagonal类似

### 棋盘左端

**|**空黑黑空黑空	or	**|**空黑空黑黑空

以上为示意图

在右端再放置一个黑色棋子的话，会形成四，故这种操作是被禁止的

在右端再放置一个白色棋子的话，可以验证，这仍然是活三

右端空着的话也仍然是活三

### 棋盘右端

空黑黑空黑空**|**	or	**|**空黑空黑黑空

以上为示意图

在左端再放置一个黑色棋子的话，会形成四，故这种操作是被禁止的

在左端再放置一个白色棋子的话，可以验证，这仍然是活三

左端空着的话也仍然是活三

### 棋盘中间

空黑黑空黑空	or	空黑空黑黑空

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

## 3. 代码实例

```c
if (count == 2)
    {
        // the other black piece is in the left of the two
        if (p1 >= 0 && record_board[x][p1] == 0 && p1 - 1 >= 0
              && (record_board[x][p1 - 1] == BLACKPIECE || record_board[x][p1 - 1] == BLACKTRIANGLE)
            && p1 - 2 >= 0 && record_board[x][p1 - 2] == 0 && p2 < SIZE && record_board[x][p2] == 0)
        {
            if (p1 - 3 >= 0)
            {
                if (record_board[x][p1 - 3] != BLACKPIECE && record_board[x][p1 - 3] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p2 + 1 < SIZE)
                    {
                        if (record_board[x][p2 + 1] != BLACKPIECE && record_board[x][p2 + 1] != BLACKTRIANGLE)
                            return 1;
                    }
                    // right side of the board
                    else
                        return 1;
                }
            }
            // left side of the board
            else if (p2 + 1 < SIZE && record_board[x][p2 + 1] != BLACKPIECE && record_board[x][p2 + 1] != BLACKTRIANGLE)
                return 1;
        }
        // the other black piece is in the right of the two
        if (p1 >= 0 && record_board[x][p1] == 0 && p2 < SIZE && record_board[x][p2] == 0 && p2 + 1 < SIZE 
            && (record_board[x][p2 + 1] == BLACKPIECE || record_board[x][p2 + 1] == BLACKTRIANGLE)
            && p2 + 2 < SIZE && record_board[x][p2 + 2] == 0)
        {
            if (p2 + 3 < SIZE)
            {
                if (record_board[x][p2 + 3] != BLACKPIECE && record_board[x][p2 + 3] != BLACKTRIANGLE)
                {
                    // middle of the board
                    if (p1 - 1 >= 0)
                    {
                        if (record_board[x][p1 - 1] != BLACKPIECE && record_board[x][p1 - 1] != BLACKTRIANGLE)
                            return 1;
                    }
                    // left side of the board
                    else
                        return 1;
                }
            }
            // right side of the board
            else if (p1 - 1 >= 0 && record_board[x][p1 - 1] != BLACKPIECE && record_board[x][p1 - 1] != BLACKTRIANGLE)
                return 1;
        }

    }
```



