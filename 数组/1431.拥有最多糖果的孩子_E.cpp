/*
【题目】
给你一个数组 candies 和一个整数 extraCandies ，其中 candies[i] 代表第 i 个孩子拥有的糖果数目。
对每一个孩子，检查是否存在一种方案，将额外的 extraCandies 个糖果分配给孩子们之后，此孩子有 最多 的糖果。注意，允许有多个孩子同时拥有最多的糖果数目。
【示例】
输入：candies = [2,3,5,1,3], extraCandies = 3
输出：[true,true,true,false,true] 
解释：
孩子 1 有 2 个糖果，如果他得到所有额外的糖果（3个），那么他总共有 5 个糖果，他将成为拥有最多糖果的孩子。
孩子 2 有 3 个糖果，如果他得到至少 2 个额外糖果，那么他将成为拥有最多糖果的孩子。
孩子 3 有 5 个糖果，他已经是拥有最多糖果的孩子。
孩子 4 有 1 个糖果，即使他得到所有额外的糖果，他也只有 4 个糖果，无法成为拥有糖果最多的孩子。
孩子 5 有 3 个糖果，如果他得到至少 2 个额外糖果，那么他将成为拥有最多糖果的孩子。
*/

/*
我的思路1：遍历输入的数组candies，分别给他们加上extraCandies数目的额外糖果，再和原来所有的candies元素分别比较，若大于或等于每个小朋友的糖果，则代表这个孩子可以成为糖果最多的孩子
我的思路2：初始化结果数组全为true，遍历输入的数组candies，给每个孩子加上额外数目的糖果，再和原来每个孩子的糖果数目比较，若发现小于任何一个孩子原来的糖果数目，
          则说明该孩子不会有最多的糖果，res为false
*/

/*我的代码1*/
class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        vector<bool> res(candies.size());
        for(int i = 0; i < candies.size(); i++){ //遍历所有孩子
            int count = 0;  //用于记录某个孩子的糖果多余其他count个孩子
            for(int j = 0; j <candies.size(); j++){ //将某个孩子加上额外糖果后的数量与原先所有孩子的糖果数分别进行比较
                if((candies[i] + extraCandies) >= candies[j] ) //这个孩子的糖果数加上额外糖果后大于几个孩子，count就是几
                    count++;          
            }
            if (count == candies.size()) res[i] = true; //count==candies.size()代表这个孩子的糖果数量大于所有孩子，则该方案成立，对应的res为true
            else res[i] = false; //若仍然不是最大的，则res为false
        }
        return res;
    } 
};
/*我的代码2*/
class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        vector<bool> res(candies.size(), true); //用true初始化res
        for(int i = 0; i < candies.size(); i++)  //遍历所有孩子
            for(int j = 0; j < candies.size(); j++) //将每个孩子加上额外的糖果，并和原来每个人的数量比较，若小于任何一个人，则说明他不可能是最多糖果的人
                if(candies[i] + extraCandies < candies[j])
                    res[i] = false;
        return res;
    } 
};

/*
题解思路：使用CPP STL中的max_element()函数返回数组最大元素的指针，再遍历原数组，将每个孩子加上额外的糖果，最后与原数组的最大值进行比较
*/

/*题解代码*/
class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        vector<bool> res;
        auto max_ptr = max_element(candies.begin(), candies.end()); //使用max_element()函数得到candies中最大值的指针
        int max = *max_ptr; //获得最大值指针存储的最大值
        for(auto i : candies)  //遍历candies
            res.push_back(i + extraCandies >= max); //加上额外的糖果后与原来的最大值比较，将结果存入res
    return res;
    }
};
