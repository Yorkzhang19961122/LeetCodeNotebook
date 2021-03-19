【题目】

输入整数数组 `arr` ，找出其中最小的 `k` 个数。例如，输入4、5、1、6、2、7、3、8这8个数字，则最小的4个数字是1、2、3、4。

【示例】

```c++
输入：arr = [3,2,1], k = 2
输出：[1,2] 或者 [2,1]
```

---

【我的思路—sort排序】

直接使用sort函数对arr数组进行升序排列，取最小的k个数存入res即可

【我的代码—sort排序】

```c++
class Solution {
public:
    //升序排列
    static bool SortByMe(int a, int b){
        return a < b;
    }
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int> res;
        sort(arr.begin(), arr.end(), SortByMe);
        for(int i = 0; i < k; i++){
            res.push_back(arr[i]);
        }
        return res;
    }
};
```

sort默认是升序的，故此处可以不借助第三个参数控制升序，下面是降序排列的代码，此处需要手动控制sort进行降序排列：

```c++
class Solution {
public:
    //降序排列
    static bool SortByMe(int a, int b){
        return a > b;
    }
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int> res;
        sort(arr.begin(), arr.end(), SortByMe);
        int a = arr.size() - 1;
        int b = arr.size() - k;
        for(int i = a; i >= b; --i){
            res.push_back(arr[i]);
        }
        return res;
    }
};
```

【题解思路1—堆排序】

我们用一个大根堆实时维护数组的前 k 小值。首先将前 k 个数插入大根堆中，随后从第k+1 个数开始遍历，如果当前遍历到的数比大根堆的堆顶的数要小，就把堆顶的数弹出，再插入当前遍历到的数。最后将大根堆里的数存入数组返回即可。在下面的代码中，由于 C++ 语言中的堆（即优先队列）为大根堆，我们可以这么做

【题解代码1—堆排序】

```c++
class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int> res (k, 0);
        if(k == 0) return res;
        priority_queue<int> Q;  //初始化大顶堆（堆顶是此时堆中的最大值）
        for(int i = 0; i < k; i++){  //将k个元素放到堆Q中
            Q.push(arr[i]);
        }
        for(int i = k; i < arr.size(); i++){  //将剩下的元素一个个与大顶堆顶元素比较大小，如果小于Q顶元素，则Q顶元素弹出，并将新元素放到Q中
            if(Q.top() > arr[i]){
                Q.pop();
                Q.push(arr[i]);
            }
        }
        for(int i = 0; i < k; i++){  //遍历结束后，堆Q中就是最小的k个元素
            res[i] = Q.top();
            Q.pop();
        }
        return res;
    }
};
```

时间复杂度：O(nlogk)，其中 n是数组 arr 的长度。由于大根堆实时维护前 k小值，所以插入删除都是O(logk) 的时间复杂度，最坏情况下数组里 n 个数都会插入，所以一共需要O(nlogk) 的时间复杂度。

空间复杂度：O(k)，大根堆里最多k个数

【题解思路2—快速排序】



【题解代码2—快速排序】

```

```

【TIPS】

**1、priority_queue（优先队列）：**

它是有二项队列编写而成的，可以以**O(log n)** 的效率查找一个队列中的最大值或者最小值。

其声明形式为：

```c++
priority_queue< type, container, function >
// 其中第一个参数不能省略
```

* type：数据类型

* container：实现优先队列的底层容器

  要求必须是**数组形式实现的容器**，例如vector、deque，而不能使用list，默认是**vector**

* function：元素之间的比较方式

  默认是一个**最大堆**，每次输出的堆顶元素是此时堆中的最大值

**大顶堆的构造：**

```c++
//构造一个空的优先队列（此优先队列默认为大顶堆）
priority_queue<int> big_heap;   

#include<functional>
//另一种构建大顶堆的方法
priority_queue<int,vector<int>,less<int> > big_heap2;   
```

**小顶堆的构造：**

```c++
#include<functional>
//构造一个空的优先队列,此优先队列是一个小顶堆
priority_queue<int,vector<int>,greater<int> > small_heap;   
```

**2、快速排序（quick sort）：**

原理见[该链接](https://blog.csdn.net/qq_28584889/article/details/88136498)。

时间复杂度：最差O(N^2)，平均时间复杂度O(NlogN)