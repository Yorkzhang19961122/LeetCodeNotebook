【题目】

输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。

【示例】

```c++
前序遍历 preorder = [3,9,20,15,7]
中序遍历 inorder = [9,3,15,20,7]
```

返回如下的二叉树：

```c++
    3
   / \
  9  20
    /  \
   15   7
```

---

【题解思路—递归】

两个关键点：

* 前序遍历的列表：第一个元素永远是 【根节点 (root)】
* 中序遍历的列表：根节点 (root)【左边】的所有元素都在根节点的【左分支】，【右边】的所有元素都在根节点的【右分支】

算法思路：

1. 通过【前序遍历的列表】确定【根节点(root)】（利用第一个关键点）
2. 使用1中【确定的根节点(root)】将【中序遍历的列表】分割成【左分支】和【右分支】（利用第二个关键点）
3. 递归处理左右分支，寻找各自的根节点

【题解代码—递归】

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
    unordered_map<int, int> map;  
    vector<int> pre, in;
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        pre = preorder, in = inorder;
        for(int i = 0; i < inorder.size(); i++) {  //将中序遍历的节点值与其索引映射起来，方便后面查找根节点在中序遍历数组中的索引
            map[in[i]] = i;
        }
        return recur(0, 0, in.size() - 1);
    }

    TreeNode* recur(int root, int left, int right) {  //（根，左边界，右边界）
        if(left > right) return NULL;  //递归终止条件
        TreeNode* node = new TreeNode(pre[root]);  //确定重建树的节点node
        int index = map[pre[root]];  //index为中序遍历中根节点的索引，方便进行左右子树的划分
        //递归左子树的划分
        //左子树的根的索引为先序数组中的root+1  【根|左|右】
        //左子树的左边界为中序数组的left  【左|根|右】
        //左子树的右边界为中序的根节点索引-1  【左|根|右】
        node->left = recur(root + 1, left, index - 1);  
        //递归右子树的划分
        //右子树的根的索引为先序数组中 root+左子树的数量 + 1  【根|左|右】
        //右子树的左边界为中序数组的root+1 【左|根|右】
        //右子树的右边界为中序数组的right  【左|根|右】
        node->right = recur(root + (index - left) + 1, index + 1, right);  
        return node;
    }
};
```

