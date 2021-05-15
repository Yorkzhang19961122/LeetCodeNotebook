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

与剑指Offer14-I不同，由于出现了大数取余（导致取余后无法再使用max函数来比大小了，比如取余后 `2000000014`会小于 `1000000020`），所以DP算法在本题中无法使用，故使用贪心，多了一个每步取余的操作

【题解代码1—贪心算法（循环取余）】

```c++
class Solution {
public:
    int cuttingRope(int n) {
        long res = 1;
        if(n < 4) return n - 1;  //特殊情况
        if(n == 4) return 4;
        while(n > 4) {
            n -= 3;  //循环减3
            res = res * 3 % 1000000007;  //res循环乘3，每步取余
        }
        return (int)res * n % 1000000007;  //最后返回时乘以小于等于4的最后一小段
    }
};
```

【题解思路2—贪心算法（快速幂）】

思路仍然为贪心，但使用快速幂（在快速幂的内部进行大数处理）代替循环取余，快速幂是在循环取余的基础上，进一步降低时间复杂度，快速幂的题目见[剑指 Offer 16. 数值的整数次方](https://leetcode-cn.com/problems/shu-zhi-de-zheng-shu-ci-fang-lcof/)和[50. Pow(x, n)](https://leetcode-cn.com/problems/powx-n/)

【题解代码2—贪心算法（快速幂）】

在使用快速幂之前，我们首先将常规使用`pow`函数进行幂运算的解法写一下（也就是[剪绳子I](https://github.com/Yorkzhang19961122/LeetCodeNotebook/blob/main/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92/%E5%89%91%E6%8C%87Offer14-I.%E5%89%AA%E7%BB%B3%E5%AD%90_M.md)中的代码加上取模）：

```c++
class Solution {
public:
    int cuttingRope(int n) {
        if(n < 4) return n - 1;  //n等于2、3的情况先处理
        int a = n / 3;  
        int b = n % 3;  //n除以3的余数，只可能有0，1，2三种情况
        if(b == 0) return ((long)pow(3, a)) % 1000000007;  //余数为0
        if(b == 1) return ((long)pow(3, a - 1)) * 4 % 1000000007;  //余数为1，最后一个3和余数1之间不切，直接乘以4
        return ((long)pow(3, a)) * 2 % 1000000007;  //余数为2
    }
};
```

这样直接`pow`后取模是错误的，因为`pow`函数在大数时会越界，理由如下：

* C++内置的`pow`函数[返回值](http://www.cplusplus.com/reference/cmath/pow/?kw=pow)为`double`类型，而`double`类型无法直接取余`1000000007`，故要将`double`类型转为整形`(int或long)`才能进行取余操作，而在大数情况下，`pow`的计算结果已经超过了整形`(int和long)`的范围，导致转换出错，问题就出在这一步类型转换上，所以不能使用系统内置的`pow`函数进行幂运算，而要自己实现`pow`函数，在实现过程中处理溢出的问题，故使用快速幂实现`pow`函数

回顾一下常规快速幂的思路：

![](https://github.com/Yorkzhang19961122/LeetCodeNotebook/blob/main/%E5%89%91%E6%8C%87Offer/%E5%89%91%E6%8C%87Offer14-II.%E5%89%AA%E7%BB%B3%E5%AD%90II_M/01.png)

```c++
class Solution {
public:
    double myPow(double x, int n) {
        if(x == 0) return x;  //0的n次方等于0(n > 0)
        long exp = n;  //防止n小于零且等于-2^31时，取相反数会超出int的范围(-2^31, 2^31 - 1)，因此将n事先存到long类型的exp中
        if(n < 0) {
            exp = -exp;
            x = 1 / x;  //当指数小于零时，实际上是对倒数求幂运算: x^-n = (1/x)^n
        }
        double res = 1.0;
        while(exp) {
            if((exp & 1) == 1) res *= x;  //当前位为0时跳过
            x *= x;  
            exp >>= 1;   //右移判断下一位
        }
        return res;
    }
};
```

再回到本题，首先不需要考虑指数小于零的情况，且在进行计算时，要处理大数的问题（即取模1e9+7），代码如下：

```c++
class Solution {
public:
    int cuttingRope(int n) {
        if(n < 4) return n - 1;  //n等于2、3的情况先处理
        int a = n / 3;
        int b = n % 3;  //n除以3的余数，只可能有0，1，2三种情况
        if(b == 0) return (int)(myPow(3, a) % 1000000007);  //余数为0
        if(b == 1) return (int)(myPow(3, a - 1) * 4 % 1000000007);  //余数为1，最后一个3和余数1之间不切，直接乘以4
        return (int)(myPow(3, a) * 2 % 1000000007);  //余数为2
    }
    //快速幂
    long myPow(long base, int exp) {
        long res = 1;
        while(exp > 0) {
            if((exp & 1) == 1) res = res * base % 1000000007;
            base = base * base % 1000000007;
            exp >>= 1;
        }
        return res;
    }
};
```

