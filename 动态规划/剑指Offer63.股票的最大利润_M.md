【题目】

假设把某股票的价格按照时间先后顺序存储在数组中，请问买卖该股票一次可能获得的最大利润是多少？

【示例】

```c++
输入: [7,1,5,3,6,4]
输出: 5
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格。
```

```c++
输入: [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
```

---

【我的思路—单次遍历维护最小值】

维护一个保存当前股票最小值的变量min和保存当前最大利润的数组profit，遍历数组，更新min和profit，遍历结束后返回profit中的最大值即可。

【我的代码—单次遍历维护最小值】

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size() == 0) return 0;  //空数组处理
        int min = prices[0];
        vector<int> profit;
        for(int i = 0; i < prices.size(); i++) {  //遍历数组prices
            if(prices[i] < min) min = prices[i];  //更新min
            profit.push_back(prices[i] - min);  //将当前位置股票价格prices[i]能取得的最大利润存入profit中
        }
        return *max_element(profit.begin(), profit.end());  //返回profit中的最大值
    }
};
```

【题解代码—动态规划】

创建数组`dp`，`dp[i]`代表前`i`天的最大利润，那么前`i`天的最大利润可以表示为`dp[i] = max(dp[i - 1], (prices[i] - min))`，这个式子即为转移方程，最后确定初始值`dp[0] = 0`，遍历完数组`prices`后返回`dp`的最后一个元素即为最大的利润。

【题解代码—动态规划】

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size() == 0) return 0;
        int dp[prices.size()];
        dp[0] = 0;  //初始化
        int min = prices[0];  //初始化最小值min
        for(int i = 1; i < prices.size(); i++) {  //遍历数组prices
            if(prices[i] < min) min = prices[i];  //更新最小值
            dp[i] = max(dp[i - 1], prices[i] - min);  //转移方程
        }
        return dp[prices.size() - 1];  
    }
};
```

以上代码可以进行优化，前`i`天的最低价格可以动态更新，记为成本`cost`，因此不必再使用`if(prices[i] < min) min = prices[i];`来处理最小值，而是使用`cost = min[cost, price]`来更新最低价格，而获得前`i`天的最大利润可以借助一个变量`profit`来动态更新，即优化为：`profit = max(profit, price - cost);`，最后返回`profit`即可，优化后的代码为：

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size() == 0) return 0;
        int cost = prices[0];
        int profit = 0;
        for(int price : prices) {  //遍历prices
            cost = min(price, cost);  //cost更新目前最低的价格
            profit = max(profit, price - cost);  //profit更新目前最大的利润
        }
        return profit;
    }
};
```

