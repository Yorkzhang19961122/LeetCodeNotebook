【题目】

找出数组中重复的数字。


在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。

【示例】

```c++
输入：
[2, 3, 1, 0, 2, 5, 3]
输出：2 或 3 
```

---

【我的思路1—哈希法】

创建一个Map，用来存储不同数字出现的次数，遍历Map，找到出现次数大于1的数字时返回。

【我的代码1—哈希法】

```c++
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        unordered_map<int, int> Map;
        for(int num : nums){  //遍历nums，将不同数字出现的次数存到Map中
            ++Map[num];
        }
        for(auto elem : Map){  //遍历Map
            if(elem.second > 1) return elem.first;  //假如某个数字出现的次数大于1，则返回这个数字
        }
        return -1;
    }
};
```

简化：

```c++
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        unordered_map<int, int> Map;
        for(int num : nums){  //遍历nums，将不同数字出现的次数存到Map中
            ++Map[num]; 
            if(Map[num] > 1) return num;  //如果某数字出现的次数大于1，则返回这个数字即可
        }
        return -1;
    }
};
```

使用数组也是一样的道理：

```c++
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        vector<int> cnt(100000, 0);
        for(int num : nums){
            ++cnt[num];
            if(cnt[num] > 1) return num;
        }
        return -1;
    }
};
```

【题解思路—原地交换】

题目说明尚未被充分使用，即 在一个长度为 n 的数组 nums 里的所有数字都在 0 ~ n-1 的范围内 。 此说明含义：数组元素的 索引 和 值 是 一对多 的关系。
因此，可遍历数组并通过交换操作，使元素的 索引 与 值 一一对应（即 nums[i] = i ）。因而，就能通过索引映射对应的值，起到与字典等价的作用。

遍历中，第一次遇到数字 x 时，将其交换至索引 x 处；而当第二次遇到数字 x 时，一定有 nums[x] = x，此时即可得到一组重复数字。

算法流程：

1. 遍历数组 nums ，设索引初始值为 i = 0:

   >若 nums[i] = inums[i]=i ： 说明此数字已在对应索引位置，无需交换，因此跳过
   >
   >若 nums[nums[i]] = nums[i]： 代表索引 nums[i]处和索引 i 处的元素值都为 nums[i]，即找到一组重复值，返回此值 nums[i]
   >
   >否则：交换索引为 i 和 nums[i] 的元素值，将此数字交换至对应索引位置

2. 若遍历完毕尚未返回，则返回 -1 

【题解代码—原地交换】

```c++
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        int i = 0;
        while(i < nums.size()){
            if(nums[i] == i){
                ++i;
                continue;
            }
            else if(nums[i] == nums[nums[i]]) return nums[i];
            else swap(nums[i], nums[nums[i]]);
        }
        return -1;
    }
};
```

