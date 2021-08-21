#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> ans;
    void dfs(string& result, int left, int right, int n) {
        if (left == n && right == n) {
            ans.push_back(result);
            return;
        }
        if (left < n) {
            result.push_back('(');
            dfs(result, left + 1, right, n);
            result.pop_back();
        }
        if (right < left) {
            result.push_back(')');
            dfs(result, left, right + 1, n);
            result.pop_back();
        }
    }

    vector<string> generateParenthesis(int n) {
        string result;
        dfs(result, 0, 0, n);
        return ans;
    }
};