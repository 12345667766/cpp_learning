#include <vector>
#include <string>
#include <queue>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        int ans = 0;
        for (int left = 0; left < n; ++left) {
            int minHeight = INT_MAX;
            for (int right = left; right < n; right++) {
                minHeight = min(minHeight, heights[right]);
                ans = max(ans, (right - left + 1) * minHeight);
            }
        }
        return ans;
    }
};