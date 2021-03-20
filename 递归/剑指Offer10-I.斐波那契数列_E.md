【题目】

写一个函数，输入 `n` ，求斐波那契（Fibonacci）数列的第 `n` 项（即 `F(N)`）。斐波那契数列的定义如下：

```c++
F(0) = 0,   F(1) = 1
F(N) = F(N - 1) + F(N - 2), 其中 N > 1.
```

斐波那契数列由 0 和 1 开始，之后的斐波那契数就是由之前的两数相加而得出。

答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。

【示例】

```c++
输入：n = 5
输出：5
```

---

【我的思路—递归】

常规思路

【我的代码—递归】

```c++
class Solution {
public:
    int fib(int n) {
        if(n == 0) return 0;
        if(n == 1) return 1;
        return (fib(n - 1) + fib(n -2))%1000000007;
    }
};
```

思路没错，只是每次计算fib(n)时都会重复计算，造成大量时间浪费，因此可以进行优化。

【题解思路1—递归+哈希表】

在递归时，利用一个哈希表把计算过的fib值存入，从而减少重复运算。

【题解代码1—递归+哈希表】

```c++
class Solution {
public:
    unordered_map<int, int> map;  //创建哈希表存放fib函数计算值
    int recursion(int n){
        //递归边界条件
        if(n == 0) return 0;
        else if(n == 1) return 1;
        else if(map.count(n)) return map[n];  //如果表map中存在n的fib值，则直接返回即可
        //否则就根据fib(n)=fib(n-1)+fib(n-2)计算fib值，并且存到哈希表中
        int a = recursion(n - 1)%1000000007;
        map[n - 1] = a;
        int b = recursion(n - 2)%1000000007;
        map[n - 2] = b;
        map[n] = (a + b)%1000000007;
        return map[n];
    }
    int fib(int n) {
        return recursion(n);
    }
};
```

【题解代码2—DP】

* 1.当i=0的时候，dp[i]=0;当i=1时，dp[i]=1，确定初始条件
* 2.根据方程迭代dp[i]=dp[i-1]+dp[i-2]

【题解代码2—DP】

```c++
class Solution {
public:
    int fib(int n) {
        vector<int> dp;
        for(int i = 0; i <= n; i++){
            //初始条件
            if(i == 0) dp.push_back(0);
            else if(i == 1) dp.push_back(1);
            //动态方程
            else dp.push_back((dp[i - 1] + dp[i - 2])%1000000007);
        }
        return dp[n];
    }
};
```

