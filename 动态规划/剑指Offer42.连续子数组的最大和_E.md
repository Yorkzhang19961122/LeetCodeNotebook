【题目】

输入一个整型数组，数组中的一个或连续多个整数组成一个子数组。求所有子数组的和的最大值。

要求时间复杂度为O(n)。

【示例】

```c++
输入: nums = [-2,1,-3,4,-1,2,1,-5,4]
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
```

---

【题解思路—动态规划DP】

为了使时间复杂度为O(N)，考虑使用动态规划求解，为了降低空间复杂度，直接在nums数组上进行更改，新的nums[i]记录以原nums[i]为结尾的子段和的最大值，nums[i-1]小于0时，nums[i]等于本身（因为加上nums[i-1]只会使得结果更小），当nums[i-1]大于等于0时，nums[i]等于nums[i]+nums[i-1]。

【题解代码1—动态规划DP，新建数组】

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> dp(nums.size());  //创建dp数组用存放以nums[i]为结尾的子数组的元素和
        dp[0] = nums[0];  //dp[0]用nums[0]初始化
        for(int i = 1; i < nums.size(); ++i){  //遍历nums
            if(dp[i-1] >= 0){  //如果dp[i-1]大于等于0
                dp[i] = nums[i] + dp[i-1];  //dp[i]等于nums[i]加dp[i-1]，使得dp[i]更大
            }
            else dp[i] = nums[i];  //而dp[i-1]小于0，则dp[i]直接等于nums[i]
        }
        return *max_element(dp.begin(), dp.end());  //遍历结束后，返回dp数组中的最大值即可
    }
};
```

【题解代码2—动态规划DP，原地】

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int res = nums[0];  //res用于存储最大连续子数组的和
        for(int i = 1; i < nums.size(); ++i){  //遍历nums
            if(nums[i - 1] >= 0){  //如果nums[i-1]大于等于0
                nums[i] = nums[i] + nums[i - 1];  //此刻的nums[i]就等于nums[i-1]加上nums[i]，使得结果可以更大
            }
            res = max(res, nums[i]);  //同时更新最大连续数组和res
        }
        return res;  //遍历结束后返回res
    }
};
```