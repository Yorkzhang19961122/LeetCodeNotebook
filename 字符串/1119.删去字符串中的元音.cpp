/*
【题目】
给你一个字符串 S，请你删去其中的所有元音字母（ 'a'，'e'，'i'，'o'，'u'），并返回这个新字符串。
【示例】
输入："leetcodeisacommunityforcoders"
输出："ltcdscmmntyfrcdrs"
*/

/*
思路：遍历字符串S，若是元音字母则使用string的erase函数删除该字母，并使循环标志位回退，注意标志位的回退是重点，否则会漏判断字符！
*/

/*代码*/
class Solution {
public:
    string removeVowels(string S) {
        for(int i = 0; i < S.length(); i++){  //遍历字符串string
            if(S[i] == 'a' || S[i] == 'e' || S[i] == 'i' || S[i] == 'o' || S[i] == 'u'){  //如果字符串中第i位为元音字母
                S.erase(i,1);  //则删除该字母
                i--;  //循环标志位回退
            }
        }
        return S;
    }
};
