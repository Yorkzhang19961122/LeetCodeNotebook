【题目】

输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。

【示例】

```c++
输入：head = [1,3,2]
输出：[2,3,1]
```

---

【我的思路—遍历】

正序遍历链表，将节点值存储在temp中，将temp中的值取出组成倒序的数组ans并返回

【我的代码—遍历】

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        ListNode* cur = head;
        vector<int> temp;
        while(cur != NULL){  //正序遍历链表，将节点值存储在temp中
            temp.push_back(cur->val);
            cur = cur->next;
        }
        int sz = temp.size();
        vector<int> ans;
        for(int i = sz-1; i >= 0; --i){  //将temp中的值取出组成倒序的数组ans并返回
            ans.push_back(temp[i]);
        }
        /*也可以使用reverse函数直接对temp进行反转
        reverse(temp.begin(), temp.end());
        return temp;
        */
        return ans;
    }
};
```

【题解思路—栈】

栈的特点是后进先出，即最后压入栈的元素最先弹出。考虑到栈的这一特点，使用栈将链表元素顺序倒置。从链表的头节点开始，依次将每个节点压入栈内，然后依次弹出栈内的元素并存储到数组中。

【题解代码—栈】

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        stack<int> S;
        ListNode* cur = head;
        while(cur != NULL){  //入栈
            S.push(cur->val);
            cur = cur->next;
        }
        vector<int> ans;
        while(!S.empty()){  //出栈
            ans.push_back(S.top());
            S.pop();
        }
        return ans;
    }
};
```

