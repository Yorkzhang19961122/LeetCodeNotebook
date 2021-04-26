【题目】

输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如，序列 {1,2,3,4,5} 是某栈的压栈序列，序列 {4,5,3,2,1} 是该压栈序列对应的一个弹出序列，但 {4,3,5,1,2} 就不可能是该压栈序列的弹出序列。

【示例】

```c++
输入：pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
输出：true
解释：我们可以按以下顺序执行：
push(1), push(2), push(3), push(4), pop() -> 4,
push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1
```

---

【题解思路—栈模拟】

用栈来模拟压入弹出的顺序：

* 定义一个栈`stk`用于模拟
* 遍历`pushed`数组，将其中元素压入栈中
* 每压入一个元素，判断栈顶的元素是否和`popped`数组中第`cur`个元素相同，相同则弹出
* 最后判断栈`stk`是否为空，为空则说明`pushed`和`popped`数组满足栈的压入弹出，返回true，否则返回false

【题解代码—栈模拟】

```c++
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        sack<int> stk;  //定义栈用于模拟
        int cur = 0;
        for(int i = 0; i < pushed.size(); i++) {  //遍历pushed数组
            stk.push(pushed[i]);  //将push数组中的元素压入栈中
            while(!stk.empty() && stk.top() == popped[cur]) {  //若此时栈顶元素与popped第cur个元素相同
                stk.pop();  //将栈顶元素弹出
                cur++;  //cur++，判断下一个
            }
        }
        return stk.empty();  //返回stk是否为空
    }
};
```

