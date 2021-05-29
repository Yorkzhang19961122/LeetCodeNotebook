【题目】

请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子字符串的长度。

【示例】

```c++
输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
```

```c++
输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
```

```c++
输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
```

---

【我的思路—双指针】

借助left和right两个指针，对字符串s进行遍历，并利用set查询当前元素是否重复：

* 初始阶段：left指向下标0，right指向下标1，将left下标对应的字符添加入set中
* 开始遍历：判断right下标对应的字符是否与set中重复：
  * 如果不重复：说明这个字符可以计入当前的子串，length++，并将此时right对应的字符添加到set中，right++，准备处理下一个字符
  * 如果重复：left移动到right的位置，right右移，并将set清空，将left对应的元素添加到set中，length恢复为1，恢复到初始状态

遍历的过程中使用max_length存储最大的长度，最后返回即可

【我的代码—双指针】

```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.size() == 1) return 1;  //特殊情况预处理
        unordered_set<int> Set;  //初始化set用于存储此时不重复的子串
        int left = 0, right = 1;  //初始化两个指针left和right
        Set.insert(s[left]);  //先将left对应的元素插入set中
        int length = 1, max_length = 0;
        while(right < s.size()) {   //遍历s，直到right指向s的最后一个字符
            if(!Set.count(s[right])) {  //如果当前right下标对应的字符在set中不存在
                length++;  
                Set.insert(s[right]);
                right++;
            }
            else {  //如果当前right下标对应的字符在set中存在，将两个指针和其他中间变量恢复到初始状态
                left++;
                right = left + 1;
                Set.clear();
                Set.insert(s[left]);
                length = 1;
            }
            max_length = max(max_length, length);  //记录遍历过程中出现的最大不重复子串长度
        }
        return max_length;
    }
};
```

【[题解思路—滑动窗口（双指针）](https://leetcode-cn.com/problems/zui-chang-bu-han-zhong-fu-zi-fu-de-zi-zi-fu-chuan-lcof/solution/tu-jie-hua-dong-chuang-kou-shuang-zhi-zhen-shi-xia/)】

* 初始化头尾指针`head`,`tail`
* 判断`tail`指向的元素是否在当前的滑动窗口中：
  * 如果窗口中没有该元素，更新窗口的最大长度，`tail`指针继续右移
  * 如果窗口中存在该元素，将`head`指针右移，直到窗口中不包含`tail`指针对应的元素
* 返回窗口长度的最大值

【题解代码—滑动窗口（双指针）】

以下是不借助其他数据结构的写法，直接在字符串上进行处理：

```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.size() < 2) return s.size();  //特殊情况处理
        int head = 0, tail = 1;  //双指针（滑动窗口的边界）初始化，因为上面已经把特殊情况处理了，因此窗口可以按照长度为1进行初始化
        int res = 1;
        while(tail < s.size()) {  //循环处理字串s
            //s.substr(head, tail - head) 代表当前滑动窗口[head, tail - 1]中的字符串
            //string的find函数如果查找不到返回s.npos，也等于-1
            if(s.substr(head, tail - head).find(s[tail]) == s.substr(head, tail - head).npos) {  //如果tail指向的字符在此时的滑动窗口[head, tail - 1]中不存在
                res = max(res, tail - head + 1);  //此时的滑动窗口[head, tail]长度就是目前的不重复子串，同时更新res
                tail++;  //当前窗口处理完后tail右移
            }
            else {  //如果tail对应的字符在此时的滑动窗口中存在
                while(s.substr(head, tail - head).find(s[tail]) != s.substr(head, tail - head).npos) {  //将head指针右移，直到窗口中不包含tail指向的元素
                    head++;
                }
            }
        }
        return res;  
    }
};
```

还可以借助hash表存放当前窗口中的字符（思路与上面的代码相同）：

```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
    if(s.size() < 2) return s.size();
    int left = 0, right = 1, res = 1;
    unordered_set<char> Set;
    Set.insert(s[left]);
    while(right < s.size()) {
        if(Set.find(s[right]) == Set.end()) {  //right指针指向的元素在当前set中不存在
            Set.insert(s[right]);
            right++;
            res = max(res, right - left);
        }
        else {  //right指针指向的元素在当前set中存在
            while(Set.find(s[right]) != Set.end()) {  //循环在set中找到s[right]，如果能找到，说明重复元素仍在当前窗口中
                //移除left指向的元素，并减小窗口，直到窗口中不含有重复的元素(即s[right])
                Set.erase(s[left]);  
                left++;
            }
        }
    }
    return res;
    }
};
```



除此之外，我们还可以使用哈希map记录每个字符的下一个索引，然后尽量向右移动尾指针来拓展窗口，并更新窗口的最大长度。如果尾指针指向的元素重复，则将头指针直接移动到窗口中重复元素的右侧。

[题解链接](https://leetcode-cn.com/problems/zui-chang-bu-han-zhong-fu-zi-fu-de-zi-zi-fu-chuan-lcof/solution/tu-jie-hua-dong-chuang-kou-shuang-zhi-zhen-shi-xia/)

```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.size() < 2) return s.size();
        map<char, int> m;  //创建hashmap用来存储字符及其位置
        int left = 0, res = 0;
        for(int right = 0; right < s.size(); right++) {  
            if(m.find(s[right]) != m.end()) {  //如果right指向的元素是重复的
                left = max(left, m[s[right]] + 1);  //left更新为s[right]在m中对应下标的右边一位；而有些情况下left > m[s[right]] + 1,所以要用max取大值，使得此时的left保持不动（只关注当前窗口left,right之间的元素），例如'abba'
            }
            m[s[right]] = right;  //将right及其下标加入m中
            res = max(res, right - left + 1);  //更新此时的最大不重复子串长度
        }
        return res;
    }
};
```

按照上面的代码风格，这种思路可以写作：

```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.size() < 2) return s.size();
        int left = 0, right = 1, res = 1;
        unordered_map<char, int> Map;
        Map[s[left]] = left;
        while(right < s.size()) {
            if(Map.find(s[right]) == Map.end()) {
                Map[s[right]] = right;
                right++;
                res = max(res, right - left);
            }
            else {
                left = max(left, Map[s[right]] + 1);  //注意这个max，使我们只关注当前窗口[left,right]中的元素
                Map.erase(s[right]);
            }
        }
        return res;
    }
};
```

