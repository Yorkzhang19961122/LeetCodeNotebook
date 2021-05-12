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

【[题解思路—BFS](https://leetcode-cn.com/problems/shu-de-zi-jie-gou-lcof/solution/jian-zhi-offer-26-shu-de-zi-jie-gou-die-0qjeh/)】

**总体思路**

* 先遍历树`A`，如果遍历到和`B`节点值相同的节点，进入`helper`方法判断接下来的节点是否都相同
* 节点都相同返回`True`；不相同返回`False`，并且继续遍历树`A`找下一个相同的节点
* 如果遍历完了`A`还没有返回过`True`，说明`B`不是`A`的子结构，返回`False`

**helper函数（用于判断A的子树是否有和B相同的部分）**

* 正常`BFS`步骤，用队列存储树`A`和`B`相对应的节点`temp1`, `temp2`
* 因为入队的条件是只要树`B`节点存在就入队，如果A已经没有了相应节点返回`False`：`if(temp1 == NULL)`
* 如果`A`和`B`对应节点值不相同也返回`False`：`if(temp1->val != temp2->val)`
* 如果遍历完了`B`也没有返回过`False`，说明`B`是`A`的子结构，返回`True`

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
        /*helper函数用于判断B树是否为以A为根节点的树的子结构，所以遍历传入的B树*/
        //和BFS一样，首先用队列存储A和B的节点
        queue<TreeNode*> que1;
        queue<TreeNode*> que2;
        que1.push(A);
        que2.push(B);
        while(!que2.empty()) {  //按照B的形状判断其是否为A的子结构（BFS遍历传入的B树）
            TreeNode* temp1 = que1.front();  //temp1暂存A的节点
            que1.pop();
            TreeNode* temp2 = que2.front();  //temp2暂存B的节点
            que2.pop();
            if(temp1 == NULL || temp1->val != temp2->val) {  //如果B节点存在(!que2.empty())而A节点为空，或者A与B节点的值不同
                return false;  //说明B不是A的子结构，返回false
            }
            //遍历B的下一层，同时A跟进
            if(temp2->left) {  //如果B存在左节点
                //将B的左节点入队，同时跟进A，准备比较其值是否相同
                que1.push(temp1->left);  
                que2.push(temp2->left);
            }
            if(temp2->right) {  //如果B存在右节点
                //将B的右节点入队，同时跟进A，准备比较其值是否相同
                que1.push(temp1->right);
                que2.push(temp2->right);
            }
        }
        return true;  //遍历完B仍未返回false，说明B是A的子结构，返回true
    }
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if(A == NULL || B == NULL) return false;  //A或B为空的情况
        queue<TreeNode*> que;  //初始化队列用于层序遍历A树
        que.push(A);
        while(!que.empty()) {
            int size = que.size();  
            for(int i = 0; i < size; i++) {  //循环遍历当前层
                TreeNode* temp = que.front();  //取出当前待处理的节点
                que.pop();
                if(temp->val == B->val) {  //如果当前节点值和B树头节点相同
                    if(helper(temp, B)) {  //借助helper函数判断B是否为A的子结构
                        return true;   //如果判断成功，返回true
                    } 
                }
                //否则就继续遍历树A余下的节点，找是否还有和B头节点相同的节点
                if(temp->left) que.push(temp->left);  //继续层序遍历，将A当前节点的left加入队列
                if(temp->right) que.push(temp->right);  //将A当前节点的right加入队列
            }
        }
        return false;  //树A全部遍历完仍未返回过true，则说明B不是A的子结构，返回false
    }
};
```

以上方法在`isSubStructure`和`helper`函数中都使用了BFS，实际上在helper中可以考虑使用DFS来减少空间占用：

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
    bool helper(TreeNode* nodeA, TreeNode* nodeB) {
        if(nodeB == NULL) return true;  //如果B为空，说明B已经遍历完成而未返回false，则B是A的子结构
        if(nodeA == NULL || nodeA->val != nodeB->val) {  //若A节点为空或者A与B节点的值不同
            return false;  //B不是A的子结构
        }
        return helper(nodeA->left, nodeB->left) && helper(nodeA->right, nodeB->right);  //返回递归处理A与B的左子节点和右子节点的结果
    }
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if(A == NULL || B == NULL) return false;  //A或B为空的情况
        queue<TreeNode*> que;  //初始化队列用于层序遍历A树
        que.push(A);
        while(!que.empty()) {
            int size = que.size();  
            for(int i = 0; i < size; i++) {  //循环遍历当前层
                TreeNode* temp = que.front();  //取出当前待处理的节点
                que.pop();
                if(temp->val == B->val) {  //如果当前节点值和B树头节点相同
                    if(helper(temp, B)) {  //借助helper函数判断B是否为A的子结构
                        return true;   //如果判断成功，返回true
                    } 
                }
                //否则就继续遍历树A余下的节点，找是否还有和B头节点相同的节点
                if(temp->left) que.push(temp->left);  //继续层序遍历，将A当前节点的left加入队列
                if(temp->right) que.push(temp->right);  //将A当前节点的right加入队列
            }
        }
        return false;  //树A全部遍历完仍未返回过true，则说明B不是A的子结构，返回false
    }
};
```

【[题解思路2—DFS](https://leetcode-cn.com/problems/shu-de-zi-jie-gou-lcof/solution/di-gui-fang-shi-jie-jue-by-sdwwld/)】

要判断`B`是否是`A`的子结构，我们只需要从根节点开始判断，通过递归的方式比较他的每一个子节点即可，但实际上`B`如果是`A`的子结构的话，不一定是从根节点开始的，也可能是在`A`的左或右子树中，所以如果从根节点判断`B`不是`A`的子结构，还要继续判断`B`是不是`A`左子树的子结构和右子树的子结构

【题解代码2—DFS】

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
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if(A == NULL || B == NULL) return false;  //边界条件判断
        //dfs(A, B):先从根节点进行判断B是不是A的子结构
        //如果不是再分别从左右两个子树进行判断
        //只要有一个为true，则说明B是A的子结构
        return dfs(A, B) || isSubStructure(A->left, B) || isSubStructure(A->right, B); 
    }
    bool dfs(TreeNode* A, TreeNode* B) {
        if(B == NULL) return true;  //这里如果B为空，说明B已经访问完了，确定是A的子结构
        //如果B不为空A为空，或者这两个节点值不同，说明B树不是
        //A的子结构，直接返回false
        if(A == NULL || A->val != B->val) {
            return false;
        }
        //当前节点比较完之后还要继续判断左右子节点
        return dfs(A->left, B->left) && dfs(A->right, B->right);
    }
};
```

