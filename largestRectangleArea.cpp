#include <vector>
#include <string>
#include <queue>
#include <stack>

using namespace std;
/*
// 方法一 枚举宽 暴力
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
*/

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> left(n);
        vector<int> right(n);
        stack<int> stk;
        for (int i = 0; i < heights.size(); i++) {
            while(!stk.empty() && heights[stk.top()] >= heights[i]) {
                stk.pop();
            }
            left[i] = stk.empty() ? -1 : stk.top();
            stk.push(i);
        }
        stack<int> stkRight;
        for (int i = n - 1; i >= 0; i--) {
            while(!stkRight.empty() && heights[stkRight.top()] >= heights[i]) {
                stkRight.pop();
            }
            right[i] = stkRight.empty() ? n : stkRight.top();
            stkRight.push(i);
        }
        // 开始进行计算
        int maxSum = 0;
        for (int i = 0; i < n; i++) {
            int currSum = (right[i] - left[i] - 1) * heights[i];
            maxSum = max(maxSum, currSum);
        }
        return maxSum;
    }
};

int main(void) {

}
