【题目】

请定义一个队列并实现函数 `max_value` 得到队列里的最大值，要求函数`max_value`、`push_back` 和 `pop_front` 的均摊时间复杂度都是`O(1)`。

若队列为空，`pop_front` 和 `max_value` 需要返回 `-1`。

【示例】

```c++
输入: 
["MaxQueue","push_back","push_back","max_value","pop_front","max_value"]
[[],[1],[2],[],[],[]]
输出: [null,null,null,2,1,2]
```

```c++
输入: 
["MaxQueue","pop_front","max_value"]
[[],[],[]]
输出: [null,-1,-1]
```

---

【我的思路—栈模拟队列（不适合本题）】

由于以前做过[栈模拟队列](https://github.com/Yorkzhang19961122/LeetCodeNotebook/blob/main/%E6%A0%88/%E5%89%91%E6%8C%87Offer09.%E7%94%A8%E4%B8%A4%E4%B8%AA%E6%A0%88%E5%AE%9E%E7%8E%B0%E9%98%9F%E5%88%97_E.md)的题，因此拿到题直接用两个栈`stk1`和`stk2`模拟队列的先进先出，时间空间复杂度非常大，权当练手。

【我的代码—栈模拟队列（不适合本题）】

```c++
class MaxQueue {
    //两个栈，stk1用来push，stk2用来delete
    stack<int> stk1;
    stack<int> stk2;
public:
    MaxQueue() {}
    int max_value() {
        if(stk1.empty()) return -1;  //队列为空，返回-1
        int max = INT_MIN;
        while(!stk1.empty()) {  //将stk1的元素push到stk2中，同时找到最大值max
            int temp = stk1.top();
            if(temp > max) {
                max = temp;
            }
            stk1.pop();
            stk2.push(temp);
        }
        while(!stk2.empty()) {  //将stk2的元素再push回stk1，等待下次操作
            int temp = stk2.top();
            stk2.pop();
            stk1.push(temp);
        }
        return max;
    }
    
    void push_back(int value) {  //插入元素就是向stk1中push元素
        stk1.push(value);
    }
    
    int pop_front() {
        if(stk1.empty()) return -1;  //队列为空，返回-1
        while(!stk1.empty()) {  //将stk1中的元素push到stk2中
            int temp = stk1.top();
            stk1.pop();
            stk2.push(temp);
        }
        int pop_num = stk2.top();  //删除stk2栈顶元素（即相当于队列头的元素），以达到pop_front()的效果
        stk2.pop();
        while(!stk2.empty()) {  //将剩余的元素重新push回stk1，等待下次操作
            int temp = stk2.top();
            stk2.pop();
            stk1.push(temp);
        }
        return pop_num;
    }
};

/**
 * Your MaxQueue object will be instantiated and called as such:
 * MaxQueue* obj = new MaxQueue();
 * int param_1 = obj->max_value();
 * obj->push_back(value);
 * int param_3 = obj->pop_front();
 */
```

【题解思路1—暴力】

直接用数组实现一个队列，查询最大值时遍历计算。

【题解代码2—暴力】

```c++
class MaxQueue {
    int nums[10000];
    int begin = 0, end = 0;
public:
    MaxQueue() {
    }
    int max_value() {
        if(begin == end) return -1;
        int res = 0;
        for(int i = begin; i < end; i++) {  //遍历begin到end，找到最大值
            res = max(res, nums[i]);
        }
        return res;
    }
    
    void push_back(int value) {
        nums[end++] = value;  //此处使用后置自增（先参与运算，再自增）
    }
    
    int pop_front() {
        if(begin == end) return -1;
        return nums[begin++];  //返回begin位置上的元素值即可，同时begin自增，指向下一个元素
    }
};

/**
 * Your MaxQueue object will be instantiated and called as such:
 * MaxQueue* obj = new MaxQueue();
 * int param_1 = obj->max_value();
 * obj->push_back(value);
 * int param_3 = obj->pop_front();
 */
```

本思路中，`pop`和`push`的时间复杂度都为`O(1)`，而取得`max`的时间复杂度为`O(N)`。

【题解思路2—单调双端队列】

使用`O(1)`时间复杂度来获得队列或栈的最大值或者最小值，往往需要使用一个辅助的数据结构来实现（空间换时间）。

对于本题，考虑构建一个递减的双端队列`deque`来保存队列中的元素，`deque`中的元素随着入队和出队操作动态更新，这样队列的最大值就是`deque`的队头元素，实现了获取最大值的`O(1)`复杂度。

需要注意两点：

* 执行入队`push_back()`时：若入队的元素`value`大于`deque`中的某些元素，则将`deque`中小于`value`的元素出队，再将`value`同时入队`queue`和`deque`
* 执行出队`pop_back()`时：若`queue`中出队的元素是最大的元素（即等于`deque`中的首元素），则将`deque`中的首元素同时出队，**以保证`deque`的队首元素始终是当前队列的最大值**

【题解代码2—单调双端队列】

```c++
class MaxQueue {
    queue<int> que;
    deque<int> deq;
public:
    MaxQueue() {
    }
    
    int max_value() {
        if(que.empty()) return -1;  //队列为空，返回-1
        return deq.front();  //否则返回deq的首元素即为此时队列的最大值
    }
    
    void push_back(int value) {
        que.push(value);  //que中直接push
        while(!deq.empty() && deq.back() < value) {  //如果deq的末尾元素小于value，则将小于value的元素都出队
            deq.pop_back();
        }
        deq.push_back(value);  //再将value入队
    }
    
    int pop_front() {
        if(que.empty()) return -1;  //队列为空，返回-1
        int val = que.front();  //val记录que的首元素
        if(val = deque.front()) {  //如果que的首元素等于deq的首元素(即此时的队列最大值)，说明此时出队的元素是队列的最大值
            deq.pop_front();  //那么将deq的首元素也出队
        }
        que.pop();  //que的首元素无论如何都是要出队的
        return val;
    }
};

/**
 * Your MaxQueue object will be instantiated and called as such:
 * MaxQueue* obj = new MaxQueue();
 * int param_1 = obj->max_value();
 * obj->push_back(value);
 * int param_3 = obj->pop_front();
 */
```

其中`max_value`，`pop_front`的时间复杂度为`O(1)`，

而`push_back()`的均摊时间复杂度为`O(1)`：

例如 `543216`，只有最后一次`push_back`是`O(n)`的，其他操作的复杂度均为`O(1)`，则均摊时间复杂度为`(O(1) * (n - 1) + O(n)) / n = O(1)`