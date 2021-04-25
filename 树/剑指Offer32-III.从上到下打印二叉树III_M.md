【题目】

请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行以此类推。

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
  [20,9],
  [15,7]
]
```

---

【我的思路—BFS】

层次遍历二叉树，与常规的层次遍历不同，本题使用双端队列`deque`来存储二叉树每层的节点（借助一个标志位`order`来确定本层需要从左到右还是从右到左）：

* 对于奇数层（`order=true`），将此时队列中的节点从`front`开始读出（达到从左到右），同时将当前节点的子节点按照左右的顺序从back放入队列中，再将标志位`order`取反
* 对于偶数层（`order=false`），将此时队列中的节点从`back`读出（达到从右到左），同时将当前节点的子节点按照右左的顺序从front存入队列中，再将标志位`order`取反

【我的代码—BFS】

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
        if(root == NULL) return res;  //空树特殊处理
        deque<TreeNode*> dque;  //初始化双端队列dque
        dque.push_back(root);
        bool order = true;  //初始化标志位order: order=true:从左到右, order=false:从右到左
        while(!dque.empty()) {  //遍历队列
            int size = dque.size();
            if(order) {  //奇数层
                vector<int> layer;
                for(int i = 0; i < size; i++) {
                    //从左向右打印
                    TreeNode* node = dque.front(); 
                    dque.pop_front();
                    layer.push_back(node->val);
                    //先左后右加入下层节点
                    if(node->left) dque.push_back(node->left);  //将当前节点的左子节点从队列尾存入
                    if(node->right) dque.push_back(node->right);  //将当前节点的右子节点从队列尾存入
                }
                res.push_back(layer);
                order = !order;
            }
            else {  //偶数层
                vector<int> layer;
                for(int i = 0; i < size; i++) {
                    //从右向左打印
                    TreeNode* node = dque.back();
                    dque.pop_back();
                    layer.push_back(node->val);
                    //先右后左加入下层节点
                    if(node->right) dque.push_front(node->right);
                    if(node->left) dque.push_front(node->left);
                }
                res.push_back(layer);  //处理完一层后将其加入res中
                order = !order;
            }
        }
        return res;
    }
};
```

代码优化，可以省略标志位，当一层处理结束后，下一层自然就需要反过来，**注意下面的代码有一个trick：可以使用`for(int i = dque.size(); i > 0; i--) `来代替创建的`size`变量**：

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
        if(root == NULL) return res;  //空树特殊处理
        deque<TreeNode*> dque;  //初始化双端队列dque
        dque.push_back(root);
        while(!dque.empty()) {  //遍历队列
            //奇数层，从左向右打印
            vector<int> layer;
            //此处for循环改为for(int i = dque.size(); i > 0; i--)可以不需要创建size变量，节省空间，把dque.size()作为初值是因为它在运行中是动态改变的，下面层也可以使用同样的做法
            int size = dque.size();
            for(int i = 0; i < dque.size(); i++) {
                TreeNode* node = dque.front();
                dque.pop_front();
                layer.push_back(node->val);
                //先左后右加入下层节点
                if(node->left) dque.push_back(node->left); 
                if(node->right) dque.push_back(node->right);  
            }
            res.push_back(layer);  //处理完一层后将其加入res中

            if(dque.empty()) break;
            //偶数层，从右向左打印
            layer.clear();
            size = dque.size();
            for(int i = 0; i < dque.size(); i++) {
                TreeNode* node = dque.back();
                dque.pop_back();
                layer.push_back(node->val);
                //先右后左加入下层节点
                if(node->right) dque.push_front(node->right);
                if(node->left) dque.push_front(node->left);
            }
            res.push_back(layer);  //处理完一层后将其加入res中            
        }
        
        return res;
    }
};
```

【题解思路1—reverse函数反转】

先对二叉树进行正常的层序遍历，在将`layer`加入`res`时判断该层为奇或偶，如果为偶则直接加入`res`，如果为奇则倒序后加入`res`

【题解代码1—reverse函数反转】

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
        if(root == NULL) return res;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            vector<int> layer;
            for(int i = q.size(); i > 0; i--) {  //正常的层序遍历
                TreeNode* node = q.front();
                q.pop();
                layer.push_back(node->val);
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            //在res二维数组中进行奇偶层数的判定
            if(res.size() % 2 == 0) res.push_back(layer);  //偶数层，直接将layer加入res
            else {
                reverse(layer.begin(), layer.end());  //奇数层，reverse layer后加入res
                res.push_back(layer);
            }
        }
        return res;
    }
};
```

【题解思路2—BFS借助list】

借助`list`数据结构来存储每层的节点值，list允许从头部插入数据，因此可以达到偶数层的时候从尾部插入，奇数层的时候从头部插入，

而不用对二叉树的层序遍历进行过多的修改。

【题解代码2—BFS借助list】

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
        if(root == NULL) return res;
        deque<TreeNode*> dque;
        dque.push_back(root);
        while(!dque.empty()) {
            list<int> layer;  //利用list来存储每层的节点值
            for(int i = dque.size(); i > 0; i--) {  
                TreeNode* node = dque.front();
                dque.pop_front();
                if(res.size() % 2 == 0) {  //偶数层
                    layer.push_back(node->val);
                }
                else {  //奇数层
                    layer.push_front(node->val);
                }
                if(node->left) dque.push_back(node->left);
                if(node->right) dque.push_back(node->right);
            }
            vector<int> temp(layer.begin(), layer.end());  //用list类型的layer来初始化vector
            res.push_back(temp);
        }
        return res;
    }
};
```

