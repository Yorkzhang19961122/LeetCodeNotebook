【题目】

输入两个链表，找出它们的第一个公共节点。

【示例】

```c++
输入：intersectVal = 8, listA = [4,1,8,4,5], listB = [5,0,1,8,4,5], skipA = 2, skipB = 3
输出：Reference of the node with value = 8
输入解释：相交节点的值为 8 （注意，如果两个列表相交则不能为 0）。从各自的表头开始算起，链表 A 为 [4,1,8,4,5]，链表 B 为 [5,0,1,8,4,5]。在 A 中，相交节点前有 2 个节点；在 B 中，相交节点前有 3 个节点。
```

---

【我的思路1—双指针】

维护两个指针curA和curB分别初始化为headA和headB，两个指针分别后移，如curA或curB到末尾，则curA指向B，curB指向A，最后两个指针走过的路程一定相同，在交点处两个指针相交，返回这个交点即可，假如两个链表不相交，最后也会返回NULL

【我的代码1—双指针】

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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* curA = headA, *curB = headB;
        if(curA == NULL || curB == NULL) return NULL;  //特殊情况处理
        while(curA != curB){
            curA = curA->next;  //curA后移
            curB = curB->next;  //curB后移
            if(curA == NULL && curB == NULL) return NULL;  //假如两个指针最后都走到了NULL，说明两个链表没有相交     
            if(curA == NULL){  //curA指向NULL，curA重新定位到headB
                curA = headB;
            }
            if(curB == NULL){  //curB指向NULL，curB重新定位到headA
                curB = headA;
            }
            if(curA == curB) return curA;  //找到并返回交点
        }
        return curA;
    }
};
```

代码进行优化：

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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* curA = headA, *curB = headB;
        while(curA != curB){  //遍历直到curA==curB
            if(curA != NULL) curA = curA->next;  //curA!=NULL的判断优于我代码中的逻辑
            else curA = headB;  //curA走到链表尾后，回头走另外一条链
            if(curB != NULL) curB = curB->next;
            else curB = headA;  //curB走到链表尾后，回头走另外一条链
        }
        return curA;
    }
};
```

【我的思路2—两重循环】

两重循环分别比较两个链表中的每个节点，遇到相同即返回

【我的代码2—两重循环】

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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* curA = headA, *curB = headB;
        while(curA != NULL){  //第一重循环
            curB = headB;  //对于A的每个节点，都从B的头节点开始遍历对比
            while(curB != NULL){  //第二重循环
                if(curA == curB) return curA;
                else curB = curB->next;
            }
            curA = curA->next;
        }
        return NULL;
    }
};
```

【我的思路3—集合】

使用集合set存放链表中的节点，并用find函数查找相同的节点

【我的代码3—集合】

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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode*> Set;
        ListNode* curA = headA;
        while(curA != NULL){
            Set.insert(curA);
            curA = curA->next;
        }
        ListNode* curB = headB;
        while(curB != NULL){
            if(Set.find(curB) != Set.end()) return curB;
            curB = curB->next;
        }
        return NULL;
    }
};
```

本题同**面试题02.07.链表相交**

