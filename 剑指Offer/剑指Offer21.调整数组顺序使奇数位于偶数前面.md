【题目】

输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有奇数位于数组的前半部分，所有偶数位于数组的后半部分。

【示例】

```c++
输入：nums = [1,2,3,4]
输出：[1,3,2,4] 
注：[3,1,2,4] 也是正确的答案之一。
```

---

【我的思路—遍历+奇偶分组】

遍历nums，奇数添加到odd数组中，偶数添加到even数组中，再分别遍历odd和even数组，将奇偶数按顺序添加到res中，得到最后的结果

【我的代码—遍历+奇偶分组】

```c++
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        vector<int> even;
        vector<int> odd;
        vector<int> res;
        for(int i = 0; i < nums.size(); i++) {  //遍历nums
            if(nums[i] % 2 == 0) even.push_back(nums[i]);
            else odd.push_back(nums[i]);
        }
        for(int i = 0; i < odd.size(); i++) {  //遍历奇数数组
            res.push_back(odd[i]);
        }
        for(int i = 0; i < even.size(); i++) {  //遍历偶数数组
            res.push_back(even[i]);
        }
        return res;
    }
};
```

【题解思路1—首尾双指针】

定义双指针left，right分别指向数组左右两端，循环执行：

1. left从左向右寻找偶数
2. right从右向左寻找奇数
3. 将偶数nums[left]和奇数nums[right]交换

【题解代码1—首尾双指针】

```c++
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;  //左找偶数，右找奇数
        while(left < right) {
            while(left < right && nums[left] % 2 == 1) {  //left从左边找偶数
                left++;
            }
            while(left < right && nums[right] % 2 == 0) {  //right从右边找奇数
                right --;
            }
            swap(nums[left], nums[right]);  //交换left和right指向的数字
        }
        return nums;
    }
};
```

【题解思路2—快慢双指针】

定义快慢指针slow和fast，fast用于寻找奇数，slow则指向下一个奇数应该存放的位置，每到fast指向奇数时，就交换slow和fast指向的元素，直到fast到达nums末尾。

【题解代码2—快慢双指针】

```c++
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int slow = 0, fast = 0;  //slow找偶，fast找奇，找到的话交换，达到奇在前，偶在后
        while(fast < nums.size()) {
            if(nums[fast] % 2 == 1) {  //fast找到奇数
                swap(nums[slow], nums[fast]);  //交换slow和fast指向的元素
                slow++;  //一旦交换过slow和fast，说明当前的slow一定指向奇数，那么slow后移，用于指向下一个奇数应当存放的位置
            }
            fast++;  //找不到奇数则后移
        }
        return nums;
    }
};
```

