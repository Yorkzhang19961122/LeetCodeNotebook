【题目】

输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。

【实例】

```c++
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,2,3,6,9,8,7,4,5]
```

---

【题解思路】

1.空值处理： 当 matrix 为空时，直接返回空列表 [] 即可。

2.初始化： 矩阵 左、右、上、下 四个边界 l , r , t , b ，用于打印的结果列表 res 。

3.循环打印： “从左向右、从上向下、从右向左、从下向上” 四个方向循环，每个方向打印中做以下三件事；

> 1.根据边界打印，即将元素按顺序添加至列表 res 尾部；
>
> 2.边界向内收缩 1 （代表已被打印）；
>
> 3.判断是否打印完毕（边界是否相遇），若打印完毕则跳出。

【题解代码】

```c++
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        if(matrix.empty()) return res;
        int l = 0;  //左
        int r = matrix[0].size() - 1;  //右（二维矩阵列数 - 1）
        int t = 0;  //上
        int b = matrix.size() - 1;  //下（二维矩阵行数 - 1）
        while(true) {
            //left->right
            for(int i = l; i <= r; i++) res.push_back(matrix[t][i]);
            ++t;  //向下收缩
            if(t > b) break;
            //top->bottom
            for(int i = t; i <= b; i++) res.push_back(matrix[i][r]);
            --r;  //向左收缩
            if(r < l) break;
            //right->left
            for(int i = r; i >= l; i--) res.push_back(matrix[b][i]);
            --b;  //向上收缩
            if(b < t) break;
            //bottom->top
            for(int i = b; i >=t; i--) res.push_back(matrix[i][l]);
            ++l;  //向右收缩
            if(l > r) break;
        }
        return res;
    }
};
```

