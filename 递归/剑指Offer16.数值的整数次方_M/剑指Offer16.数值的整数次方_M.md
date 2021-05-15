【题目】

实现 [pow(*x*, *n*)](https://www.cplusplus.com/reference/valarray/pow/) ，即计算 x 的 n 次幂函数（即，xn）。不得使用库函数，同时不需要考虑大数问题。

【示例】

```c++
输入：x = 2.00000, n = 10
输出：1024.00000
```

```c++
输入：x = 2.00000, n = -2
输出：0.25000
解释：2-2 = 1/22 = 1/4 = 0.25
```

---

【[题解思路1—循环](https://leetcode-cn.com/problems/shu-zhi-de-zheng-shu-ci-fang-lcof/solution/zi-jie-ti-ku-jian-16-zhong-deng-shu-zhi-de-zheng-s/)】

循环的实现最容易想到，注意需要把`-n`转换为`long`型，防止溢出：`int`在C++中的范围为`[-2147483648, 2147483647]`，而当n取-2147483648时，-n为2147483648，超出int的范围，因此要用long类型的变量exp暂存-n，再操作exp，但是这种方法会超时。

【题解代码1—循环】

```c++
class Solution {
public:
    double myPow(double x, int n) {
        double res = 1.0;
        if(x == 0.0) return x;  //特殊情况排除
        if(n == 0) return 1.0;  //特殊情况排除
        else if(n > 0) {  //幂大于零
            for(int i = 0; i < n; i++) {
                res *= x;  //求次方
            }
            return res;
        }
        else {  //幂小于零
            long exp = -(long)n;  //防止溢出
            for(int i = 0; i < exp; i++) {
                res *= x;
            }
            res = 1.0 / res;  //幂小于零，求倒数
            return res;
        }
    }
};
```

【[题解思路2—递归](https://leetcode-cn.com/problems/shu-zhi-de-zheng-shu-ci-fang-lcof/solution/jian-zhi-offer-16-shu-zhi-de-zheng-shu-c-tgsi/)】

* n = 0时，任何x都返回1
* n = 1时，返回x
* n = -1时，返回1/x

对于其他n值：

假如我们要求一个数字的32次方，我们已经知道了16次方，那么只要在16次方的基础上再平方一次即可，而16次方是8次方的平方，这样以此类推，我们求32次方只需要5次乘法：先求平方，再在平方的基础上求4次方，在4次方的基础上求8次方->16次方->32次方。

因此可以总结出如下的递推公式：

* 当n为偶数时，`myPow(x,n) = myPow(x,n/2)* myPow(x,n/2)`
* 当n为奇数时：`myPow(x,n) = myPow(x,(n-1)/2) * myPow(x,(n-1)/2) * x`

【题解代码2—递归】

```c++
class Solution {
public:
    double myPow(double x, int n) {
        if(n == 0) return 1;
        if(n == 1) return x;
        if(n == -1) return 1.0 / x;
        if(n % 2 == 0) {  //n为偶数
            double a = myPow(x, n/2);
            return a*a;
        }
        else {  //n为奇数
            double b = myPow(x, (n - 1)/2);
            return b*b*x;
        }
    }
};
```

【[题解思路3—快速幂](https://leetcode-cn.com/problems/shu-zhi-de-zheng-shu-ci-fang-lcof/solution/c-cheng-fa-kuai-su-mi-by-yizhe-shi/)】

`n`的二进制形式一定是由若干0和1构成，例如$x^{9}$，快速幂的思想就是将指数9转换为二进制数：

9 = 1001 = $1*2^3+0*2^2+0*2^1+1*2^0$，则 $x^{9}=x^{1*2^3+0*2^2+0*2^1+1*2^0}=x^{1*2^0}*x^{0*2^1}*x^{0*2^2}*x^{1*2^3}$，看以看出，每次乘以的值都是前一个值的平方，当`n`对应位为0时跳过

【题解代码3—快速幂】

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

【TIPS】：

C++中`int`的取值范围为：`-2147483648 ~ 2147483647`

解释如下：

* int类型在C++中占4个字节，即32个二进制位。
  * 当表示正数时，最高位为符号位（符号位为0），最大的正数是 0111 1111 1111 1111 1111 1111 1111 1111  即2^31 -1 = 2147483647
* 当表示负数时，最高位为符号位（符号位为1），最小的负数是 1000 0000 0000 0000 0000 0000 0000 0000  而在计算机中是以补码的形式存储的，C++规定 1000 0000 0000 0000 0000 0000 0000 0000 的补码为-2147483648
* 所以C++中int的取值范围为：-2147483648 ~ 2147483647

负数的二进制（在计算机中用补码存储）：先得绝对值后的原码->反码（全部取反）->加1（得补码）