【题目】

定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。

【示例】

```c++
输入: 1->2->3->4->5->NULL
输出: 5->4->3->2->1->NULL
```

---

【题解思路1—双指针】

* 定义两个指针： pre和 cur；pre在前 cur在后。
* 每次让 pre的 next指向 cur，实现一次局部反转
* 局部反转完成之后， pre和 cur同时往前移动一个位置
* 循环上述过程，直至 pre到达链表尾部

【题解代码1—双指针】

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
    ListNode* reverseList(ListNode* head) {
        ListNode* cur = NULL, *pre = head;  //定义两个指针cur和pre
        while(pre != NULL){  //遍历链表，直到链表尾
            ListNode* temp = pre->next;  //将pre后一个节点存储在temp中，防止“失联”
            pre->next = cur;  //局部反转
            cur = pre;  //cur向前移
            pre = temp;  //pre向前移
        }
        return cur;  //返回的cur即为反转后的链表
    }
};
```

【题解思路2—递归】

考虑使用递归法遍历链表，当越过尾节点后终止递归，在回溯时修改各节点的 next 引用指向。

（1）recur(cur, pre) 递归函数：

* 终止条件：当 cur 为空，则返回尾节点 pre （即反转链表的头节点）；

* 递归后继节点，记录返回值（即反转链表的头节点）为 res ；

* 修改当前节点 cur 引用指向前驱节点 pre ；

* 返回反转链表的头节点 res ；

（2）reverseList(head) 函数：
调用并返回 recur(head, null) 。传入 null 是因为反转链表后， head 节点指向 null 

【题解代码2—递归】

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
    ListNode* reverseList(ListNode* head) {
        return recur(head, nullptr);  //调用递归并返回
    }
private:
    ListNode* recur(ListNode* cur, ListNode* pre){
        if(cur == nullptr) return pre;  //终止条件
        ListNode* res = recur(cur->next, cur);  //递归后继节点，res在回溯过程中一直是反转链表的头节点
        cur->next = pre;  //修改节点引用指向
        return res;  //返回反转链表的头节点
    }
};
```

图解链接：https://leetcode-cn.com/problems/fan-zhuan-lian-biao-lcof/solution/jian-zhi-offer-24-fan-zhuan-lian-biao-die-dai-di-2/

---

【2刷】

题解1原地双指针反转的方法没写出来Orz，自己new了一个反转的链表：

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
    ListNode* reverseList(ListNode* head) {
        if(head == NULL) return NULL;
        if(head -> next == NULL) return head;
        ListNode* pre = new ListNode(head -> val);
        while(head -> next != NULL) {
            head = head -> next;
            ListNode* node = new ListNode(head -> val);  //每个节点都要new出来，并且指向之前已经反转后的最后一个新节点
            node -> next = pre;
            pre = node;
        }
        return pre;
    }
};
```