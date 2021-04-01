【题目】

数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。

【示例】

```c++
输入: [1, 2, 3, 2, 2, 2, 5, 4, 2]
输出: 2
```

---

【我的思路—哈希表】

建立HashMap，存放不同数字出现的次数，然后判断某个数字出现的次数是否大于nums中数字数量的一半。

【我的代码—哈希表】

```c++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> Map;
        for(int i = 0; i < nums.size(); i++) {  //遍历nums
            Map[nums[i]]++;
        }
       for(auto elem : Map) {  //遍历Map
           if(elem.second > nums.size()/2) return elem.first;
       }
        return -1;
    }
};
```

可以不需要第二次对map的循环，直接在map元素的添加过程中进行判断，优化后的代码如下：

```c++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> Map;
        for(int i = 0; i < nums.size(); i++) {  //遍历nums
            Map[nums[i]]++;
            if(Map[nums[i]] > nums.size()/2) return nums[i];  //在遍历的过程中动态判断是否满足题目要求
        }
        return -1;
    }
};
```

【题解思路1—数组排序法】

将数组nums排序，排序后的数组中点的元素一定为众数

【题解代码1—数组排序法】

```c++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());  //排序
        return(nums[nums.size()/2]);  //返回众数（中点的数）
    }
};
```

【题解思路2—摩尔投票】

初始化选票vote和候选人candidate，遍历nums，如果num和候选人candidate一致，则票数加1，否则票数抵消，如果vote=0，下一个num就成为此时的候选人。

【题解代码2—摩尔投票】

```c++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int vote = 0, candidate = 0;
        for(int num : nums) {  //遍历nums
            if(vote == 0) candidate = num;  //如果vote=0，下一个num就成为此时的候选人
            
            if(num == candidate) vote++;  //如果num和候选人candidate一致，则票数加1
            else vote--;  //否则票数抵消
        }
        return candidate;
    }
};
```

