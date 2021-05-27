【题目】

输入一个字符串，打印出该字符串中字符的所有排列。

你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。

【示例】

```c++
输入：s = "abc"
输出：["abc","acb","bac","bca","cab","cba"]
```

---

【题解思路—回溯法[题解1](https://leetcode-cn.com/problems/zi-fu-chuan-de-pai-lie-lcof/solution/shu-ju-jie-gou-he-suan-fa-hui-su-suan-fa-11gk/)[题解2](https://leetcode-cn.com/problems/zi-fu-chuan-de-pai-lie-lcof/solution/c-zong-jie-liao-hui-su-wen-ti-lei-xing-dai-ni-ga-4/)】

【题解代码—回溯法】

```c++
class Solution {
public:
    unordered_set<string> store;  //用一个全局的set存储可能出现的重复情况
    void backtrack(string& s, string &temp, vector<bool>& visited) {
        //终止条件(递归必须要有终止条件)
        //选择的字符串等于原串的长度，说明已经选完了
        if (temp.size() == s.size()) {
            store.insert(temp);
            return;
        }
		//在选择列表中搜索
        for (int i = 0; i < s.size(); i++) {
            if(visited[i] == true) {
                continue;
            }
            temp += s[i];
            //做出选择
            visited[i] = true;
            //递归
            backtrack(s, temp, visited);
            //撤销选择
            visited[i] = false;
            temp.pop_back();
        }
    }

    vector<string> permutation(string s) {
        vector<string> res;
        vector<bool> visited(s.size(), false);  //使用vector<bool>来标记是否被选中
        string temp;
        backtrack(s, temp, visited);
        for(auto elem : store) res.push_back(elem);
        return res;
    }
};
```

【TIPS—回溯算法】

几篇文章：[1](https://mp.weixin.qq.com/s?__biz=MzU0ODMyNDk0Mw==&mid=2247488558&idx=1&sn=bb600c06c773960b3f4536c4c6c8d948&chksm=fb41870ecc360e18db1ca13783050d1a2efb19579407587baeea9b258a92e4c90c7ad12cbc1a&scene=21#wechat_redirect)、[2](https://leetcode-cn.com/problems/subsets/solution/c-zong-jie-liao-hui-su-wen-ti-lei-xing-dai-ni-gao-/)

回溯法：回溯算法实际上一个类似枚举的搜索尝试过程，穷举的过程就是遍历一棵二叉树的过程，主要是在搜索尝试过程中寻找问题的解，当发现已不满足求解条件时，就“回溯”返回，尝试别的路径。

回溯法是建立在DFS之上的，两者的不同点在于**有无状态重置**：

* DFS是一直往某一个方向搜索
* 回溯法是往一个方向搜索，但是在搜索过程中，达到结束状态后要恢复状态，回溯到上一层，再次搜索

回溯问题的类型：

| **类型**   | **题目链接**                                                 |
| ---------- | ------------------------------------------------------------ |
| 子集、组合 | [子集](https://leetcode-cn.com/problems/subsets/)、[子集 II](https://leetcode-cn.com/problems/subsets-ii/)、[组合](https://leetcode-cn.com/problems/combinations/)、[组合总和](https://leetcode-cn.com/problems/combination-sum/)、[组合总和 II](https://leetcode-cn.com/problems/combination-sum-ii/) |
| 全排列     | [全排列](https://leetcode-cn.com/problems/permutations/)、[全排列 II](https://leetcode-cn.com/problems/permutations-ii/)、[字符串的全排列](https://leetcode-cn.com/problems/zi-fu-chuan-de-pai-lie-lcof/)、[字母大小写全排列](https://leetcode-cn.com/problems/letter-case-permutation/) |
| ※搜索      | [解数独](https://leetcode-cn.com/problems/sudoku-solver/)、[单词搜索](https://leetcode-cn.com/problems/word-search/)、[N皇后](https://leetcode-cn.com/problems/eight-queens-lcci/)、[分割回文串](https://leetcode-cn.com/problems/palindrome-partitioning/)、[二进制手表](https://leetcode-cn.com/problems/binary-watch/) |

**注意**：子集、组合与排列是不同性质的概念。子集、组合是无关顺序的，而排列是和元素顺序有关的，如 [1，2] 和 [2，1] 是同一个组合(子集)，但 [1,2] 和 [2,1] 是两种不一样的排列！因此被分为两类问题

如何写回溯算法：

① **画出递归树，找到状态变量(回溯函数的参数)，这一步非常重要※**

② **根据题意，确立结束条件**

③ **找准选择列表(与函数参数相关),与第一步紧密关联※**

④ **判断是否需要剪枝**

⑤ **作出选择，递归调用，进入下一层**

⑥ **撤销选择**

模板（回溯法的代码框架和多叉树遍历类似）：

```c++
private void backtrack("原始参数") {
    //终止条件(递归必须要有终止条件)
    if ("终止条件") {
        //一些逻辑操作（可有可无，视情况而定）
        return;
    }

    for (int i = "for循环开始的参数"; i < "for循环结束的参数"; i++) {
        //一些逻辑操作（可有可无，视情况而定）

        //做出选择

        //递归
        backtrack("新的参数");
        //一些逻辑操作（可有可无，视情况而定）

        //撤销选择
    }
}
```

```c++
List<value> result;
void backtrack(路径，选择列表) {
	if(满足结束的条件) {
		result.add(路径);  //存放结果
		return;
	}
	for(选择:选择列表——树中节点孩子的数量就是集合的大小) {
		做选择;
		backtrack(路径，选择列表);
		撤销选择;
	}
}
```

 