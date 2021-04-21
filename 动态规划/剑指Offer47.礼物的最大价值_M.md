【题目】

在一个 m*n 的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值（价值大于 0）。你可以从棋盘的左上角开始拿格子里的礼物，并每次向右或者向下移动一格、直到到达棋盘的右下角。给定一个棋盘及其上面的礼物的价值，请计算你最多能拿到多少价值的礼物？

【示例】

```c++
输入: 
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
输出: 12
解释: 路径 1→3→5→2→1 可以拿到最多价值的礼物
```

---

【[题解思路—动态规划](https://leetcode-cn.com/problems/li-wu-de-zui-da-jie-zhi-lcof/solution/jian-zhi-offer-47-li-wu-de-zui-da-jie-zh-705a/)】

* **定义数组的含义**：`dp[i][j]`表示到`grid[i][j]`位置时的最大礼物价值
* **确定初值**：
  * 当只有一个礼物时（一个格子），礼物的最大值就是这一个格子，即`dp[0][0] = grid[0][0]`
  * 对于最左边的一列：只能从上边的礼物中向下累加得到当前位置的礼物价值和，且路径唯一（因为只能向下或向右移动），即`dp[i][0] = dp[i-1][0] + gridp[i][0]`
  * 对于最上面的一行：只能从左边的礼物中向右累加得到当前位置的礼物价值和，且路径唯一，即`dp[0][i] = dp[0][i-1] + grid[0][i]`
* **确定转移方程**：
  * 对于不在上述边界中的礼物，对于当前礼物，要选择它左边或者上边礼物价值中较大的那一个并与当前位置上的礼物价值相加，即`dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + grid[i][j]`

【题解代码—动态规划】

```c++
class Solution {
public:
    int maxValue(vector<vector<int>>& grid) {
        int row = grid.size();
        int colum = grid[0].size();
        vector<vector<int>> dp(row, vector<int>(colum, 0));  //初始化二维数组
        dp[0][0] = grid[0][0];  //初始值确定
        for(int i = 1; i < row; i++) {  //最左边列
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        for(int i = 1; i < colum; i++) {  //最上边行
            dp[0][i] = dp[0][i - 1] + grid[0][i];
        }

        for(int i = 1; i < row; i++) {  //其余位置
            for(int j = 1; j < colum; j++) {
                dp[i][j] = max(dp[i - 1][j], dp[i][j-1]) + grid[i][j];
            }
        }
        return dp[row - 1][colum - 1];  //返回到最右下角能取得的最大礼物价值
    }
};
```

