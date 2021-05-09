【题目】

定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的 min 函数在该栈中，调用 min、push 及 pop 的时间复杂度都是 O(1)。

【示例】

```c++
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.min();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.min();   --> 返回 -2.
```

---

【[题解思路—辅助栈](https://leetcode-cn.com/problems/bao-han-minhan-shu-de-zhan-lcof/solution/mian-shi-ti-30-bao-han-minhan-shu-de-zhan-fu-zhu-z/)】

此题与[队列的最大值](https://github.com/Yorkzhang19961122/LeetCodeNotebook/blob/main/%E5%89%91%E6%8C%87Offer/%E5%89%91%E6%8C%87Offer59-II.%E9%98%9F%E5%88%97%E7%9A%84%E6%9C%80%E5%A4%A7%E5%80%BC_M.md)类似，也是**空间换时间**。

> 普通的栈的`push()`和`pop()`函数的时间复杂度均为O(1)；而获得最小值`min()`函数则需要遍历整个栈，复杂度为`O(N)`

为此，考虑使用空间换时间，借助一个辅助的栈`stk2`来保存当前数据栈`stk1`内的最小值：

* 数据栈`stk1`：此栈用来实现基本的`push`、`pop`、`top`函数
* 辅助栈`stk2`：按照栈底到栈顶降序，将`stk1`中的元素`push`到辅助栈中（遇到大于当前栈顶的元素则跳过），使得当前数据栈中的最小元素始终对应辅助栈的栈顶元素，从而使时间复杂度降低到`O(1)`

【题解代码—辅助栈】

```c++
class MinStack {
    stack<int> stk1;
    stack<int> stk2;
public:
    /** initialize your data structure here. */
    MinStack() {
    }
    void push(int x) {
        stk1.push(x);  //数据栈直接push
        if(stk2.empty() || x <= stk2.top()) {  //辅助栈若为空或者待处理数据小于等于当前辅助栈栈顶元素，则push，以达到辅助栈由底至顶的降序排列，此处的小于等于避免了重复的最小值被弹出（如push0，push1，push0）
            stk2.push(x);
        }
    }
    
    void pop() {  //只有当数据栈中的栈顶元素等于辅助栈的栈顶元素（即当前要弹出数据栈的元素为此时的最小值），才将辅助栈的栈顶元素弹出
        if(stk1.top() == stk2.top()) {
            stk2.pop();
        }
        stk1.pop();
    }
    
    int top() {
        return stk1.top();
    }
    
    int min() {
        return stk2.top();  //当前栈中的最小值即为辅助栈的栈顶元素
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->min();
 */
```

