【题目】

如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。

例如，

[2,3,4] 的中位数是 3

[2,3] 的中位数是 (2 + 3) / 2 = 2.5

设计一个支持以下两种操作的数据结构：

* `void addNum(int num)` - 从数据流中添加一个整数到数据结构中。
* `double findMedian()` - 返回目前所有元素的中位数。

【示例】

```c++
输入：
["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]
[[],[1],[2],[],[3],[]]
输出：[null,null,null,1.50000,null,2.00000]
```

```c++
输入：
["MedianFinder","addNum","findMedian","addNum","findMedian"]
[[],[2],[],[3],[]]
输出：[null,null,2.00000,null,2.50000]
```

---

【题解思路—堆】

使用大小顶堆`maxHeap`和`minHeap`，分别存储列表的一半元素，其中：

* 大顶堆存储列表中较小的一半元素，则其堆顶的元素靠近中位数
* 小顶堆存储列表中较大的一半元素，则其堆顶的元素靠近中位数

中位数可以根据两个堆的堆顶元素计算得到：

* 如果两个堆中元素个数相同，中位数就等于两个堆顶元素的平均数
* 如果两个堆顶元素的个数不相同，中位数就等于元素数量较多那个堆的堆顶元素（和刚开始的元素插入顺序有关，具体看代码）

【题解代码—堆】

```c++
class MedianFinder {
public:
    /** initialize your data structure here. */
    //maxHeap大顶堆(存放将数字序列排序后较小的一半，这样堆顶元素就是较小元素中最大的，靠近中位数)
    priority_queue<int, vector<int>, less<int>> maxHeap;
    //minHeap小顶堆(存放将数字序列排序后较大的一半，这样堆顶元素就是较大元素中最小的，靠近中位数)
    priority_queue<int, vector<int>, greater<int>> minHeap;
    MedianFinder() {
    }
    
    void addNum(int num) {
        if(maxHeap.size() == minHeap.size()) {  //如果大小顶堆元素个数相同
            //经过大顶堆将元素放到小顶堆后（这里先放到哪个堆都可以，区别在于最后返回的不同）
            maxHeap.push(num);
            int top = maxHeap.top();
            maxHeap.pop();
            minHeap.push(top);  
        }
        else {  //如果大小顶堆的元素个数不相同
            //将元素放到小顶堆后，取小顶堆的堆顶元素放到大顶堆中
            minHeap.push(num);
            int top = minHeap.top();
            minHeap.pop();
            maxHeap.push(top);
        }
    }
    
    double findMedian() {
        if(maxHeap.size() == minHeap.size()) {
            return (maxHeap.top() + minHeap.top()) * 1.0 / 2.0; //大小顶堆元素相同，则返回两个堆顶元素的平均值即可
        }
        else {
            return minHeap.top() * 1.0; //先经过大顶堆将元素放到小顶堆，因此这里返回小顶堆的堆顶元素（否则返回大顶堆的堆顶元素）
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
```

**时间复杂度**：

* 查找中位数：O(1)，获取堆顶元素
* 添加数字O(logN)：堆的插入和弹出操作的时间

**空间复杂度**：O(N)，N为数据流中的元素数量