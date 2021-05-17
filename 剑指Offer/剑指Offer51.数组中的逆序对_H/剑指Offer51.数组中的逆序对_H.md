【题目】

在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。

【示例】

```c++
输入: [7,5,6,4]
输出: 5
```

---

【我的思路—暴力】

两重循环判断逆序对个数，O(N^2)很显然会超时，然而本菜鸡只能想到暴力

【我的代码—暴力】

```c++
class Solution {
public:
    int reversePairs(vector<int>& nums) {
        int count = 0;
        for(int i = 0; i < nums.size(); i++) {
            for(int j = i; j < nums.size(); j++) {
                if(nums[i] > nums[j]) count++; 
            }
        }
        return count;
    }
};
```

【[题解思路—归并排序](https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/solution/jian-zhi-offer-51-shu-zu-zhong-de-ni-xu-pvn2h/)】

知识盲区—归并排序，学习一下：

归并排序体现了**分而治之**的思想。

* 不断将数组从中点位置划分开（即二分法），将整个数组的排序问题转化为子数组的排序问题
* 划分到子数组长度为 1 时，开始向上合并，不断将 **较短*排序*数组** 合并为 **较长*排序*数组**，直至合并至原数组时完成排序

总体思路见下图：

![](https://github.com/Yorkzhang19961122/LeetCodeNotebook/blob/main/%E5%89%91%E6%8C%87Offer/%E5%89%91%E6%8C%87Offer51.%E6%95%B0%E7%BB%84%E4%B8%AD%E7%9A%84%E9%80%86%E5%BA%8F%E5%AF%B9_H/02.png)

归并排序的代码如下（升序排列一个数组）：

```c++
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        vector<int> copy(nums);  //拷贝构造一个新数组copy，为了不改变原数组nums
        mergeSort(copy, 0, nums.size() - 1);
        return copy;
    }

    void mergeSort(vector<int>& copy, int left, int right) {
        int mid = left + (right - left) / 2;  //找中间点
        if(left < right) {
            mergeSort(copy, left, mid);  //递归划分左子数组
            mergeSort(copy, mid + 1, right);  //递归划分右子数组
            mergeTwoArray(copy, left, mid, right);  //合并已经排序的子数组
        }
    }

    void mergeTwoArray(vector<int>& copy, int left, int mid, int right) {
        vector<int> temp(right - left + 1, 0);  //temp数组用来存放排序后的结果
        int l_pos = left, r_pos = mid + 1;  //l_pos指向左有序数组的第一个元素，r_pos指向右有序数组的第一个元素
        int index = 0;
        while(l_pos <= mid && r_pos <= right) {  //合并两个有序数组到temp中
            if(copy[l_pos] < copy[r_pos]) {
                temp[index++] = copy[l_pos++];
            }
            else {
                temp[index++] = copy[r_pos++];
            }
        }
        //把左子数组剩余的数移入temp数组
        while(l_pos <= mid) {
            temp[index++] = copy[l_pos++];
        }
        //把右子数组剩余的数移入temp数组
        while(r_pos <= right) {
            temp[index++] = copy[r_pos++];
        }
        //将辅助数组temp中的元素覆盖原copy数组
        for(int i = 0; i < temp.size(); i++) {
            copy[i + left] = temp[i];
        }
    }
};
```

在本题中，求逆序数组和归并排序的关系在于：

所有的逆序对来源于左边区间，右边区间和横跨两个区间，而合并阶段本质上是 合并两个**排序**数组 的过程，每当遇到 左子数组当前元素 大于 右子数组当前元素 时，意味着 「左子数组当前元素 至 末尾元素」 与 「右子数组当前元素」 构成了若干 「逆序对」

例如：

```  C++ 
2 3 6 7 | 0 1 4 5   //左右两个子数组都是有序的
^         ^
i         j
```

当`i`指向2，`j`指向0时，说明左子数组所有的元素都与`j`指向的元素构成了逆序对，而这种关系在归并排序中很容易计算得到，如下图：

![](https://github.com/Yorkzhang19961122/LeetCodeNotebook/blob/main/%E5%89%91%E6%8C%87Offer/%E5%89%91%E6%8C%87Offer51.%E6%95%B0%E7%BB%84%E4%B8%AD%E7%9A%84%E9%80%86%E5%BA%8F%E5%AF%B9_H/01.png)

【题解代码—归并排序】

```C++
class Solution {
public:
    int count = 0;
    int reversePairs(vector<int>& nums) {
        vector<int> copy(nums);  //不修改原数组，拷贝构造nums
        int len = copy.size();
        if(len < 2) return 0;  //长度为2不构成逆序对
        mergeSort(copy, 0, len - 1);
        return count;
    }
    void mergeSort(vector<int>& copy, int left, int right) {
        int mid = left + (right - left) / 2;
        if(left < right) {
            mergeSort(copy, left, mid);  //递归划分左半区
            mergeSort(copy, mid + 1, right);  //递归划分右半区
            mergeTwoArray(copy, left, mid, right);  //合并两个有序数组
        }
    }
    //合并两个有序数组到
    void mergeTwoArray(vector<int>& copy, int left, int mid, int right) {
        vector<int> temp(right - left + 1, 0);  //temp存储排序后的结果
        int l_pos = left, r_pos = mid + 1;  //l_pos指向左有序数组的首部，r_pos指向右有序数组的首部
        int index = 0;
        while(l_pos <= mid && r_pos <= right) {  //比较l_pos和r_pos指向的元素值大小
            if(copy[l_pos] <= copy[r_pos]) {
                temp[index++] = copy[l_pos++];  
            }
            else {  
                temp[index++] = copy[r_pos++];
                count += (mid - l_pos + 1);  //若copy[l_pos]>copy[r_pos]，则l_pos到mid之间的元素都和r_pos位置的元素形成逆序对，统计逆序对数量count
            }
        }
        //把左子数组剩余的元素添加到temp中
        while(l_pos <= mid) {
            temp[index++] = copy[l_pos++];
        }
        //把右子数组剩余的元素添加到temp中
        while(r_pos <= right) {
            temp[index++] = copy[r_pos++];
        }
        //辅助数组temp中的元素覆盖原copy数组对应的位置
        for(int i = 0; i < temp.size(); i++) {
            copy[i + left] = temp[i];
        }
    }
};
```

