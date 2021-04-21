【题目】

从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。

【示例】

给定二叉树: `[3,9,20,null,null,15,7]`,

```c++
    3
   / \
  9  20
    /  \
   15   7
```

返回：

```c++
[3,9,20,15,7]
```

---

【我的思路—层序遍历BFS】

常规的层序遍历题

【我的代码—层序遍历BFS】

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
    vector<int> levelOrder(TreeNode* root) {
        vector<int> res;
        if(root == NULL) return res; 
        queue<TreeNode*> que;
        que.push(root);
        while(!que.empty()) {
            int size = que.size();
            for(int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                res.push_back(node->val);
                if(node->left) que.push(node->left);
                if(node->right) que.push(node->right);
            }
        }
        return res;
    }
};
```

