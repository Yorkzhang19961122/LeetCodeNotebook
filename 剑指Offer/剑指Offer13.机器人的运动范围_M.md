【题目】

地上有一个m行n列的方格，从坐标 `[0,0]` 到坐标 `[m-1,n-1]` 。一个机器人从坐标 `[0, 0]` 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），也不能进入行坐标和列坐标的数位之和大于k的格子。例如，当k为18时，机器人能够进入方格 [35, 37] ，因为3+5+3+7=18。但它不能进入方格 [35, 38]，因为3+5+3+8=19。请问该机器人能够到达多少个格子？

【示例】

```c++
输入：m = 2, n = 3, k = 1
输出：3
```

```c++
输入：m = 3, n = 1, k = 0
输出：1
```

---

【[题解思路1—DFS](https://leetcode-cn.com/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof/solution/jian-zhi-offerer-shua-javadfs-bfs-tu-jie-py05/)】

* 借助一个二维数组标记某格子是否被访问过
* 每次到一个格子就有四个方向可以搜索
* 搜索过程中不合格的格子不被统计（递归终止条件）
  * 超出边界
  * 格子已经被访问过
  * 不满足行列位数之和小于k的格子
* 行列数位之和可以采用函数进行计算(`get()`函数)

【题解代码1—DFS】

```c++
class Solution {
public:
    int movingCount(int m, int n, int k) {
        vector<vector<bool>> visited(m, vector(n, false));  //初始化一个visited数组用于存放哪些格子被访问过
        return dfs(m, n, k, visited, 0, 0);  //执行递归
    }

    int get(int position) {  //返回机器人当前行或列的坐标数位和
        int res = 0;
        while(position) {
            res += position % 10;
            position /= 10;
        }
        return res;
    }

    int dfs(int m, int n, int k, vector<vector<bool>>& visited, int row, int col) {
        if((get(row) + get(col)) > k || row < 0 || row >= m || col < 0 || col >= n || visited[row][col]) {
            return 0;  //递归终止条件：行列数位之和大于k；机器人超过方格的范围；当前格子已经被访问过
        }
        visited[row][col] = true;  //满足条件的且被第一次访问的格子被设置为true
        //递归处理当前格子的上下左右四个方向
        return 1 + dfs(m, n, k, visited, row - 1, col)
                 + dfs(m, n, k, visited, row + 1, col)
                 + dfs(m, n, k, visited, row, col - 1)
                 + dfs(m, n, k, visited, row, col + 1);
        //回溯的返回过程
    }
};
```

由于机器人的起始位置坐标为`[0, 0]`，因此只要向右和向下即可访问到表格的所有元素，因此只需要考虑向右和向下即可：

```c++
class Solution {
public:
    int movingCount(int m, int n, int k) {
        vector<vector<bool>> visited(m, vector(n, false));  //初始化一个visited数组用于存放哪些格子被访问过
        return dfs(m, n, k, visited, 0, 0);  //执行递归
    }

    int get(int position) {  //返回机器人当前行或列的坐标数位和
        int res = 0;
        while(position) {
            res += position % 10;
            position /= 10;
        }
        return res;
    }

    int dfs(int m, int n, int k, vector<vector<bool>>& visited, int row, int col) {
        if((get(row) + get(col)) > k || row < 0 || row >= m || col < 0 || col >= n || visited[row][col]) {
            return 0;  //递归终止条件：行列数位之和大于k；机器人超过方格的范围；当前格子已经被访问过
        }
        visited[row][col] = true;  //满足条件的且被第一次访问的格子被设置为true
        //递归处理当前格子的上下左右四个方向
        return 1 + dfs(m, n, k, visited, row + 1, col)  //向下
                 + dfs(m, n, k, visited, row, col + 1);  //向右
        //回溯的返回过程
    }
};
```

【[题解思路2—BFS](https://leetcode-cn.com/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof/solution/jian-zhi-offerer-shua-javadfs-bfs-tu-jie-py05/)】

对于DFS和BFS，我们可以做如下分析：

* DFS：沿着某一个方向先走到底，直到不满足递归条件了才回头，因此借助**栈**来实现，递归就是利用系统栈
* BFS：先访问离当前格子最近的格子，借助**队列**实现

核心思想（联想一下二叉树的层序遍历，有相似之处）：

* 每次访问队列的第一个元素
* 判断该元素是否符合要求
* 将该元素能访问到的元素存入队列

【题解代码2—BFS】

```c++
class Solution {
public:
    int movingCount(int m, int n, int k) {
        vector<vector<bool>> visited(m, vector<bool>(n, false));  //二维数组visited用于记录某格子是否被访问过
        queue<vector<int>> que;  //用队列进行BFS
        que.push(vector<int>{0, 0});  //将机器人的出发点(0,0)放入队列中
        int res = 0;
        while(!que.empty()) {  //遍历队列
            vector<int> temp = que.front();  //temp用于存储队列头的坐标对
            que.pop();  //队列头出队列
            int row = temp[0], col = temp[1];  //得到行列坐标
            if(get(row) + get(col) > k || row >= m || col >= n || visited[row][col]) {  //假如此格子不满足要求
                continue;  //继续while循环
            }
            res++;  //否则结果值加1
            visited[row][col] = true;  //对应的格子标记为访问过
            que.push(vector<int>{row + 1, col});  //将下边的格子坐标push入队列
            que.push(vector<int>{row, col + 1});  //将右边的格子坐标push入队列
        }
        return res;
    }

    int get(int position) {
        int res = 0;
        while(position) {
            res += position % 10;
            position /= 10;
        }
        return res;
    }
};
```

