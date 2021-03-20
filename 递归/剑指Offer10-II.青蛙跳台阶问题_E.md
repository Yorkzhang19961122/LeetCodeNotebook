【题目】

一只青蛙一次可以跳上1级台阶，也可以跳上2级台阶。求该青蛙跳上一个 n 级的台阶总共有多少种跳法。

答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。

【示例】

```c++
输入：n = 7
输出：21
```

---

【我的思路—DP】

和[斐波那契数列题目](https://github.com/Yorkzhang19961122/LeetCodeNotebook/blob/main/%E9%80%92%E5%BD%92/%E5%89%91%E6%8C%87Offer10-I.%E6%96%90%E6%B3%A2%E9%82%A3%E5%A5%91%E6%95%B0%E5%88%97_E.md)一样，只不过初值有变化。

【我的代码—DP】

```c++
class Solution {
public:
    int numWays(int n) {
        vector<int> dp;
        for(int i = 0; i <= n; i++){
            if(i == 0) dp.push_back(1);  //n=0时，初值为1
            else if(i == 1) dp.push_back(1);
            else dp.push_back((dp[i - 1] + dp[i - 2])%1000000007);
        }
        return dp[n];
    }
};
```

