【题目】

给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

【示例】

```c++
输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
      6
    /  \
  2     8
 /  \  /  \
0   4 7   9
   / \
  3   5
输出: 6 
解释: 节点 2 和节点 8 的最近公共祖先是 6。
```

---

【题解思路1—迭代】

① 树为 二叉搜索树 ，② 树的所有节点的值都是 唯一 的。根据以上条件，可方便地判断 p,q 与 root 的子树关系，即：

* 若 root.val < p.val ，则 p 在 root 右子树 中；
* 若 root.val > p.val ，则 p 在 root 左子树 中；
* 若 root.val = p.val，则 p 和 root 指向 同一节点 。

循环搜索：当节点root为空时跳出

* 当p、q都在root的左子树中，则遍历至root.left

* 当p、q都在root的右子树中，则遍历至root.right

* 否则说民找到了最近的公共祖先，跳出

返回最近的公共祖先root

【题解代码1—迭代】

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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        while(root != NULL) {  //遍历
            if(root->val > p->val && root->val > q->val) {  //根据二叉搜索树的性质，假如pq节点的值都小于root的值，则说明pq都在root的左边，则root更新为左边的子树
                root = root->left;
            }
            else if(root->val < p->val && root->val < q->val) {  //同理
                root = root->right;
            }
            else break;  //pq节点分布在root的左右两侧，则说明此时的root就为最近的公共祖先
        }
        return root;
    }
};
```

【题解思路2—递归】

* 当 p, q 都在 root 的 右子树 中，则开启递归 root.right 并返回；
* 否则，当 p, q 都在 root 的 左子树 中，则开启递归 root.left 并返回；
* 返回最近公共祖先root

【题解代码2—递归】

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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == NULL) return NULL;
        if(root->val < p->val && root->val < q->val) {  //当p, q都在root的右子树中，则开启递归root.right并返回
            return lowestCommonAncestor(root->right, p, q);
        }
        if(root->val > p->val && root->val > q->val) {  //否则，当p,q都在root的左子树中，则开启递归root.left并返回
            return lowestCommonAncestor(root->left, p, q);
        }
        return root;
    }
};
```

