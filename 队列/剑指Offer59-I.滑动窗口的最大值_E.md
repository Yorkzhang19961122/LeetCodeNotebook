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