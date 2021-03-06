【题目】

输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个节点。例如，一个链表有6个节点，从头节点开始，它们的值依次是1、2、3、4、5、6。这个链表的倒数第3个节点是值为4的节点。

【示例】

```c++
给定一个链表: 1->2->3->4->5, 和 k = 2.

返回链表 4->5.
```

---

【我的思路—遍历】

先得到链表的长度，然后标志出倒数第几个节点，再遍历链表直至标记点，返回剩下的节点就是最终的结果

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
    ListNode* getKthFromEnd(ListNode* head, int k) {
        int len = 0;
        ListNode* temp = head;
        while(temp != NULL){
            ++len;
            temp = temp->next;
        }  //遍历链表得到长度
        ListNode* ans = head;
        int x = len - k;  //x用来标记循环终止的位置，余下的链表就是需要返回的
        while(x > 0){  //遍历链表
            --x;
            ans = ans->next;  //更新ans
        }
        return ans;  //遍历结束后返回倒数第k个节点
    }
};
```

【题解思路—快慢指针】

双指针，第一个指针先找到正序的第k个结点，两个指针之间相差k个位置，然后两个指针同时后移，当快指针达到链表尾部（为空）时（此题和[题19.删除链表的倒数第N个节点](https://github.com/Yorkzhang19961122/LeetCodeNotebook/blob/main/%E9%93%BE%E8%A1%A8/19.%E5%88%A0%E9%99%A4%E9%93%BE%E8%A1%A8%E7%9A%84%E5%80%92%E6%95%B0%E7%AC%ACN%E4%B8%AA%E7%BB%93%E7%82%B9_M.md)类似），慢指针就是倒数第k个结点。

【TIPS】和19题不同的是：19题要删除倒数第n个节点，所以需要慢指针指向待删除节点的前驱节点（方便删除），因此要使用虚拟头节点，且让慢指针初始化为虚拟头节点，这样最后当快指针到达链表尾时，慢指针才能指向待删除的节点

【题解代码—快慢指针】

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
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* fast = head;  //快指针
        while(k > 0){  //快指针先出发到链表正序k的位置
            --k;
            fast = fast->next;
        }
        ListNode* slow = head;  //慢指针
        while(fast != NULL){  //快指针先到链表末尾，此时的慢指针就是倒数第k个节点
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};
```

