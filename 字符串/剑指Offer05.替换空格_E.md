【题目】

请实现一个函数，把字符串 `s` 中的每个空格替换成"%20"。

【示例】

```c++
输入：s = "We are happy."
输出："We%20are%20happy."
```

---

【我的思路—遍历添加】

创建空字符串result，遍历字符串s，当前字符为空格时，result添加"%20"，当前字符串非空格时，直接将当前字符串添加到result中，遍历完成后返回result。

【我的代码—遍历添加】

```c++
class Solution {
public:
    string replaceSpace(string s) {
        string result;  //创建空字符串result
        int size = s.size();
        for(int i = 0; i < s.size(); ++i){  //遍历字符串s
            if(s[i] != ' '){
                result += s[i];  //如果s[i]不是空格，将s[i]直接添加进result中
            }
            if(s[i] == ' '){  //如果s[i]是空格，将”%20“添加进result
                result.append("%20");
            }
        }
        return result;
    }
};
```

【题解思路—原地修改】

* 初始化：空格数量 count ，字符串 s 的长度 len ；
* 统计空格数量：遍历 s ，遇空格则 count++ ；
* 修改 s 长度：添加完 "%20" 后的字符串长度应为 len + 2 * count ；
* 倒序遍历修改：i 指向原字符串尾部元素， j 指向新字符串尾部元素；当 i = j 时跳出（代表左方已没有空格，无需继续遍历）；
  * 当 s[i] 不为空格时：执行 s[j] = s[i] ；
  * 当 s[i] 为空格时：将字符串闭区间 [j-2, j] 的元素修改为 "%20" ；由于修改了 3 个元素，因此需要 j -= 2 。
* 返回值：已修改的字符串 s ；

【题解代码—原地修改】

```c++
class Solution {
public:
    string replaceSpace(string s) {
        int len = s.size(), count = 0;
        //遍历s找到空格的数量count
        for(auto ch : s){
            if(ch == ' ') count++;
        }
        s.resize(len + 2*count);  //改变s的空间
        //利用双指针i，j倒序遍历s
        for(int i = len - 1, j = s.size() - 1; i < j; i--, j--){
            if(s[i] != ' '){
                s[j] = s[i];
            }
            else{
                s[j - 2] = '%';
                s[j - 1] = '2';
                s[j] = '0';
                j -= 2;
            }
        }
        return s;
    }
};
```

【直接利用库函数replace】

```c++
class Solution {
public:
    string replaceSpace(string s) {
        int pos = s.find(" ");  //查找空格在目前字符串中的位置，找不到返回-1
        while(pos != -1){
            s.replace(pos, 1, "%20");  //将字符串中以某个位置开始的指定长度替换为目前字符串
            pos = s.find(" ");
        }
        return s;
    }
};C
```

