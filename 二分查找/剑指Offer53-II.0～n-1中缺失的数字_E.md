【题目】

一个长度为n-1的递增排序数组中的所有数字都是唯一的，并且每个数字都在范围0～n-1之内。在范围0～n-1内的n个数字中有且只有一个数字不在该数组中，请找出这个数字。

【示例】

```c++
输入: [0,1,2,3,4,5,6,7,9]
输出: 8
```

```c++
输入: [0,1,3]
输出: 2
```

---

【题解思路1—二分法】

看到有序的数组，考虑二分法。此题则是通过nums[mid]（值）和mid（索引）的关系对左右边界进行处理。

【题解代码1—二分法】

```c++
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;  //左右两个边界
        while(left <= right) {  //当left>right时跳出循环
            int mid = left + (right - left) / 2;  
            if(nums[mid] == mid) {  //此时缺失的数字一定在mid右边，因此执行left=mid+1
                left = mid + 1;
            }
            else if(nums[mid] > mid) {  //此时缺失的数字一定在m左边，因此执行right=mid-1
                right = mid - 1;
            }
        }
        return left;  //跳出循环后，返回下标left即为缺失的数字
    }
};
```

【题解思路2—遍历】

直接遍历整个数组，缺哪个数就返回哪个，注意如果缺的是最后一个数，那么直接在最后返回原数组的长度即可。

【题解代码2—遍历】

```c++
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int length = nums.size();
        for(int i = 0; i < nums.size(); ++i) {  //遍历数组
            if(nums[i] != i) {  //进行比较
                return i; 
            }
        }
        return length;
    }
};
```

【题解思路3—求和】

求出给定数组nums的和sum，再求出不缺某个数时的连续整数和full，它们的差就是缺的数字

【题解代码3—求和】

```c++
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int sum = 0;
        for(int i = 0; i < nums.size(); i++) {  //给定数组nums的和sum
            sum += nums[i];
        }
        int full = (0 + nums.size())*(nums.size() + 1)/2;  //不缺某个数时的连续整数和full
        return full - sum;
    }
};
```

