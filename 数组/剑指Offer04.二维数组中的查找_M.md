【题目】

在一个 n * m 的二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个高效的函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

【示例】

矩阵如下：

```c++
[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
```

给定 target = `5`，返回 `true`。

给定 target = `20`，返回 `false`。

---

【题解思路—近似于二叉搜索树】

从矩阵右上角往矩阵内部看，可以看到，往左时（即列减小），对应的元素值减小；往右时（即行增大），对应的元素值增大，因此只要把当前的元素值和target比较，然后更新行列数直到遍历结束。

【题解代码—近似于二叉搜索树】

```c++
class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        if(matrix.size() == 0 || matrix[0].size() == 0) return false;  //特殊情况处理[]和[[]]
        int m = matrix.size(), n = matrix[0].size();  //获得二维矩阵的行列数
        int row = 0, colum = n - 1;  //初始化到矩阵的右上角
        while(row < m && colum >= 0) {  //开始进行搜索
            if(matrix[row][colum] == target) return true;  //矩阵元素值等于target
            else if(matrix[row][colum] > target) {  //矩阵元素值大于target
                colum--;  //列数减小
            }
            else {  //矩阵元素值小于target
                row++;  //行数增大
            }
        } 
        return false;
    }
};
```

