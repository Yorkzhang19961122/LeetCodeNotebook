【题目】

请实现两个函数，分别用来序列化和反序列化二叉树。

【示例】

```c++
你可以将以下二叉树：

    1
   / \
  2   3
     / \
    4   5

序列化为 "[1,2,3,null,null,4,5]"
```

---

【题解思路1—BFS】

* 序列化：对给定的树进行`BFS`（与常规的层序遍历不同，此处要将`null`节点也遍历出来，而非平时滤去`node->left/right`等于`null` 节点），将层序遍历的结果拼接上逗号后存储到结果`string`中

* 反序列化：
  1. 先对给定的字符串按照逗号进行拆分，存入`vector`中，方便我们使用
  2. 借助队列对上述`vector`进行遍历，`new`一个`root`节点作为树的根节点，不断遍历为其添加子节点，遍历完成后返回`root`即可

【题解代码1—BFS】

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
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res = "";
        if(root == NULL) return res;  //判空
        queue<TreeNode*> que;
        que.push(root);
        while(!que.empty()) {  //层序遍历
            TreeNode* node = que.front();
            que.pop();
            if(node == NULL) res += "NULL,";  //如果节点为空
            else {  //节点不为空
                res += to_string(node->val);
                res += ',';
                //无论node左右是否为空，都添加到队列中
                que.push(node->left);  
                que.push(node->right);
            }
        }
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data.size() == 0) return NULL;  //判空
        vector<string> temp1;
        int i = 0, j = 0;  //通过两个指针的移动，将data字符串按逗号进行切分
        while(i < data.size()) {
            if(data[i] != ',') {
                i++;
            }
            else {
                string temp2 = data.substr(j, i - j);
                temp1.push_back(temp2);
                i++;
                j = i;
            }
        }
        if(i != j) {  //处理最后一个有效子串
            string temp2 = data.substr(j, i - j);
            temp1.push_back(temp2);
        }

        TreeNode* root = new TreeNode(stoi(temp1[0]));  //new一个root节点，节点值为temp1的第一个值
        queue<TreeNode*> que;
        que.push(root);  
        i = 1;  //从temp1的第二个值开始遍历
        while(!que.empty()) {
            TreeNode* node = que.front();
            que.pop();
            if(temp1[i] != "NULL") {  //temp1对应的值非空
                node->left = new TreeNode(stoi(temp1[i])); //左子节点
                que.push(node->left);
            }
            i++;  //处理vector后一个元素
            if(temp1[i] != "NULL") {  //temp1对应的值非空
                node->right = new TreeNode(stoi(temp1[i]));  //右子节点
                que.push(node->right);
            }
            i++;  //向后处理
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
```

