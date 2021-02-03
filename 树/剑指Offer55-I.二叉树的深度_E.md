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

【题解思路1—DFS递归】

本题其实也要后序遍历（左右中），依然是因为要通过递归函数的返回值做计算树的高度。

按照递归三部曲，来看看如何来写。

确定递归函数的参数和返回值：参数就是传入树的根节点，返回就返回这棵树的深度，所以返回值为int类型。
确定终止条件：如果为空节点的话，就返回0，表示高度为0。
确定单层递归的逻辑：先求它的左子树的深度，再求的右子树的深度，最后取左右深度最大的数值 再+1 （加1是因为算上当前中间节点）就是目前节点为根节点的树的深度。

【题解代码1—DFS递归】

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

【题解思路2—BFS层序遍历】

对二叉树进行层序遍历，设置cnt为层数的标志位，每遍历一层cnt++，最终的cnt即为二叉树的最大深度。

【题解代码2—BFS层序遍历】

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
        queue<TreeNode*> que;
        if(root != NULL) que.push(root);
        vector<vector<int>> res;
        int cnt = 0;
        while(!que.empty()){  //当队列que非空时
            int size = que.size();  //size存放当前队列que的大小
            vector<int> vec;  //vec用来存放树的一层
            for(int i = 0; i < size; ++i){  //遍历树的一层
                TreeNode* node = que.front();  //node存放队列最前面的节点
                que.pop();  //删除que最前的节点
                vec.push_back(node->val);  //将一层中的节点值存放到vec数组中
                //将下一层的节点放到队列que中
                if(node->left) que.push(node->left);  
                if(node->right) que.push(node->right);
            }
            ++cnt;
        }
        return cnt;
    }
};
```



【TIPS】

**二叉树层序遍历模板**：

```c++
/*给定二叉树，返回二叉树经过层序遍历后得到的二维数组*/
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> que;
        if(root != NULL) que.push(root);
        vector<vector<int>> res;
        while(!que.empty()){  //当队列que非空时
            int size = que.size();  //size存放当前队列que的大小
            vector<int> vec;  //vec用来存放树的一层
            for(int i = 0; i < size; ++i){  //遍历树的一层
                TreeNode* node = que.front();  //node存放队列最前面的节点
                que.pop();  //删除que最前的节点
                vec.push_back(node->val);  //将一层中的节点值存放到vec数组中
                //将下一层的节点放到队列que中
                if(node->left) que.push(node->left);  
                if(node->right) que.push(node->right);
            }
            res.push_back(vec);  //一层循环结束后，将vec存放到res中
        }
        return res;
    }
};
```

