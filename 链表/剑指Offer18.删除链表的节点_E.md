【题目】

给定单向链表的头指针和一个要删除的节点的值，定义一个函数删除该节点。

返回删除后的链表的头节点。

【示例】

```c++
输入: head = [4,5,1,9], val = 5
输出: [4,1,9]
解释: 给定你链表中值为 5 的第二个节点，那么在调用了你的函数之后，该链表应变为 4 -> 1 -> 9.
```

---

【我的思路—虚拟头节点】

定义一个虚拟头节点dummy指向链表的头head，然后定义一个cur作为前驱节点，借助它遍历整个链表，发现值相同的节点时，修改cur->next指向cur->next->next，最终返回dummy->next即可

【我的代码—虚拟头节点】

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
    ListNode* deleteNode(ListNode* head, int val) {
        ListNode* dummy = new ListNode(-1);  //创建虚拟头节点
        dummy->next = head;  //指向head
        ListNode* cur = dummy;  //cur为前驱节点，从dummy开始

        while(cur!= NULL && cur->next != NULL){  //借助前驱节点cur遍历历链表
            if(cur->next->val == val){  //如果相等
                cur->next = cur->next->next;   //调整指向
            }
            cur = cur->next;  //cur后移
        }
        return dummy->next;  //返回头节点
    }
};
```

