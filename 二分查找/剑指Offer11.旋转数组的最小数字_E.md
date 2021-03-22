【题目】

把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。例如，数组 `[3,4,5,1,2]` 为 `[1,2,3,4,5]` 的一个旋转，该数组的最小值为1。  

【示例】

```c++
输入：[3,4,5,1,2]
输出：1
```

---

【题解思路—二分法】

**初始化**：声明left，right双指针分别指向nums数组的左右两端

**循环二分**：设mid=left+(right-left)/2，可以分为三种情况：

* 1.当nums[mid] > nums[right]时：mid一定在左排序数组中，即旋转点一定在[mid+1, right]闭区间内，此时执行left=mid+1
* 2.当nums[mid] < nums[right]时，mid一定在右排序数组中，即旋转点一定在[left, mid]闭区间内，此时执行right=mid
* 3.当nums[mid] = nums[right]时，无法判断旋转点在[left,m]还是[m+1,right]区间中，此时执行right--缩小判断范围

【题解代码—二分法】

```c++
class Solution {
public:
    int minArray(vector<int>& numbers) {
        int left = 0;
        int right = numbers.size() - 1;
        while(left < right) {
            int mid = left + (right - left) / 2;
            if(numbers[mid] > numbers[right]) left = mid + 1;  //nums[mid] > nums[right]
            else if(numbers[mid] < numbers[right]) right = mid;  //nums[mid] < nums[right]
            else if(numbers[mid] == numbers[right]) right--;  //nums[mid] == nums[right]
        }
        return numbers[left];  //二分查找结束，left=right，返回nums[left]
    }
};
```

