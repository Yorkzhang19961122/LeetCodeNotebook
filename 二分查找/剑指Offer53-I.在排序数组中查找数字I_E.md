【题目】

统计一个数字在排序数组中出现的次数。

【示例】

```c++
输入: nums = [5,7,7,8,8,10], target = 8
输出: 2
```

---

【题解思路1—哈希表】

创建哈希map，保存每个数字以及其出现的次数

【题解代码1—哈希表】

```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        unordered_map<int, int> Map;
        for(int i = 0; i < nums.size(); i++) {  //遍历nums
            if(nums[i] == target) Map[nums[i]]++;  //统计nums中等于target的数量
        }
        return Map[target];  //返回target在nums中出现的次数
    }
};
```

【题解思路2—二分查找】

二分法查找nums[mid]等于target的位置，然后左右分别遍历，统计所有nums等于target的数量

【题解代码2—二分查找】

```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        int res = 0;
        while(left <= right) {
            int mid = left + (right - left) / 2;
            if(nums[mid] < target) left = mid + 1;  //mid位置的数字小于target
            else if(nums[mid] > target) right = mid - 1;  //mid位置的数字大于target
            else {  //mid位置的数字等于target
                res++;  //res先加1
                right = mid + 1; //搜索mid右边
                while(right <= nums.size() - 1) {
                    if(nums[right] == target) {
                        res++;
                        right++;
                    }
                    else break;
                }
                left = mid - 1;  //搜索mid左边
                while(left >= 0) {
                    if(nums[left] == target) {
                        res++;
                        left--;
                    }
                    else break;
                }
                return res;
            }
        }
        return 0;
    }
};
```

