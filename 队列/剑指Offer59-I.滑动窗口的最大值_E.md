【题目】

给定一个数组 `nums` 和滑动窗口的大小 `k`，请找出所有滑动窗口里的最大值。

【示例】

```c++
输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
输出: [3,3,5,5,6,7] 
解释: 

  滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
```

---

【我的思路—模拟窗口】

模拟窗口在数组上前进，每次得到当前窗口中的最大值，添加进结果中。

【我的代码—模拟窗口】

```c++
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int left = 0, right = left + k - 1;   //初始化窗口
        vector<int> ans;
        while(right < nums.size()) {  //right到数组底时，跳出循环
            int max = INT_MIN;
            for(int i = left; i <= right; i++) {  //遍历当前窗口
                if(nums[i] > max) max = nums[i];  //更新最大值
            }
            ans.push_back(max);
            //窗口右移
            left++;  
            right++;
        }
        return ans;
    }
};
```

由于测试用例的关系，本题暴力法可以通过，而主站239题则无法使用暴力法。

时间复杂度为O(n*k)

【题解思路—模拟单调队列】

这是使用单调队列的经典题目，我们需要维护一个队列，这个队列，放进去窗口里的元素，然后随着窗口的移动，队列也一进一出，每次移动之后，队列告诉我们里面的最大值是什么。

队列应该长这个样子：

```c++
class MyQueue { 
public:
    void pop(int value) {
    }
    void push(int value) {
    }
    int front() {
        return que.front();
    }
};
```

每次窗口移动的时候，调用`que.pop(滑动窗口中移除元素的数值)`，`que.push(滑动窗口添加元素的数值)`，然后`que.front()`就返回我们要的最大值。

设计单调队列的时候，pop和push操作要保持如下规则：

1. pop(value)：如果窗口移除的元素value等于单调队列的出口元素，那么队列弹出元素，否则不用任何操作
2. push(value)：如果push的元素value大于入口元素的数值，那么就将队列入口的元素弹出，直到push元素的数值小于等于队列入口元素的数值为止
3. 保持如上规则，每次窗口移动的时候，只要问que.front()就可以返回当前窗口的最大值。

【题解代码—模拟单调队列】

```c++
class Solution {
public:
    class MyQueue {
    public:
        deque<int> que;  //使用双端队列deque来实现我们需要的单调序列
        void pop(int value) {  //删除
            if(!que.empty() && value == que.front()) {  //移动窗口时，窗口最左边待删除的元素等于que中front元素，那么将que中的front元素移除（if）
                que.pop_front();
            }
        }
        void push(int value) {  //添加
            while(!que.empty() && value > que.back()) {  //小于待添加value的元素将会被删除，从而使que始终为单调队列（while）
                que.pop_back();
            }
            que.push_back(value);
        }
        int front() {  //返回当前最大值
            return que.front();
        }
    };
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MyQueue que;
        vector<int> res;
        if(nums.empty()) return res;
        for(int i = 0; i < k; i++) {  //先把第一个窗口中的元素（前k个）调用push方法放到单调队列中
            que.push(nums[i]);
        }
        res.push_back(que.front());  //将第一个窗口中的最大值添加到res中
        for(int i = k; i < nums.size(); i++) {  //遍历剩下的窗口
            que.pop(nums[i - k]);  //模拟窗口滑动
            que.push(nums[i]);  //模拟窗口滑动
            res.push_back(que.front());  //返回当前窗口的最大值（即que的front元素）
        }
        return res;
    }
};
```

