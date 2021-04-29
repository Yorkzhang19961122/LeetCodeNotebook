【题目】

给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 `k[0],k[1]...k[m-1]` 。请问 `k[0]*k[1]*...*k[m-1] `可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。

【示例】

```
输入: 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36
```

---

【[题解思路1—动态规划](https://leetcode-cn.com/problems/jian-sheng-zi-lcof/solution/jian-zhi-offer-14-i-jian-sheng-zi-huan-s-xopj/)】

* 我们想要求长度为`n`的绳子剪掉后的最大乘积，可以从前面比`n`小的绳子转移而来
* 用一个`dp`数组记录从`0`到`n`长度的绳子剪掉后的最大乘积，也就是`dp[i]`表示长度为`i`的绳子剪成`m`段后的最大乘积，初始化`dp[2] = 1`
* 我们先把绳子剪掉第一段（长度为`j`），如果只剪掉长度为`1`，对最后的乘积无任何增益，所以从长度为`2`开始剪
* 剪了第一段后，剩下`(i - j)`长度可以剪也可以不剪。如果不剪的话长度乘积即为`j * (i - j)`；如果剪的话长度乘积即为`j * dp[i - j]`。取两者最大值`max(j * (i - j), j * dp[i - j])`
* 第一段长度`j`可以取的区间为`[2,i)`，对所有`j`不同的情况取最大值，因此最终`dp[i]`的转移方程为
  `dp[i] = max(dp[i], max(j * (i - j), j * dp[i - j]))`
* 最后返回`dp[n]`即可

【题解代码1—动态规划】

```c++
class Solution {
public:
    int cuttingRope(int n) {
        vector<int> dp(n + 1, 0);
        dp[2] = 1;
        for(int i = 3; i < n + 1; i++) {  
            for(int j = 2; j < i; j++) {
                dp[i] = max(dp[i], max(j * (i - j), j * dp[i - j]));  //得到绳子长度为i时的最大乘积
            }
        }
        return dp[n];
    }
};
```

【[题解思路2—贪心算法](https://leetcode-cn.com/problems/jian-sheng-zi-lcof/solution/mian-shi-ti-14-i-jian-sheng-zi-tan-xin-si-xiang-by/)】

经过数学推论，可得两个推论：

* 将绳子**以相等的长度等分成多段**，得到的乘积最大
* 尽可能将绳子以**长度为3**等分为多段时，乘积最大，当剩下的绳子长度为4时，剪成两段长度为2的绳子

【题解代码2—贪心算法】

```c++
class Solution {
public:
    int cuttingRope(int n) {
        if(n <= 3) return n - 1;  //n等于2，3的特殊值
        int a = n / 3, b = n % 3;  //a为n除3的商，b为余数
        if(b == 0) return pow(3, a);  //余数为0时，都切为3可以使乘积最大
        if(b == 1) return pow(3, a - 1) * 4;  //余数为1时，最后的(3+1)切成2*2
        return pow(3, a) * 2;  //余数为2时，不能再切了，直接乘2即可
    }
};
```

