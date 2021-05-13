【题目】

给定一个 `m x n` 二维字符网格 `board` 和一个字符串单词 `word` 。如果 `word` 存在于网格中，返回 `true` ；否则，返回 `false` 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。

例如，在下面的 3×4 的矩阵中包含单词 "ABCCED"（单词中的字母已标出）。

![](.\DFS\剑指Offer12.矩阵中的路径_M\word2.jpg)

【示例】

```c++
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
输出：true
```

```c++
输入：board = [["a","b"],["c","d"]], word = "abcd"
输出：false
```

---

【[题解思路—DFS+剪枝](https://leetcode-cn.com/problems/ju-zhen-zhong-de-lu-jing-lcof/solution/mian-shi-ti-12-ju-zhen-zhong-de-lu-jing-shen-du-yo/)】

这是一个非常典型的矩阵搜索问题，类似题目有：[剑指Offer13.机器人的运动范围](https://github.com/Yorkzhang19961122/LeetCodeNotebook/blob/main/%E5%89%91%E6%8C%87Offer/%E5%89%91%E6%8C%87Offer13.%E6%9C%BA%E5%99%A8%E4%BA%BA%E7%9A%84%E8%BF%90%E5%8A%A8%E8%8C%83%E5%9B%B4_M.md)，此类题目通常可以采用**深度优先搜索**和**剪枝**来解决。

* **深度优先搜索：** 可以理解为暴力法遍历矩阵中所有字符串可能性。DFS 通过递归，先朝一个方向搜到底，再回溯至上个节点，沿另一个方向搜索，以此类推

* **剪枝：** 在搜索中，遇到 `这条路不可能和目标字符串匹配成功` 的情况（*例如：此矩阵元素和目标字符不同、此元素已被访问）*，则应立即返回，称之为 `可行性剪枝`

**主函数exist**：

两重循环遍历`board`中的每一个字符，对每一个字符进行DFS，若DFS判断成功，则`return true`，否则继续处理`board`中的下一个元素，如果遍历完`board`的所有元素，仍未返回过`true`，则说明`board`中不存在`word`，返回`false`。

同时借助一个二维数组`visited`，用来记录`board`某位置上的字符是否被访问过

**DFS的过程**：

`dfs`函数参数：`board`，`word`，当前处理的字符的坐标位置`r`，`c`，当前字符是否被访问过`visited`，当前字符在`word`中的下标索引`k`

终止条件：

* 返回`false`：如果`r`，`c`超过`board`的边界，或者`rc`位置上的字母已经访问过，或者`rc`位置上的字母和`word`中目标字符不同
* 返回`true`：如果`k`等于`word.size()`，说明`word`已全部匹配

递推工作：

* 将`rc`位置上的字符在`visited`中标记为访问过

* 搜索下一个单元格，朝当前元素的 **上、下、左、右** 四个方向开启下层递归，使用 `或` 连接 （代表只需找到一条可行路径就直接返回，不再做后续 DFS ），并记录结果至 `res`
* 还原当前的元素：将`visited[r][c]`还原为`false`（**因为它只代表本次搜索过程中该元素已访问过，当初始的`i,j`变化时，又开始了另一次搜索过程**）

返回值：返回`res`，表示是否搜索到目标字符串

【题解代码—DFS+剪枝】

```c++
class Solution {
public:
    int rows, cols;  
    int k = 0;
    bool exist(vector<vector<char>>& board, string word) {
        rows = board.size();  //board的行数
        cols = board[0].size();  //board的列数
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));  //visited数组用来记录格子中元素是否被访问过
        //两重遍历循环处理格子中的所有元素
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                if(dfs(board, word, i, j, visited, k)) {  //对每一个元素，都进行dfs，判断是否能搜索到目标字串
                    return true;  //如果能搜索到，返回true
                }
            }
        }
        return false;  //遍历完整个格子（board）都未返回true，说明word不在board中连续存在
    }
    
    bool dfs(vector<vector<char>>& board, string& word, int r, int c, vector<vector<bool>>& visited, int k) {
        //r,c越界，或rc位置上的字母已经访问过，或rc位置上的字母不等于word在k位置上的字母
        if(r < 0 || r >= rows || c < 0 || c >= cols || visited[r][c] || board[r][c] != word[k]) {
            return false;
        }
        if(++k == word.size()) {  //++k等于word的长度，说明word都已经被匹配上了，注意此处的前置自增
            return true;
        }
        visited[r][c] = true;  //将当前访问的字符标记为访问过（true）
        //递归访问当前位置上下左右四个方向的字符，用或连接，只要一个方向满足就可以继续
        bool res = dfs(board, word, r + 1, c, visited, k)   
                || dfs(board, word, r - 1, c, visited, k) 
                || dfs(board, word, r, c + 1, visited, k) 
                || dfs(board, word, r, c - 1, visited, k);
        visited[r][c] = false;  //还原当前访问状态，方便接下来新的访问
        return res;  //回溯返回
    }
};
```

