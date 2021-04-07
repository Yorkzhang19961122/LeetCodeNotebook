【题目】

从扑克牌中随机抽5张牌，判断是不是一个顺子，即这5张牌是不是连续的。2～10为数字本身，A为1，J为11，Q为12，K为13，而大、小王为 0 ，可以看成任意数字。A 不能视为 14。

【示例】

```c++
输入: [1,2,3,4,5]
输出: True
```

```c++
输入: [0,0,1,2,5]
输出: True
```

```c++
输入: [0,0,2,2,5]
输出: False
```

---

【我的思路—排序+遍历】

* 先将nums升序排列
* 再对nums进行依次遍历，遍历的过程中统计数字0出现的次数，并判断是否有重复的数字，若有重复，则直接返回false
* 若没有重复数字，则遍历完成后得到0的个数n_zero
* 因为nums已按照升序排列，因此使用nums中非零的最后一个元素减去首个元素加1，得到的差n_to为以这两个数为首尾需要的连续数字数量
* 而n_true则是nums中实际存在的非零数的数量，由于0可以变成任意数，因此非零数数量n_true加上零的数量n_zero大于或等于n_to则意味着这五个数满足顺子的要求

【我的代码—排序+遍历】

```c++
class Solution {
public:
    bool isStraight(vector<int>& nums) {
        sort(nums.begin(), nums.end());  //对nums进行排列
        int n_zero = 0;  //n_zero记录nums中0的数量
        for(int i = 0; i < nums.size(); i++) {  //遍历排序后的nums
            if(nums[i] == 0) n_zero++;  //统计0的数量
            else {  //判断是否有重复元素
                if(count(nums.begin(), nums.end(), nums[i]) > 1) return false;
            }
        }
        int n_to = nums[nums.size() - 1] - nums[n_zero] + 1;   //非零元素按照顺子的要求应该有的数量(e.g. 1,2,5 --> n_to = (5-1)+1 = 5)
        int n_true = nums.size() - n_zero;  //实际上的非零元素数量
        if(n_to - n_true == n_zero || n_to - n_true < n_zero) return true;  //n_true补零后正好等于n_to(0全都补在中间的空缺位置), 或大于n_to(多余的0可以理解为任意放在首或尾)，则满足顺子的要求
        else return false;
    }
};
```

【题解思路1—集合Set+遍历】

根据题意，五张牌满足顺子的条件有两条：

* 除大小王外，所有牌无重复
* 除大小王外，最大牌max减去最小牌min需要满足（max - min） < 5

【题解代码1—集合Set+遍历】

```c++
class Solution {
public:
    bool isStraight(vector<int>& nums) {
        set<int> repeat;  //使用set去重
        int maxValue = 0;
        int minValue = 14;
        for(int num : nums) {  //遍历nums
            if(num == 0) continue;  //遇到0前进
            maxValue = max(maxValue, num);  //记录最大值
            minValue = min(minValue, num);  //记录最小值
            if(find(repeat.begin(), repeat.end(), num) != repeat.end()) return false;  //找重复
            repeat.insert(num);  //添加不重复的元素
        }
        return maxValue - minValue < 5;  //判断max和min之差是否小于5
    }
};
```

由于set容器本身是升序排列的，因此代码可以优化，免去max和min的获取：

```c++
class Solution {
public:
    bool isStraight(vector<int>& nums) {
        set<int> repeat;  //使用set去重
        for(int num : nums) {  //遍历nums
            if(num == 0) continue;  //遇到0前进
            if(find(repeat.begin(), repeat.end(), num) != repeat.end()) return false;  //找重复
            repeat.insert(num);  //添加不重复的元素
        }
        return *repeat.rbegin() - *repeat.begin() < 5;  //由于set已经升序排列，因此判断max和min之差是否小于5
    }
};
```

【题解思路2—排序+遍历】

* 先对数组排序
* 判别重复元素，通过nums[i] == nums[i+1]
* 获取最大最小的牌之差，若小于5，则为顺子

【题解代码2—排序+遍历】

```c++
class Solution {
public:
    bool isStraight(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int joker = 0;  //大小王的数量
        for(int i = 0; i < 4; i++) {  //注意i最大到3
            if(nums[i] == 0) joker++;  //统计0的数量
            else if(nums[i] == nums[i + 1]) return false;  //否则判断重复
        }
        return nums[4] - nums[joker] < 5;
    }
};
```



【TIPS】

C++中的`begin(),end()`和`rbegin(), rend()`:

见[此链接](https://blog.csdn.net/kjing/article/details/6936325)