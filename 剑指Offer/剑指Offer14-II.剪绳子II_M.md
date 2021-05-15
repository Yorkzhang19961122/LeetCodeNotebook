【题目】

给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 `k[0],k[1]...k[m - 1]` 。请问 `k[0]*k[1]*...*k[m - 1]` 可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。

答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。

**注意**：`2 <= n <= 1000`，需要考虑大数问题（本题除大数问题外与[剑指 Offer 14- I. 剪绳子](https://leetcode-cn.com/problems/jian-sheng-zi-lcof/)相同/[题解](https://github.com/Yorkzhang19961122/LeetCodeNotebook/blob/main/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92/%E5%89%91%E6%8C%87Offer14-I.%E5%89%AA%E7%BB%B3%E5%AD%90_M.md)）

【示例】

```c++
输入: 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36
```

---

【题解思路1—贪心算法（循环取余）】

与14-I不同，由于出现了大数取余（导致取余后无法再使用max函数来比大小了，比如取余后 `2000000014`会小于 `1000000020`），所以DP算法在本题中无法使用，故使用贪心，多了一个每步取余的操作

【题解代码1—贪心算法（循环取余）】

```c++
class Solution {
public:
    int cuttingRope(int n) {
        long res = 1;
        if(n < 4) return n - 1;
        if(n == 4) return 4;
        while(n > 4) {
            n -= 3;
            res = res * 3 % 1000000007;  //每步取余
        }
        return (int)res * n % 1000000007;
    }
};
```

【题解思路2—贪心算法（快速幂）】

思路仍然为贪心，但使用快速幂代替循环取余，快速幂是在循环取余的基础上，进一步降低时间复杂度，快速幂的题目见[链接](https://leetcode-cn.com/problems/powx-n/)

【题解代码2—贪心算法（快速幂）】

在使用快速幂之前，我们首先将常规使用`pow`函数进行幂运算的解法写一下（也就是[剪绳子I](https://github.com/Yorkzhang19961122/LeetCodeNotebook/blob/main/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92/%E5%89%91%E6%8C%87Offer14-I.%E5%89%AA%E7%BB%B3%E5%AD%90_M.md)中的代码加上取模）：

```c++
class Solution {
public:
    int cuttingRope(int n) {
        if(n < 4) return n - 1;  //n等于2、3的情况先处理
        int a = n / 3;  
        int b = n % 3;  //n除以3的余数，只可能有0，1，2三种情况
        if(b == 0) return pow(3, a);  //余数为0
        if(b == 1) return pow(3, a - 1) * 4;  //余数为1，最后一个3和余数1不切，直接乘以4
        return pow(3, a) * 2;  //余数为2
    }
};
```

`pow`函数在大数时会越界，因此