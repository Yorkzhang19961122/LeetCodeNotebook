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

**时间复杂度**：O(nlogk)，其中 n是数组 arr 的长度。由于大根堆实时维护前 k小值，所以插入删除都是O(logk) 的时间复杂度，最坏情况下数组里 n 个数都会插入，所以一共需要O(nlogk) 的时间复杂度。

**空间复杂度**：O(k)，大根堆里最多k个数

【题解思路2—快速排序】

手写快排对arr**整个数组**进行排序，再遍历排序后的arr，取出前k个最小值返回即可。

【题解代码2—快速排序】

```c++
class Solution {
public:
    //快速排序算法
    void quickSort(int left, int right, vector<int> & arr) {
        if(left >= right) return;
        int i, j, base, temp;
        i = left;
        j = right;
        base = arr[left];
        while(i < j) {
            while(arr[j] >= base && i < j) {
                j--;
            }
            while(arr[i] <= base && i < j) {
                i++;
            }
            if(i < j) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        arr[left] = arr[i];
        arr[i] = base;
        quickSort(left, i - 1, arr);
        quickSort(i + 1, right, arr);
    }
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        quickSort(0, arr.size() - 1, arr);  //对arr快排
        vector<int> res;
        for(int i = 0; i < k; i++) {  //遍历排序后的arr
            res.push_back(arr[i]);
        }
        return res;
    }
};
```

**时间复杂度**：O(NlogN)

**空间复杂度**：O(N)，快排平均为O(logN)，最差为O(N)

由于本题只需要知道前k个最小值，对这k个数的顺序并没有要求，只需要将数组划分为 **最小的 k 个数** 和 **其他数字** 两部分即可，而快速排序的哨兵划分可完成此目标。

根据快速排序原理，如果某次哨兵划分后 基准数正好是第 k+1 小的数字 ，那么此时基准数左边的所有数字便是题目所求的 最小的 k 个数 。

根据此思路，考虑在每次哨兵划分后，判断基准数在数组中的索引是否等于 k ，若 true 则直接返回此时数组的前 k 个数字即可。

```c++
class Solution {
public:
    vector<int> quickSortMinK(int left, int right, int & k ,vector<int> & arr) {
        int i  = left, j = right;
        while(i < j) {
            while(arr[j] >= arr[left] && i < j) j--;
            while(arr[i] <= arr[left] && i < j) i++;
            swap(arr[i], arr[j]); 
        }
        swap(arr[left], arr[i]);
        if(i > k) return quickSortMinK(left, i - 1, k, arr);  //若k<i，代表第k + 1小的数字在左子数组中，则递归左子数组
        if(i < k) return quickSortMinK(i + 1, right, k, arr);  //若k>i，代表第k + 1小的数字在右子数组中，则递归右子数组
        //若k = i，代表此时 arr[k] 即为第k + 1小的数字，则直接返回数组前k个数字即可
        vector<int> res;
        res.assign(arr.begin(), arr.begin() + k);
        return res;
    }
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        if(k >= arr.size()) return arr;
        return quickSortMinK(0, arr.size() - 1, k, arr);
    }
};
```

【**TIPS**】

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

快排模板（由小到大）：

```c++
void quickSort(int left, int right, vector<int> &arr) {
	if(left >= right) return;  //递归终止条件
    int i = left;
    int j = right;
    int base = arr[left];  //取数组最左元素为base，则先让j左移，再让i右移
    int temp;
    while(i < j) {
        while(arr[j] >= base && i < j) {  //j左移找比base小的元素
            j--;
        }
        while(arr[i] <= base && i < j) {  //i右移找比base大的元素
            i++;
        }
        if(i < j) {
            //arr[i]和arr[j]满足条件则交换
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;            
        }
    }
    //直至i、j相遇
    //base归位
    arr[left] = arr[i];
    arr[i] = base;
    
    quickSort(left, i - 1, arr);  //递归左边子列
    quickSort(i + 1, right, arr);  //递归右边子列
}
```

代码简化（由小到大）：

```c++
    void quickSort(int left, int right, vector<int> & arr) {
        if(left >= right) return;  //子数组长度为1时递归终止
        int i, j;
        i = left;
        j = right;
        while(i < j) {
            while(arr[j] >= arr[left] && i < j) {  //以arr[left]为基准数
                j--;
            }
            while(arr[i] <= arr[left] && i < j) {
                i++;
            }
            swap(arr[i], arr[j]);
        }
        swap(arr[left], arr[i]);
        //递归左右数组
        quickSort(left, i - 1, arr);
        quickSort(i + 1, right, arr);
    }
```

由大到小（稍稍改动）：

```c++
void quickSort(int left, int right, vector<int> &arr) {
	if(left >= right) return;  //递归终止条件
    int i = left;
    int j = right;
    int base = arr[left];  //取数组最左元素为base，则先让j左移，再让i右移
    int temp;
    while(i < j) {
        while(arr[j] <= base && i < j) {  //j左移找比base大的元素
            j--;
        }
        while(arr[i] >= base && i < j) {  //i右移找比base小的元素
            i++;
        }
        if(i < j) {
            //arr[i]和arr[j]满足条件则交换
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;            
        }
    }
    //直至i、j相遇
    //base归位
    arr[left] = arr[i];
    arr[i] = base;
    
    quickSort(left, i - 1, arr);  //递归左边子列
    quickSort(i + 1, right, arr);  //递归右边子列
}
```

代码简化（由大到小）：

```c++
    void quickSort(int left, int right, vector<int> & arr) {
        if(left >= right) return;  //子数组长度为1时递归终止
        int i, j;
        i = left;
        j = right;
        while(i < j) {
            while(arr[j] <= arr[left] && i < j) {  //以arr[left]为基准数
                j--;
            }
            while(arr[i] >= arr[left] && i < j) {
                i++;
            }
            swap(arr[i], arr[j]);
        }
        swap(arr[left], arr[i]);
        //递归左右数组
        quickSort(left, i - 1, arr);
        quickSort(i + 1, right, arr);
    }
```

