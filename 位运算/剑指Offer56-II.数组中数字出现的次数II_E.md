【题目】

在一个数组 `nums` 中除一个数字只出现一次之外，其他数字都出现了三次。请找出那个只出现一次的数字。

【实例】

```c++
输入：nums = [9,1,7,9,7,9,7]
输出：1
```

---

【我的思路—map】

创建unordered_map，键key为nums中的数字，值value为数字出现的次数，遍历nums，得到每个数字出现的次数，再便利map，找到只出现一次的数字（map.second==1）并返回。

【我的代码—map】

```c++
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_map<int, int> map;
        for(int i = 0; i < nums.size(); ++i){  //便利nums
            map[nums[i]]++;
        }
        for(auto elem : map){  //遍历map
            if(elem.second == 1) return elem.first;
        }
        return -1;
    }
};
```

【题解思路—位运算】

* 根据题意我们可以找出这么一个规律：假设不存在这个 single number，那么 nums 中所有元素的二进制形式加起来之后，每一位必然都可以被 3 整除。因为每个数字都出现了三次，那么它们的二进制形式每一位也都出现了三次，那加起来之后每一位当然可以被 3 整除了。
* 现在加上这个 single number，我们可以进一步想到：同样把 nums 中所有元素的二进制形式加起来，这时候就不是每一位都能被 3 整除了，因为混入了一个只出现了一次的元素。所以我们只需要看加起来之后的和的哪一位不能被 3 整除，就说明这个 single number 的二进制形式在这一位是 1。然后把这些 single number 是 1 的位转换成十进制再加起来，就是 single number 的十进制形式了。
* 举个例子：假设 single number = 1，然后 nums 中所有元素的二进制形式加起来之后等于 3334（即 3333 + 1 = 3334）。那么我们就知道，4 这一位不能被 3 整除，说明 single number 在从右往左第一位是 1。然后因为剩下的全都能被 3 整除，所以 single number 在剩下的位上都是 0。由此可得 single number = 0001 = 1。

【题解代码—位运算】

```c++
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int binsum[32] = {0};  //因为int最大到2^31，所以二进制形式最大为32位
        for(int num : nums) {
            for(int i = 31; i >=0; i--){
                binsum[i] += num & 1;  //将nums的所有num转为二进制并相加
                num >>= 1;
            }  
        }
        int res = 0;
        for(int i = 31; i >= 0; i--){
            if(binsum[i] % 3 != 0){  //哪一位不能被3整除，就说明目标数字的二进制在该位为1
                res += pow(2, (31 - i));  //将二进制转为十进制
            }
        }
        return res;
    }
};
```

