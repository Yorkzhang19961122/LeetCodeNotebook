【题目】

输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)

B是A的子结构， 即 A中有出现和B相同的结构和节点值。

例如:
给定的树 A:

```
    3
   / \
  4   5
 / \
1   2
```

给定的树 B：

```
  4 
 /
 1
```

返回 true，因为 B 与 A 的一个子树拥有相同的结构和节点值。

【示例】

```c++
输入：A = [1,2,3], B = [3,1]
输出：false
```

```c++
输入：A = [3,4,5,1,2], B = [4,1]
输出：true
```

---

【题解思路—BFS】



【题解代码—BFS】

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

    bool helper(TreeNode* A, TreeNode* B) {
        //初始化两个队列分别存放此时A树与B树相同的节点
        queue<TreeNode*> que1;
        queue<TreeNode*> que2;
        que1.push(A);
        que2.push(B);
        while(!que2.empty()) {  //按照B的形状与A进行比较（因为要判断B是）
            TreeNode* temp1 = que1.front();
            que1.pop();
            TreeNode* temp2 = que2.front();
            que2.pop();
            if(temp1->val != temp2->val) return false;
            if(temp2->left) {
                que1.push(temp1->left);
                que2.push(temp2->left);
            } 
            if(temp2->right) {
                que1.push(temp1->right);
                que2.push(temp2->right);
            }
        }
        return false;
    }
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if(A == NULL || B == NULL) return false;  //A或B为空的情况
        queue<TreeNode*> que;
        que.push(A);
        bool res = false;
        while(!que.empty()) {  //二叉树的层序遍历
            int size = que.size();
            for(int i = 0; i < size; i++) {  //遍历当前层
                TreeNode* temp = que.front();
                que.pop();
                if(temp->val == B->val) {  //如果当前节点值和B树头节点值相同
                    if(helper(temp, B)) {  //开始借助helper函数判断B树是否为A树的子结构
                        return true;  //如果判断成功，则返回true
                    }  
                }
                //否则就继续遍历树A寻找下一个相同节点
                if(temp->left) que.push(temp->left);  //继续层序遍历，将A当前节点的left加入队列
                if(temp->right) que.push(temp->right);  //将A当前节点的right加入队列
            }
        }
        return false;  //树A全部遍历完仍未返回过true，则说明B不是A的子结构，返回false
    }
};
```

