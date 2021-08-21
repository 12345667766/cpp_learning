#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    static bool cmp(vector<int>& p1, vector<int>& p2) {
        return (p1[0] - p1[1]) < (p2[0] - p2[1]);
    }
    int minimumEffort(vector<vector<int>>& tasks) {
        sort(tasks.begin(), tasks.end(), cmp);
        int ans = 0;
        int sum = 0;
        for (auto task : tasks) {
            ans = max(ans, sum + task[1]);
            sum += task[0];
        }
    }
};