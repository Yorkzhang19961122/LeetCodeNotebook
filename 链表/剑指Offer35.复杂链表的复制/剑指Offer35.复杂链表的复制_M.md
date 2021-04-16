【题目】

请实现 copyRandomList 函数，复制一个复杂链表。在复杂链表中，每个节点除了有一个 next 指针指向下一个节点，还有一个 random 指针指向链表中的任意节点或者 null。

【示例】

![123](https://github.com/Yorkzhang19961122/LeetCodeNotebook/blob/main/%E9%93%BE%E8%A1%A8/%E5%89%91%E6%8C%87Offer35.%E5%A4%8D%E6%9D%82%E9%93%BE%E8%A1%A8%E7%9A%84%E5%A4%8D%E5%88%B6/123.png)

```
输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]
```

---

【[题解思路1—哈希表](https://leetcode-cn.com/problems/fu-za-lian-biao-de-fu-zhi-lcof/solution/jian-zhi-offer-35-fu-za-lian-biao-de-fu-zhi-ha-xi-/)】

首先考虑正常的链表复制，首先遍历链表，每轮建立新节点+构建前驱节点pre和当前节点node的指向即可

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        Node* cur = head;
        Node* dumy = new Node(0);
        Node* pre = dumy;  //dumy虚拟节点方便返回
        while(cur != null) {
            Node* node = new Node(cur->val);  //复制当前的节点cur
            pre->next = node;  //新链表的前驱节点指向当前节点
            cur = cur->next;  //遍历下一节点
            pre = node;  //pre移动到node，为下一个节点做准备
        }
        return dumy->next;
    }
};
```

而本题的复杂链表多了一个random指针指向其他的节点，所以需要特殊处理，这里借助哈希map进行存储，键值对分别代表原节点和新链表的节点，然后再分配新链表各节点的next和random指向。

【题解代码1—哈希表】

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head == NULL) return NULL;  //若头节点为空，则直接返回空即可
        unordered_map<Node*, Node*> map;
        Node* cur = head;
        while(cur != NULL) {  //遍历原链表，复制出新链表，map：（原cur节点，新cur节点）
            map[cur] = new Node(cur->val);
            cur = cur->next;
        }
        cur = head;
        while(cur != NULL) {  //构建新链表的引用指向
            map[cur]->next = map[cur->next];  //新链表的next指向
            map[cur]->random = map[cur->random];  //新链表的random指向
            cur = cur->next;
        }
        return map[head];  //返回新链表的头节点
    }
};
```

【[题解思路2—拼接+拆分](https://leetcode-cn.com/problems/fu-za-lian-biao-de-fu-zhi-lcof/solution/jian-zhi-offer-35-fu-za-lian-biao-de-fu-zhi-ha-xi-/)】

* 把原链表中各节点复制并跟在原节点后面，形成新的拼接链表
* 构建新链表的random指向，核心：`cur->next->random = cur->random->next`
* 拆分原链表/新链表，返回新链表即可

【题解代码2—拼接+拆分】

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head == NULL) return NULL;
        Node* cur = head;
        while(cur != NULL) {  //拼接链表
            Node* temp = new Node(cur->val);
            temp->next = cur->next;
            cur->next = temp;
            cur = temp->next;
        }
        cur = head;
        while(cur != NULL) {  //构建各新节点的random指向
            if(cur->random != NULL) {
                cur->next->random = cur->random->next;
            }
            cur = cur->next->next;
        }
        cur = head->next;
        Node* pre = head, *res = head->next;
        while(cur->next != NULL) {  //拆分新旧两个链表
            pre->next = pre->next->next;
            cur->next = cur->next->next;
            pre = pre->next;
            cur = cur->next;
        }
        pre->next = NULL;  //恢复原链表的指向（NULL）
        return res;
    }
};
```

