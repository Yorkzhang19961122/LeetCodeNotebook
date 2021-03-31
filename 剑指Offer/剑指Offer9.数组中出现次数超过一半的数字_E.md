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



【我的代码—哈希表】

```c++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> Map;
        for(int i = 0; i < nums.size(); i++) {
            Map[nums[i]]++;
        }
       for(auto elem : Map) {
           if(elem.second > nums.size()/2) return elem.first;
       }
        return -1;
    }
};
```

