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

【TIPS】

几篇文章：[1](https://mp.weixin.qq.com/s?__biz=MzU0ODMyNDk0Mw==&mid=2247488558&idx=1&sn=bb600c06c773960b3f4536c4c6c8d948&chksm=fb41870ecc360e18db1ca13783050d1a2efb19579407587baeea9b258a92e4c90c7ad12cbc1a&scene=21#wechat_redirect)、[2](https://leetcode-cn.com/problems/subsets/solution/c-zong-jie-liao-hui-su-wen-ti-lei-xing-dai-ni-gao-/)

回溯法：

模板：

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

