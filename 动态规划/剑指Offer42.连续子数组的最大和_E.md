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

【题解思路1—动态规划DP】

为了使时间复杂度为`O(N)`，考虑使用动态规划求解：

* 创建`dp`数组，`dp[i]`表示`nums`中以`nums[i]`结尾的最大子序和，而`dp[i] = max(dp[i - 1] + nums[i], nums[i])`

* 为了降低空间复杂度，直接在`nums`数组上进行更改，新的`nums[i]`记录以原`nums[i]`为结尾的子段和的最大值，`nums[i-1]`小于`0`时，`nums[i]`等于本身（因为加上`nums[i-1]`只会使得结果更小），当`nums[i-1]`大于等于`0`时，`nums[i]`等于`nums[i]+nums[i-1]`

【题解代码1-1—动态规划DP，新建数组】

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> dp(nums.size());  //创建dp数组用存放以nums[i]为结尾的子数组的元素和
        dp[0] = nums[0];  //dp[0]用nums[0]初始化
        for(int i = 1; i < nums.size(); ++i){  //遍历nums
            if(dp[i-1] >= 0){  //如果dp[i-1]大于等于0
                dp[i] = nums[i] + dp[i-1];  //dp[i]等于nums[i]加上大于0的dp[i-1]，使结果得以变大
            }
            else dp[i] = nums[i];  //而dp[i-1]小于0，则dp[i]直接等于nums[i]
        }
        return *max_element(dp.begin(), dp.end());  //遍历结束后，返回dp数组中的最大值即可
    }
};
```

上述代码可以进一步优化空间复杂度为：

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> dp(nums.size());
        dp[0] = nums[0];
        
        for(int i = 1; i < nums.size(); i++) {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);
        }
        return *max_element(dp.begin(), dp.end());
    }
};
```

> 时间复杂度O(N)
>
> 空间复杂度O(N)

【题解代码1-2—动态规划DP，原地】

动态规划可以进一步优化空间复杂度：

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int res = nums[0];  //res用于存储最大连续子数组的和，注意此处用nums[0]初始化res，防止后面漏比较nums第一个数
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

> 时间复杂度O(N)
>
> 空间复杂度O(1)

二刷时写此思路的代码：

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        for(int i = 1; i < nums.size(); i++) {
            if(nums[i - 1] > 0) {  //如果nums[i-1]大于等于0
                nums[i] += nums[i - 1];
            }
            else {
                continue;
            }
        }
        return *max_element(nums.begin(), nums.end());  //直接用max_element函数得到最大值
    }
};
```

【题解思路2—暴力】

用两重外循环确定子数组的起始和终止点，再用一重内部的循环来计算这个范围内的元素和，同时更新最大值`max`，以下两种代码都会超出时间限制，因此只作为练手。

【题解代码2-1—暴力O(N^3)】

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.size() == 1) return nums[0];
        int max = INT_MIN;
        for(int i = 0; i < nums.size(); ++i){  //定前面
            for(int j = i; j < nums.size(); ++j){  //定后面
                int sum = 0;
                for(int p = i; p < j + 1; ++p){  //计算前后间的元素和
                    sum += nums[p];
                }
                if(sum > max) max = sum;    //更新最大值
            }
        }
        return max;
    }
};
```

【题解代码2-2—暴力O(N^2)】

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.size() == 1) return nums[0];
        int max = INT_MIN;
        for(int i = 0; i < nums.size(); ++i){  //定前面
            int sum = 0;
            for(int j = i; j < nums.size(); ++j){  //动态相加
                sum += nums[j];
                if(sum > max) max = sum;    //更新最大值
            }
        }
        return max;
    }
};
```

【题解思路3—贪心算法】

> 当叠加的和`curSum`小于0等于时，就从下一个数重新开始，同时更新最大和的值`resSum`
>
> 当叠加的和`curSum`大于0时，将下一个数值加入和中，同时更新最大和的值，依此继续

【题解代码3】

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int resMax = INT_MIN;
        int curSum = 0;
        for(int i = 0; i < nums.size(); i++){  //遍历数组
            if(curSum <= 0){  //如果当前的和小于等于0，那么curSum等于nums[i]，从下一个数重新开始
                curSum = nums[i];
            }
            else {  //如果当前的和大于0，那么将nums[i]加入和中
                curSum += nums[i];
            }
            if(curSum > resMax) resMax = curSum;  //每判断一次都要更新和的最大值
        }
        return resMax;
    }
};
```

