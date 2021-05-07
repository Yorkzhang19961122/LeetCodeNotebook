【题目】

给定一个数字，我们按照如下规则把它翻译为字符串：0 翻译成 “a” ，1 翻译成 “b”，……，11 翻译成 “l”，……，25 翻译成 “z”。一个数字可能有多个翻译。请编程实现一个函数，用来计算一个数字有多少种不同的翻译方法。

【示例】

```c++
输入: 12258
输出: 5
解释: 12258有5种不同的翻译，分别是"bccfi", "bwfi", "bczi", "mcfi"和"mzi"
```

---

【题解思路1—动态规划】

我们用`dp[i]`来表示前`i`个数字的翻译方法数，对于第`i`个数字，我们有两种翻译的选择：

* 只翻译自己
* 和前面的数字进行组合翻译，前提是组合后的数字大小需要在`[10, 25]`之间，否则被视为无效

此处可以联想到[青蛙跳台阶的问题](https://github.com/Yorkzhang19961122/LeetCodeNotebook/blob/main/%E9%80%92%E5%BD%92/%E5%89%91%E6%8C%87Offer10-II.%E9%9D%92%E8%9B%99%E8%B7%B3%E5%8F%B0%E9%98%B6%E9%97%AE%E9%A2%98_E.md)，只是对于不同的数字组合，转移方程的形式有所不同：

$$ dp(i)=\left\{
\begin{array}{rcl}
dp(i-2) + dp(i-1)       &      & {i前面两个数组合后的大小在[10,25]之间，\\说明前两位数字除了各自单独翻译外，还可以组合翻译，\\类似于青蛙跳2级和1级台阶}\\
dp(i-1)     &      & {否则}\\
\end{array} \right. $$

初始化*无数字*和*1位数字*的翻译方法均为`1`.

最后返回`dp[n]`即是该`num`的翻译方案数量

【题解代码1—动态规划】

```c++
class Solution {
public:
    int translateNum(int num) {
        string num_str = to_string(num);  //将num转为string
        vector<int> dp(num_str.size() + 1);
        dp[0] = 1;  //初始化
        dp[1] = 1;
        for(int i = 2; i < num_str.size() + 1; i++) {  //遍历num
            if(num_str.substr(i-2, 2) >= "10" && num_str.substr(i-2, 2) <= "25") {  //判断i-2和i-1位置的数字能否进行组合，使用了substr方法取到连续的两个数字
                dp[i] = dp[i - 1] + dp[i - 2];
            }
            else {
                dp[i] = dp[i - 1];
            }
        }
        return dp[num_str.size()];  //返回num的不同翻译方案数量
    }
};
```

对于取连续的数字组合，还有别的方法，例如`char`类型的字符减去`'0'`后得到它的`int`类型：

```c++
int n = (num_str[i - 2] - '0') * 10 + (num_str[i - 1] - '0');
if(n >= 10 && n <= 25) {  //判断i-2和i-1位置的数字能否进行组合
    dp[i] = dp[i - 1] + dp[i - 2];
}
```

对于动态规划，可以采用滚动数组(`abc`)进行空间上的优化，将使用`dp`数组产生的`O(N)`空间复杂度降至`O(1)`，但本题由于使用额外的空间存储数字`num`转化成的字符串，所以优化后总体的空间复杂度仍然没有变：

```c++
class Solution {
public:
    int translateNum(int num) {
        string num_str = to_string(num);
        //a:f(i-2), b:f(i-1), c:f(i)
        int a = 1, b = 1;  
        int c = 0;
        for(int i = 2; i < num_str.size() + 1; i++) {
            if(num_str.substr(i - 2, 2) >= "10" && num_str.substr(i - 2, 2) <= "25") {
                c = a + b;
            }
            else {
                c = b;  
            }
            a = b;  //f(i-2) = f(i-1) bc平移到ab
            b = c;  //f(i-1) = f(i) 只利用三个整数动态存放各个位置的翻译方案之和，画一下更好理解
        }
        return b;
    }
};
```

