【题目】

输入一棵二叉树的根节点，求该树的深度。从根节点到叶节点依次经过的节点（含根、叶节点）形成树的一条路径，最长路径的长度为树的深度。

【示例】

给定二叉树 `[3,9,20,null,null,15,7]`，

```
    3
   / \
  9  20
    /  \
   15   7
```

返回它的最大深度 3 。

---

【题解思路—DFS递归】

本题其实也要后序遍历（左右中），依然是因为要通过递归函数的返回值做计算树的高度。

按照递归三部曲，来看看如何来写。

确定递归函数的参数和返回值：参数就是传入树的根节点，返回就返回这棵树的深度，所以返回值为int类型。
确定终止条件：如果为空节点的话，就返回0，表示高度为0。
确定单层递归的逻辑：先求它的左子树的深度，再求的右子树的深度，最后取左右深度最大的数值 再+1 （加1是因为算上当前中间节点）就是目前节点为根节点的树的深度。

【题解代码—DFS递归】

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(root == NULL) return NULL;  //递归终止条件
        int left = maxDepth(root->left);  //左
        int right = maxDepth(root->right);  //右
        return max(left, right)+1;  
    }
};
```

