/*
【题目】
给你一个数组 nums ，数组中有 2n 个元素，按 [x1,x2,...,xn,y1,y2,...,yn] 的格式排列。请你将数组按 [x1,y1,x2,y2,...,xn,yn] 格式重新排列，返回重排后的数组。
【示例】
输入：nums = [2,5,1,3,4,7], n = 3
输出：[2,3,5,4,1,7] 
解释：由于 x1=2, x2=5, x3=1, y1=3, y2=4, y3=7 ，所以答案为 [2,3,5,4,1,7]
*/

/*
我的思路：新建三个数组res1，res2，res分别用于存放原数组中奇数，偶数和最终的元素，得到奇数和偶数的元素后，分别将它们循环放入res中
*/

/*我的代码*/
class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        vector<int> res1(n); //存放奇数元素
        vector<int> res2(n); //存放偶数元素
        vector<int> res(2*n); //存放重排结果
        int h=0;
        int g=1;  
        for(int i = 0; i < n; i++ ){ //循环得到res1和res2
            res1[i] = nums[i];
            res2[i] = nums[i+n];
        }
        for(int p=0; p < 2*n; p=p+2){ //将res1的元素按顺序放置在res中
            res[p] = res1[p-h];
            h++;
        }
        for(int q=1; q < 2*n; q=q+2){ //将res2的元素按顺序放置在res中
            res[q] = res2[q-g];
            g++;
        }
        return res; //返回结果
    }
};

/*
题解思路：新建一个数组res用于存放重排后的元素，利用vector容器的成员函数emplace_back()向res中存入元素。以nums=[2,5,1,3,4,7]为例，存入的顺序为：
nums[0],nums[3]-->nums[1],nums[4]-->nums[2],nums[5]，使用for循环实现存入的规律
*/

/*题解代码*/
class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        vector<int> res;  //res用于存放重排结果
        for(int i = 0; i < n; i++){  //每循环一次将nums下标为i和i+n的元素存入到res中
            res.emplace_back() = nums[i];
            res.emplace_back() = nums[i+n];
        }
        return res;
    }
};

/*
Tips: 
C++ STL vector添加元素push_back()和emplace_back()的区别：
push_back() 向容器尾部添加元素时，首先会创建这个元素，然后再将这个元素拷贝或者移动到容器中（如果是拷贝的话，事后会自行销毁先前创建的这个元素）；
而 emplace_back() 在实现时，则是直接在容器尾部创建这个元素，省去了拷贝或移动元素的过程。因此更推荐使用emplace_back()，具有更高的效率。
*/


