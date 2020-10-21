/*
【题目】
给你一个数组 nums ，数组「动态和」的计算公式为：runningSum[i] = sum(nums[0]…nums[i])，请返回 nums 的动态和
【示例】
输入：nums = [1,2,3,4]
输出：[1,3,6,10]
解释：动态和计算过程为 [1, 1+2, 1+2+3, 1+2+3+4] 
*/

/*
思路：给定一个数组nums，计算并返回nums的动态和数组，输出的动态和数组nums第一位(nums[0])保持不变
ex:    1. 2. 3. 4. 5
       1. (1+2). 3. 4. 5                           --> nums[1] = nums[1] + nums[0]
       1. (1+2). (1+2)+3. 4. 5                     --> nums[2] = nums[2] + nums[1]
       1. (1+2). (1+2)+3. (1+2+3)+4. 5.            --> nums[3] = nums[3] + nums[2]
       1. (1+2). (1+2)+3. (1+2+3)+4. (1+2+3+4)+5   --> nums[4] = nums[4] + nums[3]
                                                   --> nums[i] += nums[i-1]
*/
/*代码*/
class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        for(int i = 1; i < nums.size(); i++)  //i从1开始，使nums的第一个元素nums[0]不变
            nums[i] += nums[i-1];  
        return nums;
    }
};

/*
Tips：
以上方法会改变原来的nums数组，题目若修改函数签名为vector<int> runningSum(const vector<int>& nums)则明确禁止修改传入的nums。
ex:  1. 2. 3. 4. 5.
     1. (1+2).                                   --> res[1] = res[0] + nums[1]
     1. (1+2). (1+2)+3.                          --> res[2] = res[1] + nums[2]
     1. (1+2). (1+2+3). (1+2+3)+4.               --> res[3] = res[2] + nums[3]
     1. (1+2). (1+2+3). (1+2+3)+4. (1+2+3+4)+5.  --> res[4] = res[3] + nums[4]
                                                 --> res[i] = res[i-1] + nums[i]
下面的解法不会修改传入的数组：
*/
/*代码*/
class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> res(nums.size());  //初始化res，有nums.size()个元素
        res[0] = nums[0];
        for(int i = 1; i < nums.size(); i++)
            res[i] = res[i-1] + nums[i];
        return res;
    }
};
