【题目】

写一个函数 StrToInt，实现把字符串转换成整数这个功能。不能使用 atoi 或者其他类似的库函数。

首先，该函数会根据需要丢弃无用的开头空格字符，直到寻找到第一个非空格的字符为止。

当我们寻找到的第一个非空字符为正或者负号时，则将该符号与之后面尽可能多的连续数字组合起来，作为该整数的正负号；假如第一个非空字符是数字，则直接将其与之后连续的数字字符组合起来，形成整数。

该字符串除了有效的整数部分之后也可能会存在多余的字符，这些字符可以被忽略，它们对于函数不应该造成影响。

注意：假如该字符串中的第一个非空格字符不是一个有效整数字符、字符串为空或字符串仅包含空白字符时，则你的函数不需要进行转换。

在任何情况下，若函数不能进行有效的转换时，请返回 0。

说明：

* 假设我们的环境只能存储 32 位大小的有符号整数，那么其数值范围为 `[−2^31,  2^31 − 1]`。如果数值超过这个范围，请返回  `INT_MAX` (2^31 − 1) 或 `INT_MIN` (−2^31) 。

【示例】

```c++
输入: "   -42"
输出: -42
解释: 第一个非空白字符为 '-', 它是一个负号。
     我们尽可能将负号与后面所有连续出现的数字组合起来，最后得到 -42 。
```

```c++
输入: "-91283472332"
输出: -2147483648
解释: 数字 "-91283472332" 超过 32 位有符号整数范围。 
     因此返回 INT_MIN (−231) 。
```

---

【我的思路—模拟】

1. 过滤空格
2. 记录正负号
3. 遍历有效的数字，并将结果累加入res
4. 将res乘以正负号，判断是否超出边界(INT_MAX, INT_MIN)
5. 返回结果

【我的代码—模拟】

```c++
class Solution {
public:
    int strToInt(string str) {
        if(str.size() == 0) return 0;  //空字串直接返回0
        int index = 0;  //索引0从str的第一个字符开始
        while(str[index] == ' ') {  //先过滤首部的空格
            index++;
            if(index == str.size()) return 0;  //如果str全为空格，则返回0
        }
        int sign = 1, sign_cnt = 0;  //sign记录正负号，sign_cnt判断正负号出现的次数（针对类似+-24的用例）
        while(str[index] == '+' || str[index] == '-') {
            if(str[index] == '+') {
                sign = 1;
                sign_cnt++;
            }
            else if(str[index] == '-') {
                sign = -1;
                sign_cnt++;
            }
            index++;
            if(index == str.size() || sign_cnt > 1) return 0;  //如果正负号超过1个或者str只含有正负号，返回0
        }
        stack<int> stk;  //用栈存储有效的数字
        for(int i = index; i < str.size(); i++) {
            if(str[i] - '0' < 0 || str[i] - '0' > 9) break;  //遍历正负号后紧接的str直至遇到非数字
            stk.push(str[i] - '0');
        }
        double res = 0;
        double mul = 1;
        while(!stk.empty()) {  //遍历栈，累加结果到res中
            res = res + stk.top() * mul;
            stk.pop();
            mul *= 10;
        }
        //最后结果越界的处理
        if(sign * res > INT_MAX) return INT_MAX;
        if(sign * res < INT_MIN) return INT_MIN;
        return (int)sign * res;
    }
};
```

参考题解代码，并不需要使用额外的栈来辅助，**直接原地就可以累加**，代码优化如下：

```c++
class Solution {
public:
    int strToInt(string str) {
        if(str.size() == 0) return 0;  //空字串直接返回0
        int index = 0;  //索引0从str的第一个字符开始
        while(str[index] == ' ') {  //先过滤首部的空格
            index++;
            if(index == str.size()) return 0;  //如果str全为空格，则返回0
        }
        int sign = 1, sign_cnt = 0;  //sign记录正负号，sign_cnt判断正负号出现的次数（针对类似+-24的用例）
        while(str[index] == '+' || str[index] == '-') {
            if(str[index] == '+') {
                sign = 1;
                sign_cnt++;
            }
            else if(str[index] == '-') {
                sign = -1;
                sign_cnt++;
            }
            index++;
            if(index == str.size() || sign_cnt > 1) return 0;  //如果正负号超过1个或者str只含有正负号，返回0
        }
        double res = 0;
        for(int i = index; i < str.size(); i++) {
            if(str[i] - '0' < 0 || str[i] - '0' > 9) break;  //遍历正负号后紧接的str直至遇到非数字
            res = res * 10 + (str[i] - '0');  //原地累加（从前往后很巧妙，值得学习）
        }
        //最后结果越界的处理
        if(sign * res > INT_MAX) return INT_MAX;
        if(sign * res < INT_MIN) return INT_MIN;
        return (int)sign * res;
    }
};
```

