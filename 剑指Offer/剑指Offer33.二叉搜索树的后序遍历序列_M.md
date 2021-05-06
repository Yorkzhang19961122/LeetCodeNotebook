【题目】

输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历结果。如果是则返回 `true`，否则返回 `false`。假设输入的数组的任意两个数字都互不相同。

【示例】

参考以下这颗二叉搜索树：

```c++
     5
    / \
   2   6
  / \
 1   3
```

```c++
输入: [1,6,3,2,5]
输出: false
```

```c++
输入: [1,3,2,6,5]
输出: true
```

---

【[题解思路—递归分治](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-hou-xu-bian-li-xu-lie-lcof/solution/mian-shi-ti-33-er-cha-sou-suo-shu-de-hou-xu-bian-6/)】

**二叉搜索树的定义**：左子树中所有节点的值<根节点的值；右子树中所有节点的值>根节点的值；其左右子树也分别为二叉搜索树。

**递归终止条件**：当`i>=j`，说明此子树的节点数量小于等于1，无需判别其正确性，直接返回true即可（即叶子节点）

**递归**：

* **划分左右子树**：对于区间`[i, j]`，首先寻找**第一个大于根节点**的节点，索引记为`m`，此时可划分出左子树区间`[i, m-1]`，右子树区间`[m, j-1]`，根节点索引`j`
* **判断是否为二叉搜索树**：
  * **左子树区间**`[i, m-1]`内的所有节点值都应**小于**根节点值`postorder[j]`，而第一步划分左子树时已经保证了左子树区间的准确性，因此只要判断右子树区间即可
  * **右子树区间**`[m, j-1]`内的所有节点值都应**大于**根节点值`postorder[j]`：通过`p`从索引`m`开始遍历，当遇到`postorder[m]`小于等于根节点值`postorder[j]`时跳出，最后通过`p`是否遍历到了根节点`j`来判断是否为二叉搜索树
* **返回值**：
  * `p = j`判断**此树**是否正确
  * `recur(i, m - 1)`判断**此树的左子树**是否正确
  * `recur(m, j - 1)`判断**此树的右子树**是否正确

【题解代码—递归分治】

```c++
class Solution {
public:
    bool recur(vector<int>& postorder, int i, int j) {
        if(i >= j) return true;  //递归终止条件
        int m = i;  //m初始化为i
        while(postorder[m] < postorder[j]) m++;  //从i开始寻找第一个值大于根节点的索引（左子树）
        int p = m;  //初始化p为m
        while(postorder[p] > postorder[j]) p++;  //p从m开始遍历到根节点j，查看是否有值小于根节点（右子树）
        return p == j && recur(postorder, i, m - 1) && recur(postorder, m, j - 1);
    }

    bool verifyPostorder(vector<int>& postorder) {
        return recur(postorder, 0, postorder.size() - 1);
    }
};
```

思路相同，更清晰的题解代码：

```c++
class Solution {
public:

    bool recur(vector<int>& postorder, int left, int right) {
        if(left >= right) return true;  //递归终止条件，叶节点
        int rootValue = postorder[right];  //当前树的根节点值
        int m = left;  //借助m对当前的区间[left, right]进行遍历
        while(postorder[m] < rootValue && m < right) {  //找到第一个大于根节点的索引[left, m)--左子树
            m++;
        }
        for(int i = m; i < right; i++) {  //遍历m索引到当前根节点right[m, right)，判断是否都大于根节点值--右子树
            if(postorder[i] < rootValue) return false;
        }
        //当前树没问题就继续检查其左右子树
        if(!recur(postorder, left, m - 1)) return false;  //检查左子树
        if(!recur(postorder, m, right - 1)) return false;  //检查右子树
        return true;  //最终都没问题就返回true
    }
    bool verifyPostorder(vector<int>& postorder) {
        if(postorder.size() < 2) return true;  //特殊情况排除
        return recur(postorder, 0, postorder.size() - 1);
    }
};
```

