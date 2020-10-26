【题目】

字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。请定义一个函数实现字符串左旋转操作的功能。比如，输入字符串"abcdefg"和数字2，该函数将返回左旋转两位得到的结果"cdefgab"。

【示例】

>输入: s = "abcdefg", k = 2  
输出: "cdefgab"

---

【我的思路】

新建字符串res，再使用`substr()`函数保存不需要旋转的子串，然后遍历原字符串s，使用`push_back()`函数将需要旋转的字符按顺序放置到res末尾

【我的代码】

```c++
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        string res = s.substr(n);  //取出串s中不需要旋转的子串
        for(int i = 0; i < n; i++){  //遍历原串s
            res.push_back(s[i]);  //将需要旋转的n位字符放置到res的末尾
        }
        return res;
    }
};
```

使用`substr()`会申请额外的空间，空间复杂度为O(n)，时间复杂度为O(n)，本题若想要O(1)的空间复杂度，则可以使用反转字符串的方法：

【题解思路】

不申请额外的空间，只在本串上操作，通过局部反转+整体反转达到左旋的目的，例如：

输入`s = abcdefg`，`n=2`，那么

![左旋字符串](https://github.com/Yorkzhang19961122/LeetCodeNotebook/blob/main/%E5%AD%97%E7%AC%A6%E4%B8%B2/%E5%89%91%E6%8C%87Offer58-II.%E5%B7%A6%E6%97%8B%E8%BD%AC%E5%AD%97%E7%AC%A6%E4%B8%B2_E/%E5%89%91%E6%8C%87Offer58-II.%E5%B7%A6%E6%97%8B%E8%BD%AC%E5%AD%97%E7%AC%A6%E4%B8%B2_E.png)

【题解代码】

```c++
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        reverse(s.begin(), s.begin()+n);  //反转前n位
        reverse(s.begin()+n, s.end());  //反转n到末尾的字串
        reverse(s.begin(), s.end());  //反转整个字符串
        return s;
    }
};
```

【Tips】

1. `reverse()`函数 

reverse函数功能是逆序（或反转），多用于字符串、数组、容器。头文件是`#include <algorithm>`

reverse函数用于反转在[first,last)范围内的顺序（包括first指向的元素，不包括last指向的元素），reverse函数无返回值，例如：

```c++
string str="hello world , hi";
reverse(str.begin(),str.end());//str结果为 ih , dlrow olleh
vector<int> v = {5,4,3,2,1};
reverse(v.begin(),v.end());//容器v的值变为1,2,3,4,5
```

2. `substr()`方法

一种构造string的方法，形式为`s.substr(pos, n)`，返回一个string，包含s中从pos开始的n个字符的拷贝（pos的默认值是0，n的默认值是`s.size()-pos`，即不加参数会默认拷贝整个s）

注意若pos的值超过了string的大小，则substr会抛出一个`out_of_range`异常，若`pos+n`的值超过了string的大小，则substr会调整n的值，只拷贝到string的末尾

例如：

```c++
string s("12345asdf");
string a = s.substr(0, 5);  //则 a=12345
```

