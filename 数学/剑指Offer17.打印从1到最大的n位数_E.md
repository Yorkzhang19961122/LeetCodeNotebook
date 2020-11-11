【题目】

输入数字 n，按顺序打印出从 1 到最大的 n 位十进制数。比如输入 3，则打印出 1、2、3 一直到最大的 3 位数 999。

【示例】

> 输入: n = 1  
> 输出: [1,2,3,4,5,6,7,8,9]

---

【我的思路】

最大的n位十进制数有10^n-1个（从1开始），因此循环添加到向量ans中即可

【我的代码】

```c++
class Solution {
public:
    vector<int> printNumbers(int n) {
        vector<int> ans;
        for(int i = 1; i < pow(10,n); ++i){
            ans.push_back(i);
        }
        return ans;
    }
};
```

【TODO】

在这一题中，由于返回的是一个 int 型的数组，所以是不可能超过INT_MAX的，但是一般**大数问题**都不会要求返回 int 数组来保存每一位数，而是循环输出每一位数。当n很大的时候（如100），打印出来的范围可能超过`INT_MAX`，所以要考虑使用字符串来表示每个数。

思路为：假设n=3，就定义一个字符串，初始化为‘000’，然后用它来循环模拟从1到最大的n位数，并循环保存到int数组中（真实情况中往往是循环输出）

```c++
class Solution {
public:
    vector<int> output;
    vector<int> printNumbers(int n) {
        //以下注释的前提：假设n=3
        /*定义一个字符串初始化为‘000’*/
		string s(n, '0');  //直接初始化为n个0
        /*循环模拟从1到最大的n位数，保存到int数组中*/
        while(!overflow(s)){  //如果s没有越界
            inputNumbers(s);  //将s添加到output中用于输出
        }
        return output;
    }
    /*本函数用于模拟数字累加的过程，并且判断是否越界（999+1=1000就是越界情况）*/
    bool overflow(string& s){
        bool isOverFlow = false;
        int carry = 0;  //carry表示进位
        for(int i = s.length() - 1; i >= 0; --i){  //遍历，从个位(...1,0)开始
            int current = s[i] - '0' + carry;  //s[i]-'0'可以将s的第i位转化为int型参与运算
            if(i == s.length() - 1){  //如果此时i在s的个位，则current加1
                current++;
            }
            if(current == 10){  //如果i已经在最大的那一位了，而current++之后==10，说明循环到头了，即999+1=1000
                if(i == 0){
                    isOverFlow = true;
                }
                else{  //只是普通进位，比如current从9变成10
                    carry = 1;
                    s[i] = current - 10 + '0';  //+'0'转换成char
                }
            }
            else{
                s[i] = current + '0';  //如果没有进位，更新s[i]的值，然后直接跳出循环，返回执行inputNumber函数
                break;
            }
        }
        return isOverFlow;
    }
    /*本函数用于循环往output中添加符合传统阅读习惯的元素，如001，我们会添加1*/
    void inputNumbers(string s){
        output.push_back(stoi(s));
    }
};
```

