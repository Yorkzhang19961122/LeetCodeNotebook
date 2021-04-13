【题目】

输入一棵二叉树的根节点，判断该树是不是平衡二叉树。如果某二叉树中任意节点的左右子树的深度相差不超过1，那么它就是一棵平衡二叉树。

【示例】

给定二叉树 `[3,9,20,null,null,15,7]`

```c++
    3
   / \
  9  20
    /  \
   15   7
```

返回true

---

【题解思路1—至上而下+前序遍历】

要验证一颗二叉树是否为平衡二叉树，只需要它的左子树是平衡二叉树，右子树是平衡二叉树，并且左右子树的深度差小于 2。

* 创建计算树深度的函数（depth）
  * 检测传入的树
    * 如果为空，返回0
    * 如果不为空，递归调用深度计算函数，分别计算左右子树的深度，将左右两个深度中的最大值+1作为结果返回
* 创建判断平衡的函数（isBalanced）
  * 使用深度计算函数（depth）计算左右子树的深度
  * 递归调用平衡判断函数（isBalanced）判断左右子树是否平衡
  * 判断深度差是否小于2，且左右子树都平衡，则返回true
  * 否则返回false

【题解代码1—至上而下+前序遍历】

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
	//判断平衡函数
    bool isBalanced(TreeNode* root) {
        if(root == NULL) return true;
        //判断左子树和右子树的深度差，以及左右子树是否平衡
        return abs(depth(root->left) - depth(root->right)) <= 1 && isBalanced(root->left) && isBalanced(root->right);
    }
	//计算深度的函数
    int depth(TreeNode* node) {
        if(node == NULL) return 0;
        int left = depth(node->left);
        int right = depth(node->right);
        //取左右子树中深度比较大的值作为返回结果
        return max(left, right) + 1;
    }
};
```

【题解思路2—至下而上+后序遍历】

* 递归函数
  * 当节点root左右子树的深度差<=1，则返回当前子树的深度，即节点root左右子树的深度最大值+1
  * 当节点root左右子树的深度差>2，则返回-1，代表此子树是不平衡树
  * 当root为空，说明越过叶子节点，返回高度0
  * 当左右子树的深度为-1，代表此树的左右子树不是平衡树，因此剪枝，直接返回-1
* isBalanced(root)函数
  * 若recur(root) 不等于-1，则说明此树平衡，返回true，否则返回false

【题解代码2—至下而上+后序遍历】

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

    int recur(TreeNode* root) {
        if(root == NULL) return 0;
        int left = recur(root->left);
        if(left == -1) return -1;  //剪枝
        int right = recur(root->right);
        if(right == -1) return -1;  //剪枝
        return abs(left - right) < 2 ? max(left, right) + 1 : -1;
    }
    bool isBalanced(TreeNode* root) {
        return recur(root) == -1 ? false : true; 
    }
};
```

