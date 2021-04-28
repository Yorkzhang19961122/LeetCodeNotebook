【题目】

输入一棵二叉树和一个整数，打印出二叉树中节点值的和为输入整数的所有路径。从树的根节点开始往下一直到叶节点所经过的节点形成一条路径。

【示例】

给定如下二叉树，以及目标和 `target = 22`，

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1

返回

```
[
   [5,4,11,2],
   [5,8,4,5]
]
```

---

【我的思路—递归加路径求和】

联想到[二叉树的所有路径](https://github.com/Yorkzhang19961122/LeetCodeNotebook/blob/main/%E6%A0%91/257.%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E6%89%80%E6%9C%89%E8%B7%AF%E5%BE%84_E.md)，最直观暴力的方法就是对二叉树进行前序遍历，并保存二叉树所有的路径，然后再遍历路径，计算每条路径的和，如果等于target，就将此条路径加入到ans中，遍历完毕返回ans即可。

【我的代码—递归加路径求和】

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> paths;  //paths存储所有路径
    void dfs(TreeNode* root, vector<int> path) {  //注意path不能传引用（需要每次都执行path的拷贝），否则达不到回溯的效果
        if(root == nullptr) {  //递归终止条件
            return;
        }
        path.push_back(root->val);  //将当前节点的值加到当前路径path中
        if(root->left == nullptr && root->right == nullptr) {  //如果当前节点是叶子节点
            paths.push_back(path);  //将此时的路径path添加到path中
            return;  //回溯
        }
        dfs(root->left,path);  //递归处理当前节点的左孩子
        dfs(root->right, path);  //处理右孩子
    }
    vector<vector<int>> pathSum(TreeNode* root, int target) {
        vector<vector<int>> ans;  //ans用于存储最终的结果
        vector<int> path;  //path用于存储每一条路径
        dfs(root, path);  //开启递归
        for(auto vec : paths) {  //递归结束后遍历paths并计算其中每条路径的和sum
            int sum = 0;
            for(auto num : vec) {
                sum += num;
            }
            if(sum == target) {  //如果和sum等于target，将此时的路径加入ans中
                ans.push_back(vec);
            }
        }
        return ans;
    }
};
```

以上的代码非常粗暴，没有任何优化，下面对代码进行优化：

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> paths;  //paths存储所有路径
    void dfs(TreeNode* root, vector<int> path, int target) {  //注意dfs仍然传入了path，通过递归帮我们进行回溯
        if(root == nullptr) {  //递归终止条件
            return;
        }
        path.push_back(root->val); 
        target -= root->val;  //每次使用target减去当前节点的值
        //如果在当前节点，target被减为0且当前节点是叶子节点  
        if(target == 0 && root->left == nullptr && root->right == nullptr) {  
            paths.push_back(path);  //将当前的路径path添加到paths中
            return;  
        }
        dfs(root->left, path, target);  //递归处理当前节点的左孩子
        dfs(root->right, path, target);  //处理右孩子
    }
    vector<vector<int>> pathSum(TreeNode* root, int target) {
        vector<int> path;  //path用于存储每一条路径
        dfs(root, path, target);  //开启递归
        
        return paths;
    }
};
```

【题解思路—前序遍历+递归回溯】

前序遍历来提取二叉树中的所有路径，同时计算路径的和是否为target，注意此解法我们手动对路径`path`进行恢复，达到回溯的效果，而target则借助递归来回溯。

【题解代码—前序遍历+递归回溯】

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> paths;  //paths存储所有路径
    vector<int> path;
    void dfs(TreeNode* root, int target) {  
        if(root == nullptr) {  //递归终止条件
            return;
        }
        path.push_back(root->val); 
        target -= root->val;  //每次使用target减去当前节点的值
        //注意这里我们不把path带入递归函数中，而是选择手动进行pop_back来达到回溯，而target是传的引用，可以利用递归进行回溯
        if(target == 0 && root->left == nullptr && root->right == nullptr) {  //如果在当前节点时，target被减为0且当前节点是叶子节点  
            paths.push_back(path);  //将当前的路径path添加到paths中
        }
        dfs(root->left, target);  //递归处理当前节点的左孩子
        dfs(root->right, target);  //递归右孩子
        path.pop_back();  //路径恢复
    }
    vector<vector<int>> pathSum(TreeNode* root, int target) {
        vector<int> path;  //path用于存储每一条路径
        dfs(root, target);  //开启递归
        
        return paths;
    }
};
```

