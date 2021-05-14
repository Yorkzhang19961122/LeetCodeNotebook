【题目】

数字以0123456789101112131415…的格式序列化到一个字符序列中。在这个序列中，第5位（从下标0开始计数）是5，第13位是1，第19位是4，等等。

请写一个函数，求任意第n位对应的数字。

【示例】

```c++
输入：n = 3
输出：3
```

```c++
输入：n = 11
输出：0
```

【[题解思路](https://leetcode-cn.com/problems/shu-zi-xu-lie-zhong-mou-yi-wei-de-shu-zi-lcof/solution/mian-shi-ti-44-shu-zi-xu-lie-zhong-mou-yi-wei-de-6/)】

题目的意思就是在0123456789101112131415...的数字序列中找到给定位置n的数字

用`digit`表示数字的位数（例如3位数`digit` = 3），`start`表示`digit`位数的第一个数字（`digit=1`时，`start=1`， `digit=2`时，`start=10`），`count`表示所有`digit`位数所占的位数

【题解思路】

```c++
class Solution {
public:
    int findNthDigit(int n) {
        long long digit = 1;  //数字位数(例如三位数digit=3)
        int start = 1;  //digit位数的第一个数字  
        long long count = 9 * digit * start;  //所有digit位数所占的位数
        while(n > count) {  //1.确定n所在的数字的位数digit
            n -= count;
            digit++;
            start *= 10;
            count = 9 * digit * start;
        }
        //2. 确定n所在的数字num
        //此时n的值是相对于start的位置
        int num = start + (n - 1) / digit;
        //3. 确定n是num的第几位
        string s = to_string(num);
        int res = s[(n - 1) % digit] - '0';
        return res;
    }
};
```

