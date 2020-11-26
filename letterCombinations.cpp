#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    unordered_map<char, string> mp;
    vector<string> ans;

    void initMap() {
        mp[2] = "abc";
        mp[3] = "def";
        mp[4] = "ghi";
        mp[5] = "jkl";
        mp[6] = "mno";
        mp[7] = "pqrs";
        mp[8] = "tuv";
        mp[9] = "wxyz";
    }        
    void dfs(vector<string>& origin, string& path, int index) {
        if (path.size() == origin.size()) {
            ans.push_back(path);
        }
        string& words = origin[index];
        for (int i = 0; i < words.size(); i++) {
            path.push_back(words[i]);
            dfs(origin, path, index + 1);
            path.pop_back();
        }
    }

    vector<string> letterCombinations(string digits) {
        initMap();
        vector<string> origin;
        for (int i = 0; i < digits.size(); i++) {
            int temp = digits[i];
            string tmp = mp[temp];
            origin.push_back(tmp);
        }
        string path;
        dfs(origin, path, 0);
        return ans;
    }
};