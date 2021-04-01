【题目】

输入一个递增排序的数组和一个数字s，在数组中查找两个数，使得它们的和正好是s。如果有多对数字的和等于s，则输出任意一对即可。

【示例】

```c++
输入：nums = [10,26,30,31,47,60], target = 40
输出：[10,30] 或者 [30,10]
```

---

【我的思路—穷举】

两重遍历，找相加为target的数，找到即返回这两个数。

【我的代码—穷举】

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        //两重循环遍历nums
        for(int i = 0; i < nums.size(); i++) {  //i指向数对的第一个数字，从0到nums.size()-2
            for(int j = nums.size() - 1; j > i; j--) {  //j指向数对的第二个数字，从nums.size()-1到i+1
                if(nums[i] + nums[j] == target) {  //如果两数之和等于target
                    return vector<int>{nums[i], nums[j]};  //返回数对
                }
            }
        }
        return vector<int>{-1, -1};  //穷举完没有答案，返回{-1, 1}
    }
};
```

时间复杂度为O(N^2)，超出时间限制。

利用上有序数组的性质，当j减小时，假如nums[i]+nums[j] < target，则j不必要再继续减小，提前跳出内层j的循环即可：

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res;
        for(int i = 0; i < nums.size() - 2; i++) {
            for(int j = nums.size() - 1; j > i; j--) {
                if(nums[i] + nums[j] == target) {
                    return vector<int>{nums[i], nums[j]};
                }
                if(nums[i] + nums[j] < target) {  //提前break
                    break;
                }
            }
        }
        return vector<int>{-1, -1};
    }
};
```

但是时间复杂度仍然为O(N^2)

【题解思路1—双指针】

有序数组，首先想到双指针（二分），定义左右指针，分别向内移动，计算两数之和，若等于target，则返回，否则调整左右指针的移动。

【题解代码1—双指针】

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;  //初始化left和right指针
        while(left < right) {  //双指针移动
            if(nums[left] + nums[right] < target) {  //left和right指向的元素和小于target
                left++;  //left右移
            }
            else if(nums[left] + nums[right] > target) {
                right--;  //否则right左移
            }
            else {
                return vector<int>{nums[left], nums[right]};  //left和right指向的元素和等于target
            }
        }
        return vector<int>{-1, -1};
    }
};
```

时间复杂度O(N)

【题解思路2—哈希法】

创建哈希表，遍历nums，统计哈希表中是否存在等于target-nums[i]的数字，若存在，则说明此时的nums[i]和target-nums[i]就是满足条件的一对数，返回即可。否则将此时的nums[i]添加到哈希表中。

【题解代码2—哈希法】

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_set<int> Set;
        for(int i = 0; i < nums.size(); i++) {  //遍历nums
            if(Set.count(target - nums[i])) return vector<int>{target - nums[i], nums[i]};  //用哈希表记录有没有符合taeget - nums[i]的数字出现过，有的话返回target - nums[i]和nums[i]即可
            Set.insert(nums[i]);  //没有的话，将现在的数插入哈希表中
        }
        return vector<int>{-1, -1};
    }
};
```

