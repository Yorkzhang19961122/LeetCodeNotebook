【题目】

输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的循环双向链表。要求不能创建任何新的节点，只能调整树中节点指针的指向。

特别地，我们希望可以就地完成转换操作。当转化完成以后，树中节点的左指针需要指向前驱，树中节点的右指针需要指向后继。还需要返回链表中的第一个节点的指针。

【示例】

以下面的二叉搜索树为例：

```c++
       4
     /  \
    2    5
  /  \
 1    3
```

我们希望将这个二叉搜索树转化为双向循环链表。链表中的每个节点都有一个前驱和后继指针。对于双向循环链表，第一个节点的前驱是最后一个节点，最后一个节点的后继是第一个节点。

下图展示了上面的二叉搜索树转化成的链表。“head” 表示指向链表中有最小元素的节点。

![185943](G:\LeetCode\LeetCodeNotebook\剑指Offer\剑指Offer36.二叉搜索树与双向链表\185943.jpg)

【题解思路1—中序遍历+额外存储空间】

最原始暴力的方法，首先对二叉搜索树进行中序遍历，得到的结果存储在额外的vector中，再通过两次循环将vector中各节点的指向按照双向链表的要求进行处理，最后对首尾节点的指向进行处理

【题解代码1—中序遍历+额外存储空间】

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
public:

    Node* treeToDoublyList(Node* root) {
        if(root == NULL) return NULL;
        vector<Node*> vec;
        inorder(root, vec);
        for(int i = 0; i < vec.size() - 1; i++) {  //第一次循环，确定各节点的右指针指向
            vec[i]->right = vec[i + 1];
        }
        for(int i = vec.size() - 1; i > 0; i--) {  //第二次循环，确定各节点的左指针指向
            vec[i]->left = vec[i - 1];
        }
        vec[0]->left = vec[vec.size() - 1];  //处理首尾节点的指向
        vec[vec.size() - 1]->right = vec[0];
        Node* head = vec[0];
        return head;  //返回头节点
    }

    void inorder(Node* node, vector<Node*>& vec) {  //对二叉搜索树进行中序遍历，存入vector中
        if(node == NULL) return;
        inorder(node->left, vec);
        vec.push_back(node);
        inorder(node->right, vec);
    }
};
```

【[题解思路2—原地中序遍历](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-yu-shuang-xiang-lian-biao-lcof/solution/shu-ju-jie-gou-he-suan-fa-3chong-shi-xia-bucn/)】

首先对二叉搜索树进行中序遍历，但不借助额外的空间，在遍历的同时构造双向链表

【题解代码2—原地中序遍历】

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if(root == NULL) return NULL;  //特殊情况处理
        inorder(root);  //开始递归
        head->left = pre;  //递归结束后，将head与在末尾的pre的指向按照题意设置
        pre->right = head;
        return head;
    }
    Node* head, *pre;  //维护head和指向前一个处理的pre指针
    void inorder(Node* node) {  //中序遍历二叉搜索树
        if(node == NULL) return;  
        inorder(node->left);  //左
        if(pre == NULL) {  //处理当前节点
            head = node;  //判断其是否为双向链表的头节点
        }
        else {  //如若不是，将pre的右指针指向当前的节点node
            pre->right = node;
        }
        node->left = pre;  //同样，将node的左指针指向pre，实现双向
        pre = node;  //更新pre，指向当前的节点node，为接下来的处理做准备
        inorder(node->right);  //右
    }
};
```

对于一般的二叉树递归操作，我们可以使用栈进行模拟：（手推一遍此代码有利于加深对递归的理解）

```c++
/*使用栈模拟递归，按顺序输出二叉树的中序遍历结果*/
void inorder(Node* root) {
    if(root == NULL) return NULL;
    stack<Node*> stk;  //辅助栈，用于保护现场
    Node* p = root;
    while(p != NULL || !stk.empty()) {
        while(p != NULL) {
            stk.push(p);
            p = p -> left;
        }
        if(!stk.empty()) {
            p = stk.top();  //恢复现场
            stk.pop();
            cout << p->val << endl;
            p = p->right;
        }
    }
}
```

针对此题，用栈的方法可以写做如下：

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if(root == NULL) return root;
        stack<Node*> stk;
        Node* p = root;
        Node* head = NULL, *pre = NULL;
        while(p != NULL || !stk.empty()) {
            while(p != NULL) {
                stk.push(p);
                p = p->left;  //左
            }
            if(!stk.empty()) {
                p = stk.top();
                stk.pop();
                if(pre == NULL) {  //中
                    head = p;
                }
                else {
                    pre->right = p;
                }
                p->left = pre;
                pre = p;
                p = p->right; //右
            }
        }
        head->left = pre;  //连接首尾
        pre->right = head;
        return head;
    }
};
```

