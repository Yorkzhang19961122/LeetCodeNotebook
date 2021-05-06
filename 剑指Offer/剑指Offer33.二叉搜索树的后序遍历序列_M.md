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
        if(i >= j) return true;
        int m = i;
        while(postorder[m] < postorder[j]) m++;
        int p = m;
        while(postorder[p] > postorder[j]) p++;
        return p == j && recur(postorder, i, m - 1) && recur(postorder, m, j - 1);
    }

    bool verifyPostorder(vector<int>& postorder) {
        return recur(postorder, 0, postorder.size() - 1);
    }
};
```

