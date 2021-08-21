#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int ptr = 0;
        queue<string> que;
        for (int i = 0; i < wordDict.size(); i++) {
            if (wordDict[i][0] == s[ptr]) {
                que.push(wordDict[i]);
            }
        }
        int size = que.size();
        for (int i = 0; i < size; i++) {
            string top = que.front();
            que.pop();
            if (s.substr(ptr, top.size()) == top) {
                ptr += 
            }
        }
    }
};