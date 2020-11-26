#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// 桶排序思路   
// 确定桶数目 
// 确定桶大小

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) {
            return 0;
        }
        int minVar = *min_element(nums.begin(), nums.end());
        int maxVar = *max_element(nums.begin(), nums.end());
        int bucketSize = max(1, (maxVar - minVar) / (n - 1));
        int bucketNum = (maxVar - minVar) / bucketSize + 1;
        vector<vector<int>> bucket(bucketNum, vector<int> ());
        for (int i = 0; i < n; i++) {
            int idx = (nums[i] - minVar) / bucketSize;
            bucket[idx].emplace_back(nums[i]);
        }
        for (int i = 0; i < bucket.size(); i++) {
            sort(bucket[i].begin(), bucket[i].end());
        }
        int k = 0;
        for (int i = 0; i < bucket.size(); i++) {
            for (int j = 0; j < bucket[i].size(); j++) {
                nums[k++] = bucket[i][j];
            }
        }
        int maxValue = 0;
        for (int i = 1; i < nums.size(); i++) {
            maxValue = max(nums[i] - nums[i - 1], maxValue);
        }
        return maxValue;
    }
};

int main(void) {
    Solution solution;
    vector<int> nums = {3, 6, 9, 1};
    int res = solution.maximumGap(nums);
    cout << res << endl;
    return 0;
}
                    