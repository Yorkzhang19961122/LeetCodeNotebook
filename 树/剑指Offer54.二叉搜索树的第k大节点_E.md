【题目】

给定一棵二叉搜索树，请找出其中第k大的节点。

【示例】

```c++
输入: root = [3,1,4,null,2], k = 1
   3
  / \
 1   4
  \
   2
输出: 4
```

---

【我的思路—中序遍历】

考虑到是二叉搜索树，中序遍历后将由小到大的节点值保存到数组中，然后按照题意返回第k大的值即可

【我的代码—中序遍历】

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
    void recursion(TreeNode* node, vector<int>& tree_vec){
        //二叉搜索树中序遍历后就会得到一个由小到大的数组
        if(node == NULL) return;
        recursion(node->left, tree_vec);  //左
        tree_vec.push_back(node->val);  //中
        recursion(node->right, tree_vec);  //右
    }
    int kthLargest(TreeNode* root, int k) {
        vector<int> tree_vec;
        recursion(root, tree_vec);
        return tree_vec[tree_vec.size() - k];  //返回第k大的节点值
    }
};
```

考虑到搜索树的特性，代码的空间复杂度可以由O(n)简化为O(1):

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
    int ans = 0, count = 0;
    void recursion(TreeNode* node, int k){
        //按照右中左的顺序进行中序遍历，并且使用count作计数，等于k时返回此时的节点值
        if(node == NULL) return;
        recursion(node->right, k);  //右
        count++;  //中
        if(count == k){
            ans = node->val;
            return;
        }
        recursion(node->left, k);  //左
    }
    int kthLargest(TreeNode* root, int k) {
        recursion(root, k);
        return ans;  //返回第k大的节点值
    }
};
```

【二刷】由于二叉搜索树的特性，中序遍历可以得到升序或降序的结果（取决于左中右还是右中左），因此本题只需要右中左得到降序排列的二叉搜索树节点值，并对每次递归进行计数，最后返回第k次时的节点值即可。
