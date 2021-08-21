#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 中心拓展法 双指针

class Solution {
public:
    int centralExpand(string& s, int i, int j) {
        int len = 0;
        while(i >= 0 && j < s.size() && s[i] == s[j]) {
            i--;
            j++;
            len += 2;
        }
        return len;
    }

    string longestPalindrome(string s) {
        if (s.size() == 0 || s.size() == 1) {
            return s;
        }
        int maxLen = 0;
        int currLen = 0;
        int originIndex = 0;
        for (int i = 0; i < s.size() - 1; i++) {
            currLen = max(centralExpand(s, i, i) - 1, currLen);
            currLen = max(centralExpand(s, i, i + 1), currLen);
            if (currLen > maxLen) {
                maxLen = currLen;
                originIndex = i - (currLen - 1) / 2;
            }            
        }
        string ans = s.substr(originIndex, maxLen);
        return ans;
    }
};