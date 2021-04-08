【题目】

从上到下按层打印二叉树，同一层的节点按从左到右的顺序打印，每一层打印到一行。

【示例】

给定二叉树: `[3,9,20,null,null,15,7]`,

```c++
    3
   / \
  9  20
    /  \
   15   7
```

返回其层次遍历结果：

```c++
[
  [3],
  [9,20],
  [15,7]
]
```

---

【我的思路—二叉树的层序遍历】

层序遍历的模板题

【我的代码—二叉树的层序遍历】

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(!root) return res;  //特殊情况排除
        queue<struct TreeNode*> q;  //队列用来存储每层的节点
        q.push(root);
        while(!q.empty()) {  
            int size = q.size();  //size为每层的节点数量
            vector<int> temp;  //temp用来存储每层的节点值
            for(int i = 0; i < size; i++) {  //遍历每层
                struct TreeNode* node = q.front();
                q.pop();
                temp.push_back(node->val);
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            res.push_back(temp);  //将每层添加到res中
        }
        return res;
    }
};
```

