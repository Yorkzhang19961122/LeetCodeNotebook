【题目】

用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead ，分别完成在队列尾部插入整数和在队列头部删除整数的功能。(若队列中没有元素，deleteHead 操作返回 -1 )

【示例】

```c++
输入：
["CQueue","deleteHead","appendTail","appendTail","deleteHead","deleteHead"]
[[],[],[5],[2],[],[]]
输出：[null,-1,null,null,5,2]
```

---

【题解思路】

借助栈的先进后出原则实现队列的先进先出，使用两个栈stack1为输入栈，stack2为输出栈，其中stack1负责接收append进来的元素，而stack2则负责用来删除元素，具体为：执行append函数时，调用stack1的push函数实现append。当执行delete函数时，首先将stack1中的元素push进入stack2，此时弹出stack2的栈顶元素，这样的插入删除操作就符合队列先进先出的原则，随后将stack2中剩余的元素重新push进入stack1，等待下一次操作。

【题解代码】

```c++
class CQueue {
public:
    stack<int> stack1;  //输入栈，保存输入的值
    stack<int> stack2;  //输出栈，保存输出的值
    CQueue() {}
    
    void appendTail(int value) {
        stack1.push(value);  //插入操作只需要将value放入输入栈stack1即可
    }
    
    int deleteHead() {
        if(stack1.empty()) return -1;  //如果stack1为空，则返回-1

        while(!stack1.empty()){  //将stack1中的值循环取出放入到stack2中
            int temp = stack1.top();
            stack1.pop();
            stack2.push(temp);
        }
        //再弹出输出栈stack2的栈顶，即为输入栈stack1的栈顶
        //res中存放本次delete的值，作为本次删除操作的返回
        //stack2删除栈顶的元素，这样借助两个栈实现了队列的先进先出的操作
        int res = stack2.top();
        stack2.pop(); 
        while(!stack2.empty()){  //遍历stack2将元素移动回stack1中，以便继续进行其他操作
            int temp = stack2.top();
            stack2.pop();
            stack1.push(temp);
        }
        return res;
    }
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */
```

