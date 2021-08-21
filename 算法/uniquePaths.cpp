#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        int dp[n][m];
        // 初始化dp数组
        dp[0][0] = 1;
        for (int i = 1; i < m; i++) {
            dp[0][i] = 1;
        }
        for (int j = 1; j < n; j++) {
            dp[j][0] = 1;
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[n - 1][m - 1];
    }
};