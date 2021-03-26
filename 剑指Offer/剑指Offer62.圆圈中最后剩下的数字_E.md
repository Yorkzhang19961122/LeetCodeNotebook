【题目】

0,1,···,n-1这n个数字排成一个圆圈，从数字0开始，每次从这个圆圈里删除第m个数字（删除后从下一个数字开始计数）。求出这个圆圈里剩下的最后一个数字。

例如，0、1、2、3、4这5个数字组成一个圆圈，从数字0开始每次删除第3个数字，则删除的前4个数字依次是2、0、4、1，因此最后剩下的数字是3。

【示例】

```c++
输入: n = 5, m = 3
输出: 3
```

---

【题解思路1—链表模拟】

使用list模拟题意，遍历list，每过m-1步删除指针指向的元素，若指针指向list.end()，则重新指向list.begin()，以此达到环形的效果

【题解代码1—链表模拟】

```c++
class Solution {
public:
    int lastRemaining(int n, int m) {
        list<int> li;
        for(int i = 0; i < n; i++) {  //循环将0到n-1添加到列表li中
            li.push_back(i);
        }
        auto cur_iter = li.begin();  //cur指针指向li的首部
        while(li.size() > 1) {  //若li不为空，则一直遍历li
            for(int i = 1; i < m; i++) {  //cur指针前进m-1步
                cur_iter++;
                if(cur_iter == li.end()) cur_iter = li.begin();  //如果cur指针指向li.end()，则cur重新指向li.begin()
            }
            //定位到需要删除的元素后
            cur_iter++;  //cur指针后移
            auto next_iter = cur_iter;  //next指针为后移后的cur
            if(next_iter == li.end()) next_iter = li.begin();  //同样，如果next指针到末尾了，则重新指向begin
            cur_iter--;  //cur指针回到原来应该删除元素的位置
            li.erase(cur_iter);  //删除cur指针指向的元素
            cur_iter = next_iter;  //防止cur指针为空
        }
        return *cur_iter;  //全部遍历结束后，cur指向的元素就是最终剩下的，或返回li.front()也可以
    }
};
```

【题解思路2—模拟优化】

使用取模的方法，优化思路1中的代码，避免用for循环找待删除的元素

【题解代码2—模拟优化】

```c++
class Solution {
public:
    int lastRemaining(int n, int m) {
        list<int> li;
        for(int i = 0; i < n; i++) {
            li.push_back(i);
        }
        //使用取模的方法避免遍历寻找待删除的元素
        int rmidx = 0;  //待删除元素的索引
        while(li.size() > 1) {
            auto rm_iter = li.begin();  //rm_iter每次都回到li的起点
            rmidx = (rmidx + m - 1)%li.size();  //计算得到的rmidx表示当前链表中，待删除元素为rm_iter向后移动rmidx后所指向的
            advance(rm_iter, rmidx);  //移动迭代器rm_iter，rmidx个单位
            li.erase(rm_iter);  //删除此时的指向
        }
        return li.front();
    }
};
```

【题解思路3—数学】

推导过程见[此题解](https://leetcode-cn.com/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/solution/javajie-jue-yue-se-fu-huan-wen-ti-gao-su-ni-wei-sh/)

【题解代码3—数学】

```c++
class Solution {
public:
    int lastRemaining(int n, int m) {
        int ans = 0;
        for(int i = 2; i <= n; i++) {  //从2开始反推
            ans = (ans + m) % i;
        }
        return ans;
    }
};
```



【TIPS】

C++ STL之list：

* [常用list操作](https://blog.csdn.net/fanyun_01/article/details/56881515)

* [reference查询](http://www.cplusplus.com/reference/list/list/)