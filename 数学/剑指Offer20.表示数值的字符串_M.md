【题目】

请实现一个函数用来判断字符串是否表示**数值**（包括整数和小数）。

**数值**（按顺序）可以分成以下几个部分：

1. 若干空格
2. 一个 **小数** 或者 **整数**
3. （可选）一个 `'e'` 或`'E'` ，后面跟着一个 **整数**
4. 若干空格

**小数**（按顺序）可以分成以下几个部分：

1. （可选）一个符号字符（`'+'` 或 `'-'`）
2. 下述格式之一：
   1. 至少一位数字，后面跟着一个点 `'.'`
   2. 至少一位数字，后面跟着一个点 `'.'` ，后面再跟着至少一位数字
   3. 一个点 `'.'` ，后面跟着至少一位数字

**整数**（按顺序）可以分成以下几个部分：

1. （可选）一个符号字符（`'+'` 或 `'-'`）
2. 至少一位数字

部分**数值**列举如下：

`["+100", "5e2", "-123", "3.1416", "-1E-16", "0123"]`
部分**非数值**列举如下：

`["12e", "1a3.14", "1.2.3", "+-5", "12e+5.4"]`

【示例】

```c++
输入：s = "0"
输出：true
```

```c++
输入：s = "    .1  "
输出：true
```

```c++
输入：s = "e"
输出：false
```

---

【[题解思路—模拟](https://leetcode-cn.com/problems/biao-shi-shu-zhi-de-zi-fu-chuan-lcof/solution/mian-shi-ti-20-biao-shi-shu-zhi-de-zi-fu-chuan-y-2/)】

从头往后遍历处理，遇到不同的情况进行特殊处理，直接看代码，思路清晰

【题解代码—模拟】

```c++
class Solution {
public:
    //数字可能有A[.[B]][e|EC]或者.B[e|EC]来表示
    //其中A和C都可能有正负号，而B则没有正负号（无符号整数）
    bool isNumber(string s) {
        if(s.size() == 0) return false;  //s为空则直接返回false
        int index = 0;  //index指示当前遍历的下标
        while(s[index] == ' ') {  //筛除s最前面的空格
            index++;
        }
        //此处的numeric表示去除最前面空格后，紧跟着的字符是否为整数
        //有小数点的话就是小数点前的数字，没有的话就是e或E前的数字，两者都没有的话就是整个数字
        bool numeric = isInteger(s, index);  
        if(s[index] == '.') {  //如果出现'.'，接下来是小数部分
            ++index;
            //1.小数可以没有整数部分（小数点前的部分），.123等于0.123
            //2.小数点后可以没有数字，233.等于233.0
            //3.小数点前和后都有数字，1.234
            //4.所以此处用||
            //注意此处的顺序，要先让index到小数点后面去进行判断
            //否则小数点前面的numeric==true就已经让整体为true了，而index还没有动，导致最后indx不等于s.size()，参考用例"0.8"
            numeric = isUnsignedInteger(s, index) || numeric; //小数点后的数字是否为无符号整数||小数点前的字符是否合规
        }
        if(s[index] == 'e' || s[index] == 'E') {  //如果出现'e'或'E'，接下来的数字是指数部分
            index++;
            //1.若e或E前没有数字则不合规，例如.e1，e2
            //2.若e或E后没有数字或不为整数则不合规，例如12e，12e+5.4
            //3.所以此处用&&
            numeric = numeric && isInteger(s, index); //e或E前的字符是否合规&&e或E后是否为整数
        }
        while(s[index] == ' ') {  //滤去最后的空格
            ++index;
        }
        return numeric && index == s.size();  //只有上述几步都合规，此时的numeric才为true，并且遍历完s所有的字符
    }
    
    bool isInteger(string s, int& index) {
        if(s[index] == '+' || s[index] == '-') {  //可能有正负号，滤去
            index++;
        }
        return isUnsignedInteger(s, index);  //接下来没有正负号的字符可以进行无符号整型的判断
    }

    bool isUnsignedInteger(string s, int& index) {
        int before = index;  //before标记处理前的下标位置
        while(index != s.size() && s[index] >= '0' && s[index] <= '9') {  //index对应的字符是数字且未超出边界
            index++;
        }
        return index > before;  //处理后的当前下标index大于处理前的当前下标before，则说明before至index为整数
    }
};
```

