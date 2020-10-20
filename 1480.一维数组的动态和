class Solution {
public:
		// i=1,保留nums[0]，再将后面的元素进行相加，但该解法会改变nums数组
    vector<int> runningSum(vector<int>& nums) {  
        for(int i = 1; i < nums.size(); i++){  
            nums[i] += nums[i-1];
        }
        return nums;
    }
};
