【题目】

给定一个数组 `A[0,1,…,n-1]`，请构建一个数组 `B[0,1,…,n-1]`，其中 `B[i] `的值是数组 `A `中除了下标 `i `以外的元素的积, 即 `B[i]=A[0]×A[1]×…×A[i-1]×A[i+1]×…×A[n-1]`。不能使用除法。

【示例】

```c++
输入: [1,2,3,4,5]
输出: [120,60,40,30,24]
```

---

【题解思路—分别计算每个位置的左右乘积后再相乘】

分别计算每个数字左右两边各元素的乘积`left`和`right`，最后将`left`和`right`相乘得到每个位置除该位置元素外所有元素的乘积

【题解代码—分别计算每个位置的左右乘积后再相乘】

```c++
class Solution {
public:
    vector<int> constructArr(vector<int>& a) {
        if(a.size() == 0) return a;
        int size = a.size();
        int left[size];  //left存储左边各元素的乘积
        int right[size];  //right存储右边各元素的乘积
        left[0] = 1;  //a中首元素的左边没有其他元素，故left[0]记为1
        right[size - 1] = 1;  //a中尾元素的右边没有其他元素，故right[size - 1]记为1
        for(int i = 1; i < size; i++) {  //遍历a，计算第i个元素左边各元素的乘积，注意使用i的前一个元素左边各元素乘积left[i-1]乘以a[i-1]得到a中不包括i的左边各元素乘积
            left[i] = left[i - 1] * a[i - 1];
        }
        for(int i = size - 2; i >= 0; i--) {  //遍历b，计算每个元素右边各元素的乘积，计算思路同left
            right[i] = right[i + 1] * a[i + 1];
        }
        vector<int> B(size, 0);
        for(int i = 0; i < size; i++) {  //分别将left和right对应元素相乘，得到结果
            B[i] = left[i] * right[i];
        }
        return B;
    }
};
```

上面的代码利用了3个for循环，可以将后面两个for循环合并，代码如下：

```c++
class Solution {
public:
    vector<int> constructArr(vector<int>& a) {
        if(a.size() == 0) return a;
        int size = a.size();
        vector<int> B(size, 1);  //初始化数组B用于中途计算与结果存储
        B[0] = 1;  //B先用来存储当前位置左边元素的乘积
        for(int i = 1; i < size; i++) {  //遍历a，计算a中第i个位置（从下标1开始）左边的元素之积，其中显然B[0]为1
            B[i] = B[i - 1] * a[i - 1];
        }
        int right = 1;  //right保存当前元素右边所有元素的乘积
        for(int i = size - 1; i >= 0; i--) {  //此时B[i]中保存的就是当前位置左边各元素的乘积，与right相称更新B[i]即可
            B[i] *= right;
            right *= a[i];  //更新right
        }
        return B;
    }
};
```

