【题目】

在字符串 s 中找出第一个只出现一次的字符。如果没有，返回一个单空格。 s 只包含小写字母。

【示例】

```c++
s = "abaccdeff"
返回 "b"

s = "" 
返回 " "
```

---

【我的思路—哈希表】

遍历字符串s，使用unordered_map存储s中每个字母出现的次数，由于次数为1的字母大多在map靠后的位置，因此对s的遍历结束后，再遍历map，将出现次数等于1的字母添加到数组temp中（实现倒序，出现1次的字符将位于temp的第一位），假若数组不空（即存在出现一次的字符），则返回数组的第一个元素，否则返回空格。

【我的代码—哈希表】

```c++
class Solution {
public:
    char firstUniqChar(string s) {
        unordered_map<char, int> M;
        for(int i = 0; i < s.size(); i++) {  //遍历s
            M[s[i]]++;  //M中存储不同字母出现的次数
        }
        vector<char> temp;
        for(auto elem : M) {  //遍历M，将出现次数为一次的元素添加到temp数组中
            if(elem.second == 1) temp.push_back(elem.first);
        }
        if(!temp.empty()) return temp[temp.size() - 1];  //假如数组不为空，返回数组的第一个元素即可
        else return ' ';  //否则返回空格
    }
};
```

【题解思路—哈希表】

两次遍历s，使用哈希映射统计出字符串中每个字符出现的次数，第二次遍历s时，只要遍历到一个出现一次的字符时，就返回该字符，否则在遍历结束后返回空格。相对与我的方法，该方法更节省空间。

【题解代码—哈希表】

```c++
class Solution {
public:
    char firstUniqChar(string s) {
        map<char, int> M;
        for(int i = 0; i < s.size(); i++) {  //第一次遍历
            M[s[i]]++;
        }
        for(int i = 0; i < s.size(); i++) {  //第二次遍历
            if(M[s[i]] == 1) return s[i];
        }
        return ' ';
    }
};
```

