【题目】

输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的。

【示例】

```c++
输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4
```

---

【题解思路—双指针+虚拟头节点】

1.初始化：伪头节点dummy，节点cur指向dummy

2.循环合并：当l1或l2为空时跳出

> 1.当l1->val < l2->val时：cur的后继节点指定为l1，并l1向前走一步，节点cur向前走一步
>
> 2.当l1->val >= l2->val时：cur的后继节点指定为l2，并l2向前走一步，节点cur向前走一步

3.合并剩余尾部

【题解代码—双指针+虚拟头节点】

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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0);  //创建虚拟头节点
        ListNode* cur = dummy;  //初始化节点cur为dummy
        while(l1 && l2){  //若l1和l2都不为空，则继续循环
            if(l1 -> val < l2 ->val){  //如果l1节点的值小于l2节点的值
                cur -> next = l1;  //cur->next指向较小的l1
                cur = cur ->next;  //cur向后移
                l1 = l1 -> next;  //l1向后移
            }
            else{  //如果l1节点的值大于或等于l2节点的值
                cur -> next = l2;  //cur指向较小的l2
                cur = cur -> next;  //cur后移
                l2 = l2 -> next;  //l2后移
            }
            //如果l1或l2已经遍历结束（退出上面的while循环），此时较长的链表余下部分则可以直接添加在cur之后（因为其本身就是升序的）
        }
        if(l1) cur -> next = l1;
        if(l2) cur -> next = l2;
        return dummy->next;  //返回dummy->next即合并后的链表
    }
};
```

