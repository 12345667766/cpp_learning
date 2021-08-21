#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<vector<int>> ans;

    void dfs(vector<int>& candidates, vector<int>& path, int sum, int target, int index) {
        if (index == candidates.size() || sum > target) {
            return;
        }
        if (index == candidates.size() && sum == target) {
            ans.push_back(path);
            return;
        }
        // 选当前下标
        path.push_back(candidates[index]);
        dfs(candidates, path, sum + candidates[index], target, index + 1);
        path.pop_back();
        // 不选当前下标
        dfs(candidates, path, sum, target, index + 1);
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        int sum = 0;
        vector<int> path;
        dfs(candidates, path, 0, target, 0);
        return ans;
    }
};