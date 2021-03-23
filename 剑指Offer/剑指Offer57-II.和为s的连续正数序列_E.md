【题目】

输入一个正整数 target ，输出所有和为 target 的连续正整数序列（至少含有两个数）。

序列内的数字由小到大排列，不同序列按照首个数字从小到大排列。

【示例】

```c++
输入：target = 15
输出：[[1,2,3,4,5],[4,5,6],[7,8]]
```

```c++
输入：target = 9
输出：[[2,3,4],[4,5]]
```

---

【我的思路—遍历】

两重循环遍历1到target，第一重循环i控制连续正整数的头，第二重循环j控制连续正整数的尾，每次将j累加到sum中，同时将j添加到temp数组中，直到sum等于target，则将此时的temp放入res中，如果sum大于target而未满足sum等于target时，说明以此时的i为头，不可能使连续数字和为target，那么提前终止内层循环。并且每次移动连续数字的头时，temp都需要清空。

【我的代码—遍历】

```c++
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>> res;  //存放最终的答案
        vector<int> temp;  //存放中间数组
        for(int i = 1; i <= target; i++) {  //外层循环i控制连续数字的头
            temp.clear();  //清空temp，为本次循环做准备
            int sum = i;  //先将连续数字的头i赋给sum，为接下来的累加做准备
            temp.push_back(i);  //同理，将i放到temp中
            for(int j = i + 1; j <= target; j++) {  //内层循环i用于控制连续数字的尾
                sum += j;  //累加j，sum就代表了以i为头，j为尾时连续整数的累加和
                temp.push_back(j);  //每次都将j添加到temp中
                if(sum == target) {  //如果某个j时，sum等于target，表明此时temp中的数组就是满足要求的
                    res.push_back(temp);
                }
                else if(sum > target) {  //如果sum大于target而未满足条件，则说明以此i为头的连续整数和不会再满足要求，因此退出第二层循环
                    break;
                }               
            }
        }
        return res;  //全部遍历结束后，将res返回
    }
};
```

【题解思路1—数学计算法】

根据连续整数累加和的求和公式（梯形的面积公式），得到起始为i，结束为j时的连续整数累加和target=((i+j)(j-i+1))/2，已知i时，解得此一元二次方程，j=(-1+sqrt(1+4*(i^2-i+2target)))/2，此时通过从小到大遍历左边界i来计算sum值，根据题意，当满足j为整数（连续整数），且i<j时（至少含有两个数），满足题目要求，从而将i到j添加进结果数组即可。

【题解代码1—数学计算法】

```c++
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>> res;
        int i = 1;
        double j = 2.0;
        while(i < j) {
            j = (-1 + sqrt(1 + 4 * (2 * target + (long)i*i  - i))) / 2;  //根据一元二次方程求根公式计算得到j，为了防止i的平方溢出，将其转换为long
            if(i < j && j == (int)j) {  //满足两个条件
                vector<int> temp;
                for(int k = i; k <= j; k++) {  //将i到j中的数字添加到tem中
                    temp.push_back(k);
                }
                res.push_back(temp);  //将temp添加到结果数组中
            }
            i++;  //i加1，改变左边界，继续循环
        }
        return res;  //返回结果数组res即可
    }
};
```

【题解思路2—滑窗法】

设连续正整数序列的左边界 i 和右边界 j ，则可构建滑动窗口从左向右滑动。循环中，每轮判断滑动窗口内元素和与目标值 target 的大小关系，若相等则记录结果，若大于 target 则移动左边界 i （以减小窗口内的元素和），若小于 target 则移动右边界 j （以增大窗口内的元素和）。

【题解代码2—滑窗法】

```c++
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        int i = 1, j = 2;
        vector<vector<int>> res;
        int sum = i + j;  //初始化
        while(i < j) {  //当i>=j时，跳出循环
            /*特别需要注意本题对【sum增减】和【左右边界ij移动】这两步的先后顺序*/
            if(sum == target) {  //如果sum等于target
                vector<int> temp;
                for(int k = i; k <= j; k++) {  //将i到j的数字添加到temp中
                    temp.push_back(k);
                }
                res.push_back(temp);  //将temp添加到res中
                sum -= i;  //sum先减去左边界
                i++;  //向右移动左边界
            }
            else if(sum > target) {
                sum -=i;  //和上面的逻辑一样，也是先减再移动边界
                i++;
            }
            else if(sum < target) {
                 j++;  //先移动边界，再加上边界值，很好理解
                sum += j;                           
            }
        }
        return res;
    }
};
```

