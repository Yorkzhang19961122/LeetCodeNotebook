【题目】

输入一个整数 n ，求1～n这n个整数的十进制表示中1出现的次数。

例如，输入12，1～12这些整数中包含1 的数字有1、10、11和12，1一共出现了5次。

【示例】

```c++
输入：n = 12
输出：5
```

```c++
输入：n = 13
输出：6
```

---

【[题解思路—找规律](https://leetcode-cn.com/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof/solution/mian-shi-ti-43-1n-zheng-shu-zhong-1-chu-xian-de-2/)】

标记数字`n`中的低位`low`，当前位`cur`和高位`high`，`digit`记为位因子（个位为1，十位为10...），按照当前位`cur`的大小分为三种情况：

* `cur = 0`时，此位`1`的出现次数只由高位 `high` 决定，计算公式为：`high * digit`
* `cur = 1`时，此位`1`的出现次数由高位 `high` 和低位 `low` 决定，计算公式为：`high * digit + low + 1`
* `cur > 1`时，此位`1`的出现次数只由高位 `high` 决定，计算公式为：`(high + 1) * digit`

【题解代码—找规律】

```c++
class Solution {
public:
    int countDigitOne(int n) {
        long digit = 1;
        int res = 0;
        int high = n / 10, cur = n % 10, low = 0;
        while(high != 0 || cur != 0) {  //当 high 和 cur 同时为 0 时，说明已经越过最高位，因此跳出
            //三种情况
            if(cur == 0) res += high * digit;
            else if(cur == 1) res += high * digit + low + 1;
            else res += (high + 1) * digit;
            //更新四个值
            low += cur * digit;
            cur = high % 10;
            high /= 10;
            digit *= 10;
        }
        return res;
    }
};
```

