【题目】

我们把只包含质因子 2、3 和 5 的数称作丑数（Ugly Number）。求按从小到大的顺序的第 n 个丑数。

**说明**：

1. 1是丑数
2. n不超过1690

【示例】

```c++
输入: n = 10
输出: 12
解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。
```

---

【[题解思路1—暴力](https://leetcode-cn.com/problems/chou-shu-lcof/solution/jian-zhi-49chou-shu-bao-li-xiao-ding-dui-fhab/)】

逐个判断每一个数字是否为丑数，注意丑数大于零，且只能被2，3，5整除，然而这种方法是超时的。

【题解代码1—暴力】

```c++
class Solution {
public:

    bool isUgly(int x) {
        vector<int> factors = {2, 3, 5};
        for(int factor : factors) {  //判断一个数字是否为丑数的逻辑
            while(x % factor == 0) {  //注意这里的while，易写成if
                x /= factor;
            }
        }
        return x == 1 ? true : false;
    }
    int nthUglyNumber(int n) {
        int x = 1, count = 0;
        while(true) {
            if(isUgly(x)) {  //count用于统计丑数的个数
                count++;
            }
            x++;
            if(count == n) return x-1;
        }
    }
};
```

【[题解思路2—小顶堆](https://leetcode-cn.com/problems/chou-shu-lcof/solution/chou-shu-by-leetcode-solution-0e5i/)】

思路1中的方法时间复杂度高，原因是对每一个数字都进行了判断，而实际上我们可以通过对数字乘以`2、3、5`得到新的丑数，再返回第`n`个丑数即可。

* 初始化一个`priority_queue`，将最小的丑数`1`加入堆中
* 每次取出堆顶元素x（即堆中最小的丑数），再将`2x、3x、5x`加入堆
* 为了避免重复，使用哈希集合去重。避免相同的元素多次加入堆
* 在排除重复元素的情况下，第n次从最小堆中取出的元素即为第`n`个丑数

【题解代码2—小顶堆】

```c++
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> factors = {2, 3, 5};  //factors存储丑数的因子
        priority_queue<long, vector<long>, greater<long>> Heap; //初始化小顶堆heap
        unordered_set<long> Set;  //初始化set用于去重
        Heap.push(1);  //将最小的丑数1加入set和heap中
        Set.insert(1);
        int ugly = 0;
        for(int i = 0; i < n; i++) {  //n次后的ugly就是从小到大的第n个丑数
            long cur = Heap.top();  //cur为当前堆中最小的丑数
            Heap.pop();
            ugly = cur;
            for(int factor : factors) {  //计算cur*2/*3/*5后的丑数
                long next = factor * cur;
                if(Set.count(next) == 0) {  //在set中查找是否有重复，将不重复的丑数添加到set和heap中，不去重的话，heap中的重复丑数会被计算多次
                    Set.insert(next);
                    Heap.push(next);
                }
            }
        }
        return ugly;
    }
};
```

【[题解思路3—动态规划+三指针](https://leetcode-cn.com/problems/chou-shu-lcof/solution/chou-shu-ii-qing-xi-de-tui-dao-si-lu-by-mrsate/)】

一个丑数乘以2、3、3后一定还是丑数，所以题解的思路就是：用三个数组分别存储丑数1乘以2、3、5后的序列，那么最终的丑数序列就是对这三个有序序列进行合并的结果，注意实际代码中这三个数组是隐含的。

合并三个数组的方法：每个数组维护一个指针，比较指针指向的元素的值，将最小的元素放入最终的合并数组中，并将相应的指针往后移动一个元素（注意使用三个`if`，这样使得当某一时刻某些子数组中的值相同时，这些数组的指针都能同时后移，避免了重复）。

【题解代码3—动态规划+三指针】

```c++
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> dp(n, 0);  //dp用于存放最后的丑数数组
        dp[0] = 1;  //将1存入dp
        int p1 = 0, p2 = 0, p3 = 0;  //初始化三个指针p1,p2,p3
        for(int i = 1; i < n; i++) {  //循环n-1次
            dp[i] = min(min(dp[p1]*2, dp[p2]*3), dp[p3]*5);  //取出此时三个数组中的最小值存入dp中
            //使用三个if是为了防止重复，在出现重复时，对应数组的指针都可以后移
            if(dp[i] == dp[p1]*2) {  //如果取出的数字dp[i]等于dp[p1]*2(理解为三个子数组中某个数组内对应的值)，则其对应的指针后移
                p1++;
            }
            if(dp[i] == dp[p2]*3) {
                p2++;
            }
            if(dp[i] == dp[p3]*5) {
                p3++;
            }                        
        }
        return dp[n - 1];
    }
};
```

