【题目】

给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

【示例】

```c++
输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
     3
    /  \
  5      1
 / \    / \
6   2  0   8
   / \
  7   4
输出: 3
解释: 节点 5 和节点 1 的最近公共祖先是节点 3。
```

```c++
输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出: 5
解释: 节点 5 和节点 4 的最近公共祖先是节点 5。因为根据定义最近公共祖先节点可以为节点本身。
```

---

【题解思路1—递归】

递归终止条件：root 是否等于 p 或 q。若等于，直接返回 root

后序遍历二叉树，先去 root 的左子树找 p 或 q，再去 root 的右子树找 p 或 q，然后看左边和右边的寻找情况。

一共只有四种情况：左边没找到右边也没找到、左边找到了右边也找到了、左边没找到右边找到了、左边找到了右边没找到

* 左边没找到右边也没找到。说明题目给的二叉树根本不包含 p 或 q，返回 nullptr
* 左边找到了右边也找到了。说明 p 和 q 分居在 root 的两侧，那么最低公共祖先为 root，返回 root
* 左边没找到右边找到了。说明 p 和 q 全都在 root 的右侧，加上我们在第一步就知道 root 不等于 p 也不等于 q，所以最低公共祖先在 root 的右子树，返回右子树
* 左边找到了右边没找到。说明 p 和 q 全都在 root 的左侧，加上我们在第一步就知道 root 不等于 p 也不等于 q，所以最低公共祖先在 root 的左子树，返回左子树


【题解代码1—递归】

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
        if(!root || root == p || root == q) {  //递归终止条件
            return root;
        }

        TreeNode* leftTree = lowestCommonAncestor(root->left, p, q);
        TreeNode* rightTree = lowestCommonAncestor(root->right, p, q);

        if(!leftTree && !rightTree) return NULL;  //左右都没找到
        else if(!leftTree && rightTree) return rightTree;  //左边没找到，右边找到了
        else if(leftTree && !rightTree) return leftTree;  //左边找到了，右边没找到，返回左子树
        else return root;  //左右都找到了，root就是此时的公共祖先
    }
};
```

【题解思路2—前序遍历+链表最后公共节点】

前序遍历二叉树，分别存储从根节点到p和q的路径path1和path2，再找到两条路径的最后公共节点。

【题解思路2—前序遍历+链表最后公共节点】

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
        if(root == NULL || p == NULL || q == NULL) return NULL;
        list<TreeNode*> path1, path2;

        getNodePath(root, p, path1);
        getNodePath(root, q, path2);

        return getLastCommonNode(path1, path2);
    }
    //得到p，q的路径path1和path2(前序遍历)
    bool getNodePath(TreeNode* root, TreeNode* node, list<TreeNode*>& path) {  //注意传引用
        bool found = false;  //标志位
        path.push_back(root);  //将root加入到path中
        if(root == node) return true;  //找到目标节点，则返回true

        if(!found && root->left) found = getNodePath(root->left, node, path);  //左
        if(!found && root->right) found = getNodePath(root->right, node, path);  //右

        if(!found) {  //如果没有找到，则返回路径时，删除当前的节点
            path.pop_back();
        }
        return found;
    }
    //得到两个路径的最后共同节点
    TreeNode* getLastCommonNode(list<TreeNode*> path1, list<TreeNode*> path2) {
        TreeNode* pLast = NULL;  //pLast指向path1和path2最后的公共节点
        list<TreeNode*>::iterator it1 = path1.begin();  //定义两个迭代器分别指向两条路径的起点
        list<TreeNode*>::iterator it2 = path2.begin();

        while(it1 != path1.end() && it2 != path2.end()) {  //遍历两条路径
            if(*it1 == *it2) pLast = *it1;  //更新最后的公共节点（解引用后才能得到it1指向的内容<treenode*>）
            it1++;
            it2++;
        }
        return pLast;  //返回公共节点
    }
};
```

