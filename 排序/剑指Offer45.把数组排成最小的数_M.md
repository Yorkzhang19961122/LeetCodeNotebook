【题目】

输入一个非负整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。

【示例】

```c++
输入: [3,30,34,5,9]
输出: "3033459"
```

---

【题解思路—自定义排序】

此题求拼接起来的最小数字，本质上是一个排序问题。设数组 `nums` 中任意两数字的字符串为 `x` 和 `y` ，则规定排序判断规则为：

* 若拼接字符串 `x + y > y + x` ，则 `x` “大于” `y` ；
* 反之，若 `x + y < y + x` ，则 `x` “小于” `y `；
  * `x` “小于” `y` 代表：排序完成后，数组中 `x` 应在 `y` 左边；“大于” 则反之。

根据以上规则，套用任何排序方法对 `nums` 执行排序即可。

【题解代码1—自定义排序之sort函数】

```c++
class Solution {
public:
    string minNumber(vector<int>& nums) {
        string res;
        vector<string> strs;
        for(int i = 0; i < nums.size(); i++) {  //将nums中的数字转为string后存入strs中
            strs.push_back(to_string(nums[i]));
        }
        sort(strs.begin(), strs.end(), [](string& x, string& y){return x + y < y + x;});  //自定义排序顺序，将strs中的string进行排序，使用了lambda表达式，注意string重载了运算符，可以直接比较
        for(auto str : strs) {
            res += str;  //将排序的结果拼接到res中
        }
        return res;
    }
};
```

非lambda表达式实现：

```c++
class Solution {
public:
    static bool cmp(const string& x, const string& y) {
        return x + y < y + x;
    }
    string minNumber(vector<int>& nums) {
        string res;
        vector<string> strs;
        for(int i = 0; i < nums.size(); i++) {  //将nums中的数字转为string后存入strs中
            strs.push_back(to_string(nums[i]));
        }
        sort(strs.begin(), strs.end(), cmp);  //自定义排序顺序，将strs中的string进行排序
        for(auto str : strs) {
            res += str;  //将排序的结果拼接到res中
        }
        return res;
    }
};
```

【题解代码2—自定义排序之快排】

```c++
class Solution {
public:
    string minNumber(vector<int>& nums) {
        string res;
        vector<string> strs;
        for(auto num : nums) {  //将num转为string存在strs中
            strs.push_back(to_string(num));
        }
        QuickSort(0, strs.size() - 1, strs);  //对strs进行快排
        for(auto str : strs) {  //将排序后的strs拼接起来
            res += str;
        }
        return res;
    }
    //快排的实现
    void QuickSort(int left, int right, vector<string>& strs) {
        if(left >= right) return;
        int i = left, j = right;
        while(i < j) {
            //利用我们自己定义的规则x + y < y + x，则x“小于”y，即x在y的前面
            //x + y > y + x，则x“大于”y，即x在y的后面
            while(strs[j] + strs[left] >= strs[left] + strs[j] && i < j) j--;  //若strs[j]“大于”strs[left]，说明strs[j]在strs[left]的后面，则j左移，直到找到strs[j]在strs[left]左边
            while(strs[i] + strs[left] <= strs[left] + strs[i] && i < j) i++;  //同上，直到找到strs[i]在strs[left]的右边
            swap(strs[i], strs[j]);  //交换
        }
        swap(strs[i], strs[left]);  //基准数归位，基准数左边都小于它，右边都大于它
        QuickSort(left, i - 1, strs); //递归左
        QuickSort(i + 1, right, strs); //递归右
    }
};
```

