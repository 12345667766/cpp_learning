#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<vector<int>> ans;

    void dfs(int index, vector<int>& nums, vector<int>& subset) {
        if (index == nums.size()) {
            ans.push_back(subset);
            return;
        }        
        dfs(index + 1, nums, subset);
        subset.push_back(nums[index]);        
        dfs(index + 1, nums, subset);  
        subset.pop_back();      
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> subset;
        dfs(0, nums, subset);
        return ans;
    }
};