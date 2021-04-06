【题目】

输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。为简单起见，标点符号和普通字母一样处理。例如输入字符串"I am a student. "，则输出"student. a am I"。

【示例】

```c++
输入: "the sky is blue"
输出: "blue is sky the"
```

```c++
输入: "  hello world!  "
输出: "world! hello"
解释: 输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
```

```c++
输入: "a good   example"
输出: "example good a"
解释: 如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。
```

---

【我的思路—模拟】

核心思路：遍历字符串s，根据空格的位置划分句子中的单词word，将word按照正序存放在words中，再遍历words，将其中单词倒序存入res并输出（注意多个空格和首尾空格的处理）

【我的代码—模拟】

```c++
class Solution {
public:
    string reverseWords(string s) {
        vector<string> words;
        string word;
        bool space_FLAG = false;  //空格的标识符  false：代表这是继前一个字母后第一次出现空格， true：代表这是重复的空格
        for(int i = 0; i < s.length(); i++) {  //遍历字符串s
            if(s[i] == ' ') {  //如果s的第i位为空格
                if (space_FLAG == false) {  //空格第一次出现
                    if(s[i] == ' ' && word.empty()) {  //跳过s首部的空格
                        continue;
                    }
                    space_FLAG = true;  //将空格的标识位置为true，防止下一个连续空格进入此循环
                    words.push_back(word);
                    word.clear();
                }
            }
            else {
                word += s[i];  //拼接word
                space_FLAG = false;
                if(i == s.size() - 1) {  //对最后一个word的特殊处理
                    words.push_back(word);
                    word.clear();
                }
            }
        }
        string res;
        for(int i = words.size() - 1; i >= 0; i--) {  //倒序输出（单词间空格添加）
            res += words[i];
            if(i > 0) {
                res += " ";
            }
        }
        return res;
    }
};
```

优化（移除flag标识位）：

```c++
class Solution {
public:
    string reverseWords(string s) {
        vector<string> words;
        string word;
        for(int i = 0; i < s.length(); i++) {  //遍历字符串s
            if(s[i] == ' ') {  //如果s的第i位为空格
                if(s[i] == ' ' && word.empty()) {  //对连续多个空格的处理
                    continue;
                }
                words.push_back(word);  //将上一个完整的word添加到words中
                word.clear();  //word清空准备接收下一个词
            }
            else {  //s的第i位不为空格
                word += s[i];  //将word进行拼接
                if(i == s.size() - 1) {  //s遍历到末尾时的处理
                    words.push_back(word);
                    word.clear();
                }
            }
        }
        string res;
        for(int i = words.size() - 1; i >= 0; i--) {  //倒序排列word，注意单词之间用空格分隔
            res += words[i];
            if(i > 0) {
                res += " ";
            }
        }
        return res;
    }
};
```

【题解思路1—双指针】

* 使用两个指针left，right来帮助选择每一个单词
* 在每次循环时，先去除所有单词右侧空格，获取某个单词的最右下标`r`，再获取单词的最左下标`l`
* 然后把单词`s.substr(l + 1, r - l)`加入`ret`，别忘了加空格
* 最后要把多余的空格去除`ret.pop_back()`

【题解代码1—双指针】

```c++
class Solution {
public:
    string reverseWords(string s) {
        string res;
        int left, right = s.length() - 1;  //初始化left，right指针
        while(right >= 0) {
            while(right >= 0 && s[right] == ' ') right--;  //去除右边的空格
            if(right < 0) break;  //right到达s左边界时退出循环
            left = right;  //left从right开始往左获得单词的左下标
            while(left >= 0 && s[left] != ' ') left--;
            res += (s.substr(left + 1, right - left) + ' ');  //将left+1开始的right-left个字符（即一个完整单词）加入到res中
            right = left;  //right复位，继续循环 
        }
        if(res.size()) res.pop_back();  //遍历完成后删除最后在res中添加的空格
        return res;
    }
};
```

【题解思路2—字符流法】

利用istringstream对象以空格为分隔符把字符串分开的特性，将分开得到的单词逐一流入字符串word并进行拼接

【题解代码2—字符流法】

```c++
class Solution {
public:
    string reverseWords(string s) {
        string res, word;
        istringstream istr(s);
        while(istr >> word) {
            res = word + ' ' + res;
        }
        return res.substr(0, res.length() - 1);
    }
};
```

【TIPS】

C++字符串流（包含头文件`<sstream>`）：

* istringstream:

  ```c++
  istringstream istr(s);  
  while(istr >> word) {
      cout << word << endl;
  }
  int main() {
      string line, word;
      getline(cin, line);  //获取一行字符赋给line
      istringstream istr(line);  //创建istringstream对象istr同时初始化，使其和字符串line绑定
      while(istr >> word) {
          cout << word << endl;
      }
  }
  //输入: "i love you"
  //输出:
  //          i
  //          love
  //          you
  ```

  istringstream对象可以绑定一行字符串，然后以空格为分隔符把该行分隔开来。

